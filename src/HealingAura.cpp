#include "HealingAura.hpp"
#include "Enemy.hpp"

namespace TowerDefence
{
	void HealingAura::apply(std::shared_ptr<Enemy> enemy) const
	{
		// TODO: check reload
		enemy->increaseHealth(m_healthAmount);
	}
}