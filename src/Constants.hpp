#ifndef __CONSTANTS_HPP_INCLUDED__
#define __CONSTANTS_HPP_INCLUDED__

namespace TowerDefence::Constants
{
	inline constexpr auto DT{ .1f };

	inline constexpr auto REPAIR_COST{ 100 };

	inline constexpr auto CASTLE_REGEN_AMOUNT{ 10 };
	inline constexpr auto CASTLE_UPDATE_RATIO{ 1.f };

	inline constexpr auto TOWER_UPDATE_RATIO{ 1.f };

	inline constexpr auto WALL_COST{ 100 };
	inline constexpr auto WALL_MAX_HEALTH{ 100 };

	inline constexpr auto ENEMY_UPDATE_RATIO{ 1.f };

	inline constexpr auto BULLET_MIN_DISTANCE_TO_TARGET{ .8f };
	inline constexpr auto BULLET_SPEED{ 1.f };

	inline constexpr auto ENEMIES_Z_LVL{ 1 };
	inline constexpr auto BULLETS_Z_LVL{ 2 };
	inline constexpr auto GUI_Z_LVL{ 3 };

	inline constexpr auto PARTICLES_NUM{ 5LLU };
} // namespace TowerDefence::Constants

#endif /* !__CONSTANTS_HPP_INCLUDED__ */