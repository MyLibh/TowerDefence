// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Tower.hpp"
#include "EnemyManager.hpp"

namespace TowerDefence
{
	bool Tower::upgrade() noexcept
	{
		auto res = PropsManager::canTowerUpgrade(m_lvl + 1);
		if (res)
		{
			++m_lvl;
			m_props = PropsManager::getTowerProps(m_lvl);
		}

		return res;
	}

	void Tower::update(const float dt)
	{
		static float accumulator{};

		accumulator += dt;

		if (sEnemyManager && accumulator >= m_props.attackSpeed)
			if (auto target = sEnemyManager->getNearestEnemy(m_pos, m_props.r); target)
			{
				accumulator = 0.f;

				auto bulletPos = m_pos;
				bulletPos.x += .5f;
				bulletPos.y += .5f;
				sEnemyManager->addBullet(m_props.damage, bulletPos, target);
			}
	}
} // namespace TowerDefence