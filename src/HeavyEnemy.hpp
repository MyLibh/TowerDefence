#ifndef __HEAVY_ENEMY_HPP_INCLUDED__
#define __HEAVY_ENEMY_HPP_INCLUDED__

#include "Enemy.hpp"

namespace TowerDefence
{
	class HeavyEnemy : public Enemy
	{
	public:
		inline HeavyEnemy(std::shared_ptr<EnemyProps> props) noexcept :
			Enemy(props)
		{}

		inline ~HeavyEnemy() noexcept override = default;

		void update(const float dt) override final;
	};
} // namespace TowerDefence

#endif /* !__HEAVY_ENEMY_HPP_INCLUDED__ */