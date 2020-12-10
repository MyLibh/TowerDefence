#ifndef __SPEED_AURA_HPP_INCLUDED__
#define __SPEED_AURA_HPP_INCLUDED__

#include "Aura.hpp"

namespace TowerDefence
{
	class SpeedAura final : public Aura
	{
	private:
		inline void apply(Buffs& buffs) const override { buffs.speed += m_speed; }

	public:
		explicit inline SpeedAura(const float speed, const float r) noexcept :
			Aura(r),
			m_speed(speed)
		{ }

	private:
		float m_speed;
	};
} // namespace TowerDefence

#endif /* !__SPEED_AURA_HPP_INCLUDED__ */