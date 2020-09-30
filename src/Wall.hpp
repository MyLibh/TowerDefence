#ifndef __WALL_HPP_INCLUDED__
#define __WALL_HPP_INCLUDED__

#include "BreakableBuilding.hpp"

namespace TowerDefence
{
	class Wall final : public BreakableBuilding
	{
	public:
		inline Wall(const PosF pos) noexcept :
			BreakableBuilding(pos)
		{ }
	};
} // namespace TowerDefence

#endif /* !__WALL_HPP_INCLUDED__ */