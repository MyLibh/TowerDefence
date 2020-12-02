#ifndef __GRAPHICS_OBJECT_HPP_INCLUDED__
#define __GRAPHICS_OBJECT_HPP_INCLUDED__

#include "Pos.hpp"

#include <memory>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>

namespace TowerDefence
{
	template<typename _T>
	class GraphicsObject
	{
	public:
		inline constexpr GraphicsObject() noexcept :
			m_item{},
			m_object()
		{ }

		inline GraphicsObject(std::shared_ptr<QGraphicsScene> scene, QPixmap pixmap, std::shared_ptr<_T> object) :
			m_scene(scene),
			m_item(scene->addPixmap(pixmap)),
			m_object(std::move(object))
		{ }

		inline virtual ~GraphicsObject() noexcept
		{
			if (m_scene && m_item.use_count() == 1)
				m_scene->removeItem(m_item.get());
		}

		[[nodiscard]] inline constexpr auto getItem() const noexcept { return m_item; }

		[[nodiscard]] inline constexpr auto getObject() const noexcept { return m_object; }

		inline virtual void setPos(const PosF& pos) noexcept
		{
			if (m_item)
				m_item->setPos(pos.x, pos.y);
		}

		inline virtual void update(const float dx, const float dy) noexcept 
		{
			auto [x, y] = m_object->getPos();
			setPos({ x * dx, y * dy });
		}

	protected:
		std::shared_ptr<QGraphicsPixmapItem> m_item;
		std::shared_ptr<_T>  m_object;

	private:
		std::shared_ptr<QGraphicsScene> m_scene;
	};

	template<typename _T>
	using GObject = GraphicsObject<_T>;
} // namespace TowerDefence 

#endif /* !__GRAPHICS_OBJECT_HPP_INCLUDED__ */