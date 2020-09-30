#ifndef __TOWER_HPP_INCLUDED__
#define __TOWER_HPP_INCLUDED__

#include "UpgradableBuilding.hpp"

namespace TowerDefence
{
	class Tower final : public UpgradableBuilding
	{
	public:
		~Tower() noexcept override = default;

		void update(float dt) override;

		bool upgrade() noexcept override;

	private:
		float m_shotTimer;
	};
} // namespace TowerDefence

#endif /* !__TOWER_HPP_INCLUDED__ */
