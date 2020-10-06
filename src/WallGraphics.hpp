#ifndef __WALL_GRAPHICS_HPP_INCLUDED__
#define __WALL_GRAPHICS_HPP_INCLUDED__

#include "Pos.hpp"
#include "HP.hpp"

#include <memory>

class QGraphicsScene;
class QGraphicsPixmapItem;
class QPixmap;

namespace TowerDefence
{
	class Wall;

	class WallGraphics final
	{
	public:
		WallGraphics(std::shared_ptr<QGraphicsScene> scene, QPixmap pixmap, std::shared_ptr<Wall> wall);

		void setPos(const PosF& pos);

		void draw() const;

	private:
		QGraphicsPixmapItem*  m_item;
		std::shared_ptr<Wall> m_wall;
		mutable HP            m_hp;
	};
} // namespace TowerDefence

#endif /* !__WALL_GRAPHICS_HPP_INCLUDED__ */