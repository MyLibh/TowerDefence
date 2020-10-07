#ifndef __TOWER_HPP_INCLUDED__
#define __TOWER_HPP_INCLUDED__

#include "UpgradableBuilding.hpp"
#include "PropsManager.hpp"

namespace TowerDefence
{
	class Tower final : public UpgradableBuilding
	{
	public:
		inline Tower(const PosF& pos) :
			UpgradableBuilding(pos),
			Building(pos),
			m_shotTimer{},
			m_props(PropsManager::getTowerProps())
		{ }

		inline ~Tower() noexcept override = default;

		inline bool canUpgrade() const override { return PropsManager::canTowerUpgrade(m_lvl + 1); }

		bool upgrade() noexcept override;

		void update(float dt) override;

		_NODISCARD inline int getUpgradePrice() const noexcept override { return m_props.price; }

	private:
		float m_shotTimer;
		TowerProps m_props;
	};
} // namespace TowerDefence

#endif /* !__TOWER_HPP_INCLUDED__ */
