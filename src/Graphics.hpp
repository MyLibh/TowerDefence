#ifndef __GRAPHICS_HPP_INCLUDED__
#define __GRAPHICS_HPP_INCLUDED__

#include "GraphicsObjectWithHPAndAura.hpp"
#include "GraphicsObjectUpgradableWithHP.hpp"
#include "GraphicsBullet.hpp"
#include "AirEnemy.hpp"
#include "HeavyEnemy.hpp"
#include "LightEnemy.hpp"
#include "Castle.hpp"
#include "Lair.hpp"
#include "Wall.hpp"
#include "Tower.hpp"

#include <vector>
#include <map>
#include <string>

class QGraphicsLineItem;

namespace TowerDefence
{
	class Landscape;

	class Graphics
	{
	private:
		void loadImages();

		void createGrid(const float width, const float height);

		void createSelectionTile();

	public:
		inline Graphics() :
			m_tileWidth{},
			m_tileHeight{},
			m_scene(std::make_shared<QGraphicsScene>()),
			m_currentTile{},
			m_castle{},
			m_gameOver{}
		{ }

		inline ~Graphics() noexcept
		{
			delete m_castle;
		}

		[[nodiscard]] inline constexpr auto getScaleX() const noexcept { return m_tileWidth; }

		[[nodiscard]] inline constexpr auto getScaleY() const noexcept { return m_tileHeight; }

		[[nodiscard]] inline auto& getScene() const noexcept { return m_scene; }

		[[nodiscard]] PosF getSelectedTilePos() const noexcept;

		inline void setTileSize(const float width, const float height) noexcept
		{
			m_tileWidth = width;
			m_tileHeight = height;
		}

		bool isTileSelected() const noexcept;

		void createMap(const std::shared_ptr<Landscape>& landscape);

		void update();

		void showGameOver(const int width, const int height);

		void setCurrentTilePos(int x, int y);

		template<typename _T>
		inline void add(std::shared_ptr<_T> object)
		{
			auto scale = PosF{ m_tileWidth, m_tileHeight };

#define _params(str, ...) scale, m_scene, m_images.at(str).scaled(m_tileWidth, m_tileHeight), object, __VA_ARGS__
#define _add(cont, str, ...) ptr = &cont.emplace_back(_params(str, __VA_ARGS__))

			GObject<_T>* ptr{};
			if constexpr (std::is_same_v<_T, Castle>)
				ptr = (m_castle = new GObjectUpgradableWithHP<Castle>(_params("Castle1", "Castle", m_images, PosI{ 100, 15 })));
			else if constexpr (std::is_same_v<_T, Lair>)
				_add(m_lairs, "Lair");
			else if constexpr (std::is_same_v<_T, Wall>)
				_add(m_walls, "Wall");
			else if constexpr (std::is_same_v<_T, Tower>)
				_add(m_towers, "Tower1", "Tower", m_images);
			//object->getR() * m_tileWidth,
			//object->getR() * m_tileHeight);
			else if constexpr (std::is_same_v<_T, Bullet>)
			{
				ptr = &m_bullets.emplace_back(scale, m_scene, m_images.at("Bullet").scaled(30, 20), object);
				if (ptr)
					ptr->getItem()->setZValue(2);
			}
			else if constexpr (std::is_base_of_v<Enemy, _T>)
			{
				if (typeid(*object) == typeid(AirEnemy))
					_add(m_enemies, "AirEnemy", m_images);
				else if (typeid(*object) == typeid(HeavyEnemy))
					_add(m_enemies, "HeavyEnemy", m_images);
				else if (typeid(*object) == typeid(LightEnemy))
					_add(m_enemies, "LightEnemy", m_images);

				if (ptr)
					ptr->getItem()->setZValue(1);
			}

			if (ptr)
				ptr->setPos({ object->getX() * m_tileWidth, object->getY() * m_tileHeight });

#undef _add
#undef _params
		}

	private:
		float                           m_tileWidth;
		float                           m_tileHeight;
		std::shared_ptr<QGraphicsScene> m_scene;
		std::vector<QGraphicsLineItem*> m_grid[2];
		std::map<std::string, QPixmap>  m_images;
		QGraphicsRectItem*              m_currentTile;
		
		GObjectUpgradableWithHP<Castle>*         m_castle;
		std::vector<GObject<Lair>>               m_lairs;
		std::vector<GObjectWithHP<Wall>>         m_walls;
		std::vector<GObjectUpgradable<Tower>>    m_towers;
		std::vector<GObjectWithHPAndAura<Enemy>> m_enemies;
		std::vector<GObject<Bullet>>             m_bullets;

		QGraphicsPixmapItem* m_gameOver;
	};
} // namespace TowerDefence

#endif /* !__GRAPHICS_HPP_INCLUDED__ */