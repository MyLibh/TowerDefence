#ifndef __HEAVY_ENEMY_HPP_INCLUDED__
#define __HEAVY_ENEMY_HPP_INCLUDED__

#include "Enemy.hpp"

namespace TowerDefence
{
	class HeavyEnemy : public Enemy
	{
	public:
		inline HeavyEnemy(std::shared_ptr<EnemyProps> props, std::vector<std::shared_ptr<Aura>>&& auras) noexcept :
			Enemy(props, std::move(auras))
		{}

		inline ~HeavyEnemy() noexcept override = default;

		void update(const float dt) override final;
	};
} // namespace TowerDefence

#endif /* !__HEAVY_ENEMY_HPP_INCLUDED__ */