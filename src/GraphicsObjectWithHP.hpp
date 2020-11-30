#ifndef __GRAPHICS_OBJECT_WITH_HP_HPP_INCLUDED__
#define __GRAPHICS_OBJECT_WITH_HP_HPP_INCLUDED__

#include "GraphicsObject.hpp"
#include "HP.hpp"

namespace TowerDefence
{
	template<typename _T>
	class GraphicsObjectWithHP : virtual public GObject<_T>
	{
	public:
		inline GraphicsObjectWithHP() noexcept :
			m_hp()
		{ }

		inline GraphicsObjectWithHP(std::shared_ptr<QGraphicsScene> scene, QPixmap pixmap, std::shared_ptr<_T> object, const PosI& size = { HP::WIDTH, HP::HEIGHT }) :
			GObject<_T>(scene, pixmap, object),
			m_hp(scene, size)
		{ }

		inline virtual ~GraphicsObjectWithHP() noexcept override = default;

		inline virtual void setPos(const PosF& pos) noexcept override
		{
			if (this->m_item)
			{
				this->m_item->setPos(pos.x, pos.y);

				m_hp.setPos({ pos.x + static_cast<float>(this->m_item->boundingRect().width() / 2), pos.y });
			}
		}

		inline void update(const float dx, const float dy) noexcept override
		{
			m_hp.setHP(static_cast<float>(this->m_object->getHealth()) / this->m_object->getMaxHealth());

			GObject<_T>::update(dx, dy);
		}

	protected:
		mutable HP m_hp;
	};

	template<typename _T>
	using GObjectWithHP = GraphicsObjectWithHP<_T>;
} // namespace TowerDefence

#endif /* !__GRAPHICS_OBJECT_WITH_HP_HPP_INCLUDED__ */