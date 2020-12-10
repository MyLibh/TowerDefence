#ifndef __DAMAGE_AURA_HPP_INCLUDED__
#define __DAMAGE_AURA_HPP_INCLUDED__

#include "Aura.hpp"

namespace TowerDefence
{
	class DamageAura final : public Aura
	{
	private:
		inline void apply(Buffs& buffs) const override { buffs.damage += m_damage; }

	public:
		explicit inline DamageAura(const int damage, const float r) noexcept :
			Aura(r),
			m_damage(damage)
		{ }

	private:
		int m_damage;
	};
} // namesapce TowerDefence

#endif /* !__DAMAGE_AURA_HPP_INCLUDED__ */