#ifndef __BUILDING_HPP_INCLUDED__
#define __BUILDING_HPP_INCLUDED__

#include "Entity.hpp"
#include "Pos.hpp"

namespace TowerDefence
{
	class Building : public Entity
	{
	public:
		constexpr Building(const PosF& pos) noexcept :
			Entity(),
			m_pos(pos)
		{ }

		_INLINE_VAR virtual ~Building() noexcept = default;

		_NODISCARD _INLINE_VAR _CONSTEXPR20 auto getX() const noexcept { return m_pos.x; }

		_NODISCARD _INLINE_VAR _CONSTEXPR20 auto getY() const noexcept { return m_pos.y; }

		_NODISCARD _INLINE_VAR _CONSTEXPR20 auto getPos() const noexcept { return m_pos; }

	protected:
		PosF m_pos;
	};
} // namespace TowerDefence

#endif /* !__BUILDING_HPP_INCLUDED__ */