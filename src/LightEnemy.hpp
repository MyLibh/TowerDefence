#ifndef __LIGHT_ENEMY_HPP_INCLUDED__
#define __LIGHT_ENEMY_HPP_INCLUDED__

#include "Enemy.hpp"

namespace TowerDefence
{
	class LightEnemy : public Enemy
	{
	public:
		inline LightEnemy(std::shared_ptr<EnemyProps> props, std::vector<std::shared_ptr<Aura>>&& auras) noexcept :
			Enemy(props, std::move(auras))
		{}

		inline ~LightEnemy() noexcept override = default;
	};
} // namespace TowerDefence

#endif /* !__LIGHT_ENEMY_HPP_INCLUDED__ */