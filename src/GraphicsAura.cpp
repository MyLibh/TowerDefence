// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "GraphicsAura.hpp"

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

#include <algorithm>

namespace TowerDefence
{
	GraphicsAura::GraphicsAura(std::shared_ptr<QGraphicsScene> scene, const float r, const PosF& scale, QColor color, QPixmap particlePixmap) :
		m_scale(scale),
		m_r(r),
		m_scene(scene),
		m_item(scene->addEllipse(0., 0., 2. * m_r * m_scale.x, 2. * m_r * m_scale.y, QPen(color)))
	{
		for (size_t i{}; i < GAura::PARTICLES_NUM; ++i)
			m_particles.emplace_back(m_scene, particlePixmap, m_r * m_scale.x, m_r * m_scale.y);
	}

	void GraphicsAura::setPos(const PosF& pos) noexcept
	{
		if (m_item)
			m_item->setPos(pos.x - static_cast<qreal>(m_r) * m_scale.x, pos.y - static_cast<qreal>(m_r) * m_scale.y / 2.);

		for (auto& particle : m_particles) 
			particle.setPos(pos);
	}
} // namespace TowerDefence