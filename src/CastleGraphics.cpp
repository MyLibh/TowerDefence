#include "CastleGraphics.hpp"
#include "Castle.hpp"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>

namespace TowerDefence
{
	CastleGraphics::CastleGraphics(std::shared_ptr<QGraphicsScene> scene, QPixmap pixmap, std::shared_ptr<Castle> castle) :
		m_item(scene->addPixmap(pixmap)),
		m_castle(castle),
		m_hp(scene)
	{ }

	void CastleGraphics::setPos(const PosF& pos)
	{
		if (m_item)
		{
			m_item->setPos(pos.x, pos.y);

			m_hp.setPos(pos);
		}
	}

	void CastleGraphics::draw() const
	{
		m_hp.setHP(1.f * m_castle->getHealth() / m_castle->getMaxHealth());
	}
}