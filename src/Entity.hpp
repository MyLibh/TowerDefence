#ifndef __ENTITY_HPP_INCLUDED__
#define __ENTITY_HPP_INCLUDED__

#include "Pos.hpp"

namespace TowerDefence
{
	class Entity
	{
	public:
		inline constexpr Entity() noexcept :
			m_pos{}
		{ }

		inline explicit constexpr Entity(const PosF& pos) noexcept :
			m_pos(pos)
		{ }

		inline virtual ~Entity() noexcept = default;

		[[nodiscard]] inline constexpr auto getX() const noexcept { return m_pos.x; }

		[[nodiscard]] inline constexpr auto getY() const noexcept { return m_pos.y; }

		[[nodiscard]] inline constexpr auto getPos() const noexcept { return m_pos; }

		inline constexpr void setPos(const PosF& pos) noexcept { m_pos = pos; }

		virtual void update(const float dt) = 0;
		
	protected:
		PosF m_pos;
	};
} // namespace TowerDefence

#endif /* !__ENTITY_HPP_INCLUDED__ */