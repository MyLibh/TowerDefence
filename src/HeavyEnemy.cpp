// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "HeavyEnemy.hpp"
#include "GameManager.hpp"
#include "Castle.hpp"

namespace TowerDefence
{
	void HeavyEnemy::update(const float dt)
	{
		static float accumulator{};

		accumulator += dt;

		if (m_route && !m_route.isFinished())
		{
			if (auto target = sGameManager->getTargetAt(m_pos); target && target->isAlive())
				attack(target);
			else
				move(dt);
		}
		
		if (accumulator >= Constants::ENEMY_UPDATE_RATIO)
		{
			accumulator = 0.f;

			if (m_route.isFinished() && sGameManager)
				attack(std::static_pointer_cast<ObjectWithHP>(sGameManager->getCastle()));

			regenerate();
		}

		ClearBuffs(m_buffs);

		useAuras();
	}
} // namespace TowerDefence
