#ifndef __PARTICLE_HPP_INCLUDED__
#define __PARTICLE_HPP_INCLUDED__

#include "Pos.hpp"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPixmap>

namespace detail
{
	inline QPixmap setAlpha(const QPixmap& pixmap, const float val)
	{
		QPixmap alpha(pixmap);

		QPainter p(&alpha);
		p.setOpacity(val);
		p.drawPixmap(0, 0, pixmap);
		p.end();

		return alpha;
	}
} // namespace detail

namespace TowerDefence
{
	class Particle
	{
	private:
		inline void setOffsets()
		{
			m_offsetX = rand() % (2 * MAX_X) - 1.2 * MAX_X;
			m_offsetY = rand() % (2 * MAX_Y) - 1.5 * MAX_Y;
		}

	public:
		inline Particle(std::shared_ptr<QGraphicsScene> scene, const QPixmap& pixmap, const int maxX, const int maxY) :
			m_pixmap(pixmap),
			m_scene(scene),
			m_item(scene->addPixmap(pixmap)),
			MAX_X(maxX),
			MAX_Y(maxY),
			m_offsetX{},
			m_offsetY{}
		{
			setOffsets();
		}

		Particle(const Particle&) = delete;

		inline Particle(Particle&& other) noexcept :
			m_item(std::move(other.m_item)),
			m_scene(std::move(other.m_scene)),
			m_offsetX(std::move(other.m_offsetX)),
			m_offsetY(std::move(other.m_offsetY)),
			MAX_X(std::move(other.MAX_X)),
			MAX_Y(std::move(other.MAX_Y))
		{
			other.m_item = nullptr;
			other.m_scene = nullptr;
			other.m_offsetX = other.m_offsetY = 0.f;
			other.MAX_X = other.MAX_Y = 0;
		}

		inline ~Particle()
		{
			if (m_scene && m_item && m_item.use_count() == 1)
				m_scene->removeItem(m_item.get());
		}

		Particle& operator=(const Particle&) = delete;

		Particle& operator=(Particle&& other) noexcept
		{
			if (this != &other)
			{
				m_item = std::move(other.m_item);
				m_scene = std::move(other.m_scene);
				m_offsetX = std::move(other.m_offsetX);
				m_offsetY = std::move(other.m_offsetY);
				MAX_X = std::move(other.MAX_X);
				MAX_Y = std::move(other.MAX_Y);

				other.m_item = nullptr;
				other.m_scene = nullptr;
				other.m_offsetX = other.m_offsetY = 0.f;
				other.MAX_X = other.MAX_Y = 0;
			}

			return *this;
		}

		inline void setPos(const PosF& pos)
		{
			if (m_item)
				m_item->setPos(static_cast<qreal>(pos.x) + m_offsetX, static_cast<qreal>(pos.y) - m_offsetY);
		}

		inline void update(const float dx, const float dy)
		{
			if (m_offsetY > MAX_Y / 2.f)
				setOffsets();

			m_offsetY += dy * 0.08;
		}

	private:
		QPixmap m_pixmap;
		std::shared_ptr<QGraphicsPixmapItem> m_item;
		std::shared_ptr<QGraphicsScene> m_scene;
		float m_offsetX;
		float m_offsetY;
		int MAX_X;
		int MAX_Y;
	};
} // namespace TowerDefence

#endif /* !__PARTICLE_HPP_INCLUDED__ */