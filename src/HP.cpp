// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "HP.hpp"
#include "Constants.hpp"

#include <QGraphicsScene>
#include <QGraphicsRectItem>

namespace TowerDefence
{
	HP::HP(std::shared_ptr<QGraphicsScene> scene, const PosI& size /* = { HP::WIDTH, HP::HEIGHT } */) :
		m_scene(scene),
		m_back(scene->addRect(0., 0., size.x, size.y, QPen(Qt::black, 3), Qt::transparent)),
		m_front(scene->addRect(0., 0., size.x, size.y, QPen(Qt::transparent, 3), Qt::green))
	{
		m_back->setZValue(Constants::GUI_Z_LVL);
		m_front->setZValue(Constants::GUI_Z_LVL);
	}

	HP::~HP() noexcept
	{
		if (m_scene && m_front.use_count() == 1 && m_back.use_count() == 1)
		{
			if (m_front) m_scene->removeItem(m_front.get());
			if (m_back)  m_scene->removeItem(m_back.get());

			m_front = m_back = nullptr;
		}
	}

	void HP::setPos(const PosF& pos) noexcept
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
		if (m_front && m_back)
		{
			auto rect = m_front->rect();
			rect.setWidth(m_back->rect().width() * percent);

			m_front->setRect(rect);
		}
	}
} // namespace TowerDefence