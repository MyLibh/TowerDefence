#ifndef __CONSTANTS_HPP_INCLUDED__
#define __CONSTANTS_HPP_INCLUDED__

namespace TowerDefence::Constants
{
	inline constexpr auto CASTLE_REPAIR_AMOUNT{ 10 };
	inline constexpr auto CASTLE_UPDATE_RATIO{ 1.f };

	inline constexpr auto TOWER_UPDATE_RATIO{ 1.f };

	inline constexpr auto WALL_MAX_HEALTH{ 100 };

	inline constexpr auto ENEMY_UPDATE_RATIO{ 1.f };

	inline constexpr auto BULLET_MIN_DISTANCE_TO_TARGET{ 1.f };
	inline constexpr auto BULLET_SPEED{ 1.f };
} // namespace TowerDefence::Constants

#endif /* !__CONSTANTS_HPP_INCLUDED__ */