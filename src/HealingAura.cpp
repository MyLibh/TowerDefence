// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "HealingAura.hpp"
#include "Enemy.hpp"

namespace TowerDefence
{
	void HealingAura::apply(std::shared_ptr<Enemy> enemy) const
	{
		enemy->increaseHealth(m_heal);
	}
}