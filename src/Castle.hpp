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
		inline static constexpr auto REPAIR_AMOUNT{ 1 };

	public:
		inline Castle(const int startMoney, const PosF& pos) :
			UpgradableBuilding(pos),
			BreakableBuilding(pos),
			Building(pos),
			m_money(startMoney),
			m_props(PropsManager::getCastleProps(m_lvl))
		{ }

		inline ~Castle() noexcept override = default;

		bool canUpgrade() const override { return PropsManager::canCastleUpgrade(m_lvl + 1); }

		bool upgrade() noexcept override;

		void update(const float dt) override;

		_NODISCARD inline int getUpgradePrice() const noexcept override { return m_props.price; }

		_NODISCARD inline int getMaxHealth() const noexcept override { return m_props.maxHealth; }

		_NODISCARD inline constexpr auto getMoney() const noexcept { return m_money; }

		void withdraw(const int amount);

		inline bool hasMoney(const int amount) const noexcept { return m_money >= amount; }

	private:
		int m_money;
		CastleProps m_props;
	};
}

#endif /* !__CASTLE_HPP_INCLUDED__ */