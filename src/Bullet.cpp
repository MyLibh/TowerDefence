// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Bullet.hpp"
#include "Enemy.hpp"
#include "ObjectWithHP.hpp"

namespace TowerDefence
{
	void Bullet::update(const float dt)
	{
		if (!m_isAlive)
			return;

		if (!m_target->isAlive())
		{
			// TODO: Retarget

			m_isAlive = false;

			return;
		}

		auto targetPos = m_target->getPos();
		targetPos.x += .5f;
		targetPos.y += .5f;
		if (auto dist = Distance(m_pos, targetPos); dist < Constants::BULLET_MIN_DISTANCE_TO_TARGET)
		{
			std::dynamic_pointer_cast<ObjectWithHP>(m_target)->decreaseHealth(m_power);

			m_isAlive = false;

			return;
		}

		PosF v = PosF{ targetPos.x - m_pos.x, targetPos.y - m_pos.y };
		m_pos.x += Constants::BULLET_SPEED * v.x * dt;
		m_pos.y += Constants::BULLET_SPEED * v.y * dt;
	}
} // namespace TowerDefence