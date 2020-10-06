#ifndef __BREAKABLE_BUILDING_HPP_INCLUDED__
#define __BREAKABLE_BUILDING_HPP_INCLUDED__

#include "Building.hpp"

namespace TowerDefence
{
	class BreakableBuilding : virtual public Building
	{
	public:
		_INLINE_VAR BreakableBuilding(const PosF& pos, const int health = 0) noexcept :
			Building(pos),
			m_health(health)
		{ }

		_INLINE_VAR virtual ~BreakableBuilding() noexcept override = default;

		_NODISCARD _INLINE_VAR _CONSTEXPR20 auto getHealth() const noexcept { return m_health; }

		virtual int getMaxHealth() const noexcept = 0;

		void decreaseHealth(const int amount)
		{
			m_health -= amount;
			if (m_health < 0)
				m_health = 0;
		}

	protected:
		int m_health;
	};
} // namespace TowerDefence

#endif /* !__BREAKABLE_BUILDING_HPP_INCLUDED__ */