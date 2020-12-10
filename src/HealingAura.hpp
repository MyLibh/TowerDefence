#ifndef __HEALING_AURA_HPP_INCLUDED__
#define __HEALING_AURA_HPP_INCLUDED__

#include "Aura.hpp"

namespace TowerDefence
{
	class HealingAura final : public Aura
	{
	private:
		inline void apply(Buffs& buffs) const override { buffs.regen += m_heal; }

	public:
		explicit inline HealingAura(const int heal, const float r) noexcept :
			Aura(r),
			m_heal(heal)
		{ }

	private:
		int m_heal;
	};
} // namesapce TowerDefence

#endif /* !__HEALING_AURA_HPP_INCLUDED__ */