#ifndef __AIR_ENEMY_HPP_INCLUDED__
#define __AIR_ENEMY_HPP_INCLUDED__

#include "Enemy.hpp"

namespace TowerDefence
{
	class AirEnemy : public Enemy
	{
	public:
		inline AirEnemy() noexcept = default;

		inline ~AirEnemy() noexcept override = default;

		inline int getMaxHealth() const noexcept override { return 50; }
	};
} // namespace TowerDefence

#endif /* !__AIR_ENEMY_HPP_INCLUDED__ */