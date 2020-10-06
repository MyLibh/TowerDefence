// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "TowerGraphics.hpp"
#include "Tower.hpp"

#include <QGRaphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>

namespace TowerDefence
{
	TowerGraphics::TowerGraphics(std::shared_ptr<QGraphicsScene> scene, QPixmap pixmap, std::shared_ptr<Tower> tower) :
		m_item(scene->addPixmap(pixmap)),
		m_tower(tower)
	{ }

	void TowerGraphics::setPos(const PosF& pos) noexcept
	{
		if (m_item)
			m_item->setPos(pos.x, pos.y);
	}
}
