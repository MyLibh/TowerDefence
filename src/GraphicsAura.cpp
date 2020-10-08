// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "GraphicsAura.hpp"

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

namespace TowerDefence
{
	GraphicsAura::GraphicsAura(std::shared_ptr<QGraphicsScene> scene, const float rx, const float ry) :
		m_rx(rx),
		m_ry(ry),
		m_item(scene->addEllipse(0., 0., 2. * m_rx, 2. * m_ry, QPen(Qt::black)))
	{ }

	void GraphicsAura::setPos(const PosF& pos) noexcept
	{
		if (m_item)
		{
			m_item->setPos(static_cast<qreal>(pos.x) - m_rx, pos.y - m_ry / 2.);
		}
	}
} // namespace TowerDefence