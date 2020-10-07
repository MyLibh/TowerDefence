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
			GraphicsObject(scene, pixmap, object),
			m_hp(scene, size)
		{ }

		inline virtual ~GraphicsObjectWithHP() noexcept override = default;

		inline virtual void setPos(const PosF& pos) noexcept override
		{
			if (m_item)
			{
				m_item->setPos(pos.x, pos.y);

				m_hp.setPos({ pos.x + static_cast<float>(m_item->boundingRect().width() / 2), pos.y });
			}
		}

		inline void draw() const
		{
			m_hp.setHP(static_cast<float>(m_object->getHealth()) / m_object->getMaxHealth());
		}

	protected:
		mutable HP m_hp;
	};

	template<typename _T>
	using GObjectWithHP = GraphicsObjectWithHP<_T>;
} // namespace TowerDefence

#endif /* !__GRAPHICS_OBJECT_WITH_HP_HPP_INCLUDED__ */