#ifndef __GRAPHICS_HPP_INCLUDED__
#define __GRAPHICS_HPP_INCLUDED__

#include "Pos.hpp"

#include <memory>
#include <vector>
#include <map>
#include <string>

#include <QtGlobal>

class QGraphicsScene;
class QGraphicsLineItem;
class QGraphicsRectItem;
class QPixmap;

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
		_INLINE_VAR Graphics() :
			m_tileWidth{},
			m_tileHeight{},
			m_scene(std::make_unique<QGraphicsScene>()),
			m_grid(),
			m_images(),
			m_currentTile{}
		{ }

		_INLINE_VAR ~Graphics() noexcept = default;

		_NODISCARD _INLINE_VAR auto& getScene() const noexcept { return m_scene; }

		_NODISCARD PosF getSelectedTilePos() const noexcept;

		_INLINE_VAR void setTileSize(const float width, const float height) noexcept
		{
			m_tileWidth = width;
			m_tileHeight = height;
		}

		bool isTileSelected() const noexcept;

		void createMap(const std::shared_ptr<Landscape>& landscape);

		void draw() const;

		void setCurrentTilePos(int x, int y);

	private:
		float                           m_tileWidth;
		float                           m_tileHeight;
		std::unique_ptr<QGraphicsScene> m_scene;
		std::vector<QGraphicsLineItem*> m_grid[2];
		std::map<std::string, QPixmap>  m_images;
		QGraphicsRectItem*              m_currentTile;
	};
} // namespace TowerDefence

#endif /* !__GRAPHICS_HPP_INCLUDED__ */