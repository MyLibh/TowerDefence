#ifndef __GRAPHICS_OBJECT_HPP_INCLUDED__
#define __GRAPHICS_OBJECT_HPP_INCLUDED__

#include "Entity.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"

#include <memory>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>

namespace TowerDefence
{
	template<typename _T> requires std::is_base_of_v<Entity, _T>
	class GraphicsObject
	{
	public:
		inline GraphicsObject() noexcept = default;

		inline GraphicsObject(const PosF& scale, std::shared_ptr<QGraphicsScene> scene, const QPixmap& pixmap, std::shared_ptr<_T> object) :
			m_scale(scale),
			m_scene(scene),
			m_item(scene->addPixmap(pixmap)),
			m_object(object)
		{ }

		GraphicsObject(const GraphicsObject&) = delete;

		inline GraphicsObject(GraphicsObject&& other) noexcept :
			m_item(std::move(other.m_item)),
			m_object(std::move(other.m_object)),
			m_scale(std::move(other.m_scale)),
			m_scene(std::move(other.m_scene))
		{
			other.m_item = nullptr;
			other.m_object = nullptr;
			other.m_scale = {};
			other.m_scene = nullptr;
		}

		inline virtual ~GraphicsObject() noexcept = default;

		GraphicsObject& operator=(const GraphicsObject&) = delete;

		inline GraphicsObject& operator=(GraphicsObject&& other) noexcept
		{
			if (this != &other)
			{
				m_item = std::move(other.m_item);
				m_object = std::move(other.m_object);
				m_scale = std::move(other.m_scale);
				m_scene = std::move(other.m_scene);

				other.m_item = nullptr;
				other.m_object = nullptr;
				other.m_scale = {};
				other.m_scene = nullptr;
			}

			return *this;
		}

		[[nodiscard]] inline constexpr auto getItem() const noexcept { return m_item; }

		[[nodiscard]] inline constexpr auto getObject() const noexcept { return m_object; }

		[[nodiscard]] inline constexpr auto getScaleX() const noexcept { return m_scale.x; }

		[[nodiscard]] inline constexpr auto getScaleY() const noexcept { return m_scale.y; }

		[[nodiscard]] inline constexpr auto getScale() const noexcept { return m_scale; }

		inline virtual void setPos(const PosF& pos) noexcept
		{
			if (m_item)
				m_item->setPos(pos.x, pos.y);
		}

		void setScaleX(const float scaleX) noexcept { m_scale.x = scaleX; }

		void setScaleY(const float scaleY) noexcept { m_scale.y = scaleY; }

		void setScale(const PosF& scale) noexcept { m_scale = scale; }

		inline virtual void update() noexcept
		{
			if (m_object)
			{
				auto [x, y] = m_object->getPos();
				setPos(PosF{ x * m_scale.x, y * m_scale.y });
			}
		}

	protected:
		std::shared_ptr<QGraphicsPixmapItem> m_item;
		std::shared_ptr<_T>                  m_object;

	private:
		PosF m_scale;
		std::shared_ptr<QGraphicsScene> m_scene;
	};

	template<>
	inline void GraphicsObject<Bullet>::update() noexcept
	{
		if (m_object)
		{
			const auto [x, y] = m_object->getPos();
			setPos(PosF{ x * m_scale.x, y * m_scale.y });

			if (m_item)
			{
				const auto [targetX, targetY] = m_object->getTarget()->getPos();
				PosF v{ targetX + .5f - x, targetY +.5f - y };

				int angle = Angle(v);
				m_item->setRotation(angle);
			}
		}
	}

	template<typename _T>
	using GObject = GraphicsObject<_T>;
} // namespace TowerDefence 

#endif /* !__GRAPHICS_OBJECT_HPP_INCLUDED__ */