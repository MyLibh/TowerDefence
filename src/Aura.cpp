#include "Aura.hpp"
#include "GameManager.hpp"
#include "Enemy.hpp"

namespace TowerDefence
{
	void Aura::setGameManager(std::shared_ptr<GameManager> GameManager) noexcept
	{
		Aura::sGameManager = std::move(GameManager);
	}

	void Aura::applyEffect(const PosF& pos) const
	{
		if (Aura::sGameManager)
		{
			for (auto& enemy : Aura::sGameManager->getEnemiesAround(pos, m_r))
				apply(enemy->getBuffs());
		}
	}
} // namespace TowerDefence