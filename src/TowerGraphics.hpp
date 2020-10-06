#ifndef __TOWER_GRAPHICS_HPP_INCLUDED__
#define __TOWER_GRAPHICS_HPP_INCLUDED__

#include "Pos.hpp"

#include <memory>

class QGraphicsScene;
class QGraphicsPixmapItem;
class QPixmap;

namespace TowerDefence
{
	class Tower;

	class TowerGraphics final
	{
	public:
		TowerGraphics::TowerGraphics(std::shared_ptr<QGraphicsScene> scene, QPixmap pixmap, std::shared_ptr<Tower> tower);

		void setPos(const PosF& pos) noexcept;

	private:
		QGraphicsPixmapItem* m_item;
		std::shared_ptr<Tower> m_tower;
	};
} // namespace TowerDefence 

#endif /* !__TOWER_GRAPHICS_HPP_INCLUDED__ */