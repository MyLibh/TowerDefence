#ifndef __WALL_HPP_INCLUDED__
#define __WALL_HPP_INCLUDED__

#include "BreakableBuilding.hpp"

namespace TowerDefence
{
	class Wall final : public BreakableBuilding
	{
	private:
		inline static constexpr auto MAX_HEALTH{ 100 };

	public:
		inline Wall(const PosF& pos) noexcept :
			BreakableBuilding(pos)
		{ }

		inline ~Wall() noexcept override = default;

		_NODISCARD inline int getMaxHealth() const noexcept override { return Wall::MAX_HEALTH; }
	};
} // namespace TowerDefence

#endif /* !__WALL_HPP_INCLUDED__ */