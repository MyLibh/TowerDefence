// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Lair.hpp"
#include "Enemy.hpp"
#include "EnemyManager.hpp"

namespace TowerDefence
{
	void Lair::spawn(std::shared_ptr<Enemy> enemy)
	{
		enemy->setPos(m_pos);
		sEnemyManager->add(enemy, this);
	}

	void Lair::update(float dt)
	{
		spawn();

		m_timer += dt;
	}

	void Lair::spawn()
	{
		auto [begin, end] = m_shedule.equal_range(std::floor(m_timer));
		for (auto it = begin; it != end; ++it)
			spawn(it->second);
	}
} // namespace TowerDefence