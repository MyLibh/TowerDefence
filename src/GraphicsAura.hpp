#ifndef __GRAPHICS_AURA_HPP_INCLUDED__
#define __GRAPHICS_AURA_HPP_INCLUDED__

#include "Pos.hpp"

#include <memory>

class QGraphicsScene;
class QGraphicsEllipseItem;

namespace TowerDefence
{
	class GraphicsAura final
	{
	public:
		inline constexpr GraphicsAura() noexcept :
			m_rx{},
			m_ry{},
			m_item{}
		{ }

		GraphicsAura(std::shared_ptr<QGraphicsScene> scene, const float rx, const float ry);

		void setPos(const PosF& pos) noexcept;

	private:
		float m_rx;
		float m_ry;
		QGraphicsEllipseItem* m_item;
	};
} // namespace TowerDefence

#endif /* !__GRAPHICS_AURA_HPP_INCLUDED__ */