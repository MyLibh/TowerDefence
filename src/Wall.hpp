#ifndef __WALL_HPP_INCLUDED__
#define __WALL_HPP_INCLUDED__

#include "BreakableBuilding.hpp"

namespace TowerDefence
{
	class Wall final : public BreakableBuilding
	{
	private:
		_INLINE_VAR static _CONSTEXPR20 auto MAX_HEALTH{ 100 };

	public:
		_INLINE_VAR Wall(const PosF& pos) noexcept :
			BreakableBuilding(pos)
		{ }

		_INLINE_VAR ~Wall() noexcept override = default;

		_NODISCARD _INLINE_VAR int getMaxHealth() const noexcept override { return Wall::MAX_HEALTH; }
	};
} // namespace TowerDefence

#endif /* !__WALL_HPP_INCLUDED__ */