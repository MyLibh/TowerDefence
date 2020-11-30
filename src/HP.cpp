// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "HP.hpp"

#include <QGraphicsScene>
#include <QGraphicsRectItem>

namespace TowerDefence
{
	HP::HP(std::shared_ptr<QGraphicsScene> scene, const PosI& size /* = { HP::WIDTH, HP::HEIGHT } */) :
		m_back(scene->addRect(0., 0., size.x, size.y, QPen(Qt::black, 5), Qt::transparent)),
		m_front(scene->addRect(0., 0., size.x, size.y, QPen(Qt::transparent, 5), Qt::green))
	{ }

	void HP::setPos(const PosF & pos) noexcept
	{
		if (m_back && m_front)
		{
			const QPointF newPos{ pos.x - m_back->rect().width() / 2, pos.y };
			m_back->setPos(newPos);
			m_front->setPos(newPos);
		}
	}

	void HP::setHP(const float percent) noexcept
	{
		if (m_front)
		{
			auto rect = m_front->rect();
			rect.setWidth(rect.width() * percent);

			m_front->setRect(rect);
		}
	}
} // namespace TowerDefence