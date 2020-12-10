#ifndef __GRAPHICS_AURA_HPP_INCLUDED__
#define __GRAPHICS_AURA_HPP_INCLUDED__

#include "Pos.hpp"
#include "Particle.hpp"
#include "Aura.hpp"

#include <QPixmap>

#include <memory>
#include <array>

class QGraphicsScene;
class QGraphicsEllipseItem;
class QGraphicsPixmapItem;

namespace TowerDefence
{
	class GraphicsAura
	{
	public:
		inline GraphicsAura() noexcept = default;

		GraphicsAura(std::shared_ptr<QGraphicsScene> scene, const float r, const PosF& scale, QColor color, const QPixmap& particlePixmap);

		GraphicsAura(const GraphicsAura&) = delete;

		inline GraphicsAura(GraphicsAura&& other) noexcept :
			m_scale(std::move(other.m_scale)),
			m_r(std::move(other.m_r)),
			m_scene(std::move(other.m_scene)),
			m_item(std::move(other.m_item)),
			m_particles(std::move(other.m_particles))
		{
			other.m_scale = {};
			other.m_r = 0.f;
			other.m_scene = nullptr;
			other.m_item = nullptr;
		}

		inline ~GraphicsAura() noexcept = default;

		GraphicsAura& operator=(const GraphicsAura&) = delete;

		inline GraphicsAura& operator=(GraphicsAura&& other) noexcept
		{
			if (this != &other)
			{
				m_scale = std::move(other.m_scale);
				m_r = std::move(other.m_r);
				m_scene = std::move(other.m_scene);
				m_item = std::move(other.m_item);
				m_particles = std::move(other.m_particles);

				other.m_scale = {};
				other.m_r = 0.f;
				other.m_scene = nullptr;
				other.m_item = nullptr;
			}

			return *this;
		}

		void setPos(const PosF& pos) noexcept;

		inline void update() noexcept
		{
			for (auto& particle : m_particles)
				particle.update(m_scale.x, m_scale.y);
		}

	private:
		PosF m_scale;
		float m_r;
		std::shared_ptr<QGraphicsScene> m_scene;
		std::shared_ptr<QGraphicsEllipseItem> m_item;
		std::vector<Particle> m_particles;
	};

	using GAura = GraphicsAura;
} // namespace TowerDefence

#endif /* !__GRAPHICS_AURA_HPP_INCLUDED__ */