// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "EnemyManager.hpp"
#include "Enemy.hpp"

#include <algorithm>

namespace TowerDefence
{
	void EnemyManager::update(const float dt)
	{
		std::for_each(std::begin(m_enemies), std::end(m_enemies), [dt](auto& enemy) { enemy->update(dt); });
	}

	void EnemyManager::add(std::shared_ptr<Enemy> enemy)
	{
		m_enemies.emplace_back(enemy);

		// TODO: add to graphics
	}
} // namespace TowerDefence