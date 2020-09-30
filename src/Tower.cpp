#include "Tower.hpp"

void TowerDefence::Tower::update(float dt)
{
	m_shotTimer += dt;

	if (m_shotTimer > 0)
	{
		// Try attack

		m_shotTimer = 0.f;
	}
}
