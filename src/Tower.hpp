#ifndef __TOWER_HPP_INCLUDED__
#define __TOWER_HPP_INCLUDED__

#include "UpgradableBuilding.hpp"
#include "PropsManager.hpp"

namespace TowerDefence
{
	class EnemyManager;
	class Tower final : public UpgradableBuilding
	{
	protected:
		inline static std::shared_ptr<EnemyManager> sEnemyManager;

	public:
		inline static void setEnemyManager(std::shared_ptr<EnemyManager> enemyManager) noexcept { sEnemyManager = std::move(enemyManager); }

	public:
		inline Tower(const PosF& pos) :
			UpgradableBuilding(pos),
			Building(pos),
			m_props(PropsManager::getTowerProps())
		{ }

		inline ~Tower() noexcept override = default;

		inline bool canUpgrade() const override { return PropsManager::canTowerUpgrade(m_lvl + 1); }

		bool upgrade() noexcept override;

		void update(const float dt) override;

		[[nodiscard]] inline int getUpgradePrice() const noexcept override { return m_props.price; }

		[[nodiscard]] inline auto getR() const noexcept { return m_props.r; }

	private:
		TowerProps m_props;
	};
} // namespace TowerDefence

#endif /* !__TOWER_HPP_INCLUDED__ */
