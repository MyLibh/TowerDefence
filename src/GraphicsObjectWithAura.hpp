#ifndef __GRAPHICS_OBJECT_WITH_AURA_HPP_INCLUDED__
#define __GRAPHICS_OBJECT_WITH_AURA_HPP_INCLUDED__

#include "GraphicsObject.hpp"
#include "GraphicsAura.hpp"

namespace TowerDefence
{
	template<typename _T>
	class GraphicsObjectWithAura : virtual public GObject<_T>
	{
	public:
		inline GraphicsObjectWithAura() noexcept :
			m_aura()
		{ }

		inline GraphicsObjectWithAura(std::shared_ptr<QGraphicsScene> scene, QPixmap pixmap, std::shared_ptr<_T> object, const float rx, const float ry) :
			GraphicsObject(scene, pixmap, object),
			m_aura(scene, rx, ry)
		{ }

		inline virtual ~GraphicsObjectWithAura() noexcept override = default;

		inline virtual void setPos(const PosF& pos) noexcept override
		{
			if (m_item)
			{
				m_item->setPos(pos.x, pos.y);

				m_aura.setPos({ pos.x + static_cast<float>(m_item->boundingRect().width() / 2), pos.y });
			}
		}

	protected:
		GraphicsAura m_aura;
	};

	template<typename _T>
	using GObjectWithAura = GraphicsObjectWithAura<_T>;
} // namespace TowerDefence

#endif /* !__GRAPHICS_OBJECT_WITH_AURA_HPP_INCLUDED__ */