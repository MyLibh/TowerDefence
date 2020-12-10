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

	void Tower::update(float dt)
	{
		m_shotTimer += dt;

		if (sEnemyManager && m_shotTimer >= Constants::TOWER_UPDATE_RATIO)
			if (auto target = sEnemyManager->getNearestEnemy(m_pos, m_props.r); target)
			{
				m_shotTimer = 0.f;

				sEnemyManager->addBullet(m_props.damage, m_pos, target);
			}
	}
} // namespace TowerDefence