#ifndef __AIR_ENEMY_HPP_INCLUDED__
#define __AIR_ENEMY_HPP_INCLUDED__

#include "Enemy.hpp"

namespace TowerDefence
{
	class AirEnemy : public Enemy
	{
	public:
		inline AirEnemy(std::shared_ptr<EnemyProps> props) noexcept :
			Enemy(props)
		{}

		inline ~AirEnemy() noexcept override = default;
	};
} // namespace TowerDefence

#endif /* !__AIR_ENEMY_HPP_INCLUDED__ */