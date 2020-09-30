// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Lair.hpp"
#include "Enemy.hpp"

namespace TowerDefence
{
	void Lair::spawn(std::shared_ptr<Enemy> enemy)
	{
		// enemy->setPos(m_pos);
		m_enemies->insert(enemy);
	}

	void Lair::update(float dt)
	{
		spawn();

		m_timer += dt;
	}

	void Lair::spawn()
	{
		auto [begin, end] = m_shedule.equal_range(m_timer);
		for (auto it = begin; it != end; ++it)
			spawn(it->second);
	}
} // namespace TowerDefence