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

		inline virtual ~Building() noexcept = default;

		_NODISCARD inline constexpr auto getX() const noexcept { return m_pos.x; }

		_NODISCARD inline constexpr auto getY() const noexcept { return m_pos.y; }

		_NODISCARD inline constexpr auto getPos() const noexcept { return m_pos; }

	protected:
		PosF m_pos;
	};
} // namespace TowerDefence

#endif /* !__BUILDING_HPP_INCLUDED__ */