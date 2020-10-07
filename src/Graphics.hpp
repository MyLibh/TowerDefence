#ifndef __GRAPHICS_HPP_INCLUDED__
#define __GRAPHICS_HPP_INCLUDED__

#include "TowerGraphics.hpp"
#include "CastleGraphics.hpp"

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

		void addCastle(std::shared_ptr<Castle> castle);

	public:
		inline Graphics() :
			m_tileWidth{},
			m_tileHeight{},
			m_scene(std::make_shared<QGraphicsScene>()),
			m_grid(),
			m_images(),
			m_currentTile{},
			m_castle(),
			m_towers()
		{ }

		inline ~Graphics() noexcept = default;

		_NODISCARD inline auto& getScene() const noexcept { return m_scene; }

		_NODISCARD PosF getSelectedTilePos() const noexcept;

		inline void setTileSize(const float width, const float height) noexcept
		{
			m_tileWidth = width;
			m_tileHeight = height;
		}

		bool isTileSelected() const noexcept;

		void createMap(const std::shared_ptr<Landscape>& landscape);

		void draw() const;

		void setCurrentTilePos(int x, int y);

		void addTower(std::shared_ptr<Tower> tower);

	private:
		float                           m_tileWidth;
		float                           m_tileHeight;
		std::shared_ptr<QGraphicsScene> m_scene;
		std::vector<QGraphicsLineItem*> m_grid[2];
		std::map<std::string, QPixmap>  m_images;
		QGraphicsRectItem*              m_currentTile;
		
		std::unique_ptr<CastleGraphics> m_castle;
		std::vector<TowerGraphics>      m_towers;
	};
} // namespace TowerDefence

#endif /* !__GRAPHICS_HPP_INCLUDED__ */