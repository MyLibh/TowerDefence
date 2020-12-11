// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Enemy.hpp"
#include "Aura.hpp"
#include "EnemyManager.hpp"
#include "Castle.hpp"

#include <algorithm>

namespace TowerDefence
{
	void Enemy::attack(std::shared_ptr<ObjectWithHP> object) const noexcept
	{
		if (object && object->isAlive())
			object->decreaseHealth(m_props->damage + m_buffs.damage);
	}

	void Enemy::move(const float dt)
	{
		if (m_route)
		{
			auto speed = m_props->speed + m_buffs.speed;
			if (auto next = m_route.next(); next.x == m_pos.x)
			{
				if (next.y > m_pos.y)
					m_pos.y = std::min(m_pos.y + speed * dt, next.y);
				else
					m_pos.y = std::max(m_pos.y - speed * dt, next.y);

				if (m_pos == next)
					(void)m_route.getNext();
			}
			else if (next.y == m_pos.y)
			{
				if (next.x > m_pos.x)
					m_pos.x = std::min(m_pos.x + speed * dt, next.x);
				else
					m_pos.x = std::max(m_pos.x - speed * dt, next.x);

				if (m_pos == next)
					(void)m_route.getNext();
			}
		}
	}

	void Enemy::regenerate()
	{
		increaseHealth(m_props->regen * m_props->maxHealth + m_buffs.regen);
	}

	void Enemy::useAuras()
	{
		std::for_each(std::begin(m_auras), std::end(m_auras), [&](const auto& aura) { aura->applyEffect(m_pos); });
	}

	void Enemy::update(const float dt)
	{
		static float accumulator{};

		accumulator += dt;

		if (!isAlive())
			return;

		if (m_route && !m_route.isFinished())
			move(dt);
		
		if (accumulator >= Constants::ENEMY_UPDATE_RATIO)
		{
			accumulator = 0.f;

			if (m_route.isFinished() && sEnemyManager)
				attack(std::static_pointer_cast<ObjectWithHP>(sEnemyManager->getCastle()));

			regenerate();
		}

		ClearBuffs(m_buffs);

		useAuras();
	}
}