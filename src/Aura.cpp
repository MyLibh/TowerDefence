#include "Aura.hpp"
#include "EnemyManager.hpp"
#include "Enemy.hpp"

namespace TowerDefence
{
	void Aura::setEnemyManager(std::shared_ptr<EnemyManager> enemyManager) noexcept
	{
		Aura::sEnemyManager = std::move(enemyManager);
	}

	void Aura::applyEffect(const PosF& pos) const
	{
		if (Aura::sEnemyManager)
		{
			for (auto& enemy : Aura::sEnemyManager->getEnemiesAround(pos, m_r))
				apply(enemy->getBuffs());
		}
	}
} // namespace TowerDefence