#ifndef __TOWER_HPP_INCLUDED__
#define __TOWER_HPP_INCLUDED__

#include "UpgradableBuilding.hpp"
#include "PropsManager.hpp"

namespace TowerDefence
{
	class Tower final : public UpgradableBuilding
	{
	public:
		~Tower() noexcept override = default;

		bool canUpgrade() const override { return PropsManager::canTowerUpgrade(m_lvl + 1); }

		bool upgrade() noexcept override;

		void update(float dt) override;

	private:
		float m_shotTimer;
	};
} // namespace TowerDefence

#endif /* !__TOWER_HPP_INCLUDED__ */
