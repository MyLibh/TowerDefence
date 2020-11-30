#ifndef __GRAPHICS_HPP_INCLUDED__
#define __GRAPHICS_HPP_INCLUDED__

#include "GraphicsObjectWithHPAndAura.hpp"
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
			m_grid(),
			m_images(),
			m_currentTile{},
			m_castle{},
			m_lairs(),
			m_walls(),
			m_towers(),
			m_enemies(),
			m_gameOver{}
		{ }

		inline ~Graphics() noexcept = default;

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
#define _add(cont, str, ...) ptr = &cont.emplace_back(m_scene, m_images.at(str).scaled(m_tileWidth, m_tileHeight), object, __VA_ARGS__)

			GraphicsObject<_T>* ptr{};
			if constexpr (std::is_same_v<_T, Castle>)
				ptr = &(m_castle = GraphicsObjectWithHP<Castle>(m_scene, m_images.at("Castle").scaled(m_tileWidth, m_tileHeight), object, PosI{ 100, 15 }));
			else if constexpr (std::is_same_v<_T, Lair>)
				_add(m_lairs, "Lair");
			else if constexpr (std::is_same_v<_T, Wall>)
				_add(m_walls, "Wall");
			else if constexpr (std::is_same_v<_T, Tower>)
				_add(m_towers, "Tower", object->getR() * m_tileWidth, object->getR() * m_tileHeight);
			else if constexpr (std::is_same_v<_T, Enemy>)
			{
				if (typeid(*object) == typeid(AirEnemy))
					_add(m_enemies, "AirEnemy", 0, 0);
				else if (typeid(*object) == typeid(HeavyEnemy))
					_add(m_enemies, "HeavyEnemy", 0, 0);
				else if (typeid(*object) == typeid(LightEnemy))
					_add(m_enemies, "LightEnemy", 0, 0);
			}

			if (ptr)
				ptr->setPos({ object->getX() * m_tileWidth, object->getY() * m_tileHeight });

#undef _add
		}

	private:
		float                           m_tileWidth;
		float                           m_tileHeight;
		std::shared_ptr<QGraphicsScene> m_scene;
		std::vector<QGraphicsLineItem*> m_grid[2];
		std::map<std::string, QPixmap>  m_images;
		QGraphicsRectItem*              m_currentTile;
		
		GObjectWithHP<Castle>                    m_castle;
		std::vector<GObject<Lair>>               m_lairs;
		std::vector<GObjectWithHP<Wall>>         m_walls;
		std::vector<GObjectWithAura<Tower>>      m_towers;
		std::vector<GObjectWithHPAndAura<Enemy>> m_enemies;

		QGraphicsPixmapItem* m_gameOver;
	};
} // namespace TowerDefence

#endif /* !__GRAPHICS_HPP_INCLUDED__ */