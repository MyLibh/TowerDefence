#ifndef __HEALING_AURA_HPP_INCLUDED__
#define __HEALING_AURA_HPP_INCLUDED__

#include "Aura.hpp"

namespace TowerDefence
{
	class HealingAura final : public Aura
	{
	private:
		void apply(std::shared_ptr<Enemy> enemy) const override;

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