// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Tower.hpp"

bool TowerDefence::Tower::upgrade() noexcept
{
	auto res = PropsManager::canTowerUpgrade(m_lvl + 1);
	if (res)
	{
		++m_lvl;
		m_props = PropsManager::getTowerProps(m_lvl);
	}

	return res;
}

void TowerDefence::Tower::update(float dt)
{
	m_shotTimer += dt;

	if (m_shotTimer > 0)
	{
		// Try attack

		m_shotTimer = 0.f;
	}
}
