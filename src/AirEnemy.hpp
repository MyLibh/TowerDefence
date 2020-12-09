#ifndef __AIR_ENEMY_HPP_INCLUDED__
#define __AIR_ENEMY_HPP_INCLUDED__

#include "Enemy.hpp"

namespace TowerDefence
{
	class AirEnemy : public Enemy
	{
	public:
		inline AirEnemy(std::shared_ptr<EnemyProps> props, std::vector<std::shared_ptr<Aura>>&& auras) noexcept :
			Enemy(props, std::move(auras))
		{}

		inline ~AirEnemy() noexcept override = default;
	};
} // namespace TowerDefence

#endif /* !__AIR_ENEMY_HPP_INCLUDED__ */