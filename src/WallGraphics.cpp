#include "WallGraphics.hpp"
#include "Wall.hpp"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>

namespace TowerDefence
{
	WallGraphics::WallGraphics(std::shared_ptr<QGraphicsScene> scene, QPixmap pixmap, std::shared_ptr<Wall> wall) :
		m_item(scene->addPixmap(pixmap)),
		m_wall(wall),
		m_hp(scene)
	{ }

	void WallGraphics::setPos(const PosF& pos)
	{
		if (m_item)
		{
			m_item->setPos(pos.x, pos.y);

			m_hp.setPos(pos);
		}
	}

	void WallGraphics::draw() const
	{
		m_hp.setHP(1.f * m_wall->getHealth() / m_wall->getMaxHealth());
	}
} // namespace TowerDefence