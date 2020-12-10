#ifndef __GRAPHICS_OBJECT_WITH_HP_HPP_INCLUDED__
#define __GRAPHICS_OBJECT_WITH_HP_HPP_INCLUDED__

#include "GraphicsObject.hpp"
#include "HP.hpp"
#include "ObjectWithHP.hpp"

namespace TowerDefence
{
	template<typename _T> requires std::is_base_of_v<ObjectWithHP, _T>
	class GraphicsObjectWithHP : virtual public GObject<_T>
	{
	public:
		inline GraphicsObjectWithHP() noexcept = default;

		inline GraphicsObjectWithHP(
			const PosF& scale,
			std::shared_ptr<QGraphicsScene> scene,
			const QPixmap& pixmap,
			std::shared_ptr<_T> object,
			const PosI& size = { HP::WIDTH, HP::HEIGHT }) :
			GObject<_T>(scale, scene, pixmap, object),
			m_hp(scene, size)
		{ }

		GraphicsObjectWithHP(const GraphicsObjectWithHP&) = delete;

		inline GraphicsObjectWithHP(GraphicsObjectWithHP&& other) noexcept :
			GObject<_T>(std::move(other)),
			m_hp(std::move(other.m_hp))
		{
			other.m_hp = {};
		}

		inline virtual ~GraphicsObjectWithHP() noexcept override = default;

		GraphicsObjectWithHP& operator=(const GraphicsObjectWithHP&) = delete;

		inline GraphicsObjectWithHP& operator=(GraphicsObjectWithHP&& other) noexcept
		{
			GObject<_T>::operator=(std::move(other));

			if (this != &other)
				m_hp = std::move(other.m_hp);

			return *this;
		}

		inline virtual void setPos(const PosF& pos) noexcept override
		{
			if (this->m_item)
			{
				this->m_item->setPos(pos.x, pos.y);

				m_hp.setPos({ pos.x + static_cast<float>(this->m_item->boundingRect().width() / 2), pos.y });
			}
		}

		inline virtual void update() noexcept override
		{
			if (this->m_object)
				m_hp.setHP(static_cast<float>(this->m_object->getHealth()) / this->m_object->getMaxHealth());

			GObject<_T>::update();
		}

	protected:
		mutable HP m_hp;
	};

	template<typename _T>
	using GObjectWithHP = GraphicsObjectWithHP<_T>;
} // namespace TowerDefence

#endif /* !__GRAPHICS_OBJECT_WITH_HP_HPP_INCLUDED__ */