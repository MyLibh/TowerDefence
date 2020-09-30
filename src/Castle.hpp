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
		inline Castle(const int startMoney, const PosF pos) :
			UpgradableBuilding(pos),
			BreakableBuilding(pos),
			Building(pos),
			m_money(startMoney),
			m_props(PropsManager::getCastleProps(m_lvl))
		{ }

		inline ~Castle() noexcept override = default;

		bool upgrade() noexcept override;

		void update(const float dt) override;

	private:
		int m_money;
		CastleProps m_props;
	};
}

#endif /* !__CASTLE_HPP_INCLUDED__ */