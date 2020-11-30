// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Castle.hpp"
#include "PropsManager.hpp"

#include <cmath>

namespace TowerDefence
{
	bool Castle::upgrade() noexcept
	{
		auto res = PropsManager::canCastleUpgrade(m_lvl + 1);
		if (res)
		{
			++m_lvl;
			m_props = PropsManager::getCastleProps(m_lvl);
		}

		return res;
	}

	void Castle::update(const float dt)
	{
		static float accumulator{};

		accumulator += dt;
		if (accumulator >= 1.f)
		{
			accumulator -= 1.f;

			increaseHealth(dt * REPAIR_AMOUNT);
		}

		m_money += m_props.profit;
	}

	void Castle::withdraw(const int amount)
	{
		if (m_money < amount)
			throw std::runtime_error("Not enought money");

		m_money -= amount;
	}
}