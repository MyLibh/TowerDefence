#ifndef __LIGHT_ENEMY_HPP_INCLUDED__
#define __LIGHT_ENEMY_HPP_INCLUDED__

#include "Enemy.hpp"

namespace TowerDefence
{
	class LightEnemy : public Enemy
	{
	public:
		inline LightEnemy(std::shared_ptr<EnemyProps> props) noexcept :
			Enemy(props)
		{}

		inline ~LightEnemy() noexcept override = default;

		inline int getMaxHealth() const noexcept override { return 50; }
	};
} // namespace TowerDefence

#endif /* !__LIGHT_ENEMY_HPP_INCLUDED__ */