#ifndef __HEALING_AURA_HPP_INCLUDED__
#define __HEALING_AURA_HPP_INCLUDED__

#include "Aura.hpp"

namespace TowerDefence
{
	class HealingAura final : public Aura
	{
	private:
		void apply(std::shared_ptr<Enemy> enemy) const override;

	private:
		float m_healthAmount;

	};
} // namesapce TowerDefence

#endif /* !__HEALING_AURA_HPP_INCLUDED__ */