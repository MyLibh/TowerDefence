#ifndef __BREAKABLE_BUILDING_HPP_INCLUDED__
#define __BREAKABLE_BUILDING_HPP_INCLUDED__

#include "Building.hpp"
#include "ObjectWithHP.hpp"

namespace TowerDefence
{
	class BreakableBuilding : virtual public Building, public ObjectWithHP
	{
	public:
		inline explicit BreakableBuilding(const PosF& pos, const int health = 0) noexcept :
			Building(pos),
			ObjectWithHP(health)
		{ }

		inline virtual ~BreakableBuilding() noexcept override = default;
	};
} // namespace TowerDefence

#endif /* !__BREAKABLE_BUILDING_HPP_INCLUDED__ */