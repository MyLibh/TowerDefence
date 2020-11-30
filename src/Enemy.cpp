#include "Enemy.hpp"
#include "Aura.hpp"
#include "EnemyManager.hpp"
#include "Castle.hpp"

#include <algorithm>

namespace TowerDefence
{
	void Enemy::attack()
	{
		if (sEnemyManager && sEnemyManager->getCastle())
			sEnemyManager->getCastle()->decreaseHealth(m_props->damage);
	}

	void Enemy::move(const float dt)
	{
		if (m_route)
		{
			if (auto next = m_route.next(); next.x == m_pos.x)
			{
				if (next.y > m_pos.y)
					m_pos.y = std::min(m_pos.y + m_props->speed * dt, next.y);
				else
					m_pos.y = std::max(m_pos.y - m_props->speed * dt, next.y);

				if (m_pos == next)
					(void)m_route.getNext();
			}
			else if (next.y == m_pos.y)
			{
				if (next.x > m_pos.x)
					m_pos.x = std::min(m_pos.x + m_props->speed * dt, next.x);
				else
					m_pos.x = std::max(m_pos.x - m_props->speed * dt, next.x);

				if (m_pos == next)
					(void)m_route.getNext();
			}
		}
	}

	void Enemy::regenerate()
	{
		increaseHealth(m_props->regen * m_props->maxHealth);
	}

	void Enemy::useAuras()
	{
		std::for_each(std::begin(m_auras), std::end(m_auras), [&](const auto& aura) { aura->applyEffect(m_pos); });
	}

	void Enemy::update(const float dt)
	{
		static float accumulator{};

		accumulator += dt;

		if (m_route && !m_route.isFinished())
			move(dt);
		else if (accumulator >= 1.f)
		{
			accumulator -= 1.f;

			if (m_route.isFinished())
				attack();

			regenerate();

			useAuras();
		}
	}
}