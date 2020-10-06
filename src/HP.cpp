// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "HP.hpp"

#include <QGraphicsScene>
#include <QGraphicsRectItem>

namespace TowerDefence
{
	HP::HP(std::shared_ptr<QGraphicsScene> scene) :
		m_back(scene->addRect(0., 0., HP::WIDTH, HP::HEIGHT, QPen(Qt::black), Qt::transparent)),
		m_front(scene->addRect(0., 0., HP::WIDTH, HP::HEIGHT, QPen(Qt::transparent), Qt::green))
	{ }

	void HP::setPos(const PosF & pos)
	{
		if (m_back && m_front)
		{
			m_back->setPos(pos.x, pos.y);
			m_front->setPos(pos.x, pos.y);
		}
	}

	void HP::setHP(const float percent)
	{
		if (m_front)
			;
	}
} // namespace TowerDefence