#ifndef __CASTLE_HPP_INCLUDED__
#define __CASTLE_HPP_INCLUDED__

#include "UpgradableBuilding.hpp"
#include "BreakableBuilding.hpp"
#include "PropsManager.hpp"

namespace TowerDefence
{
	class Castle final : public UpgradableBuilding, public BreakableBuilding
	{
	private:
		_INLINE_VAR static _CONSTEXPR20 auto REPAIR_AMOUNT{ 1 };

	public:
		_INLINE_VAR Castle(const int startMoney, const PosF& pos) :
			UpgradableBuilding(pos),
			BreakableBuilding(pos),
			Building(pos),
			m_money(startMoney),
			m_props(PropsManager::getCastleProps(m_lvl))
		{ }

		_INLINE_VAR ~Castle() noexcept override = default;

		bool canUpgrade() const override { return PropsManager::canCastleUpgrade(m_lvl + 1); }

		bool upgrade() noexcept override;

		void update(const float dt) override;

		_NODISCARD _INLINE_VAR _CONSTEXPR20 auto getMoney() const noexcept { return m_money; }

	private:
		int m_money;
		CastleProps m_props;
	};
}

#endif /* !__CASTLE_HPP_INCLUDED__ */