#ifndef __UPGRADABLE_BUILDING_HPP_INCLUDED__
#define __UPGRADABLE_BUILDING_HPP_INCLUDED__

#include "Building.hpp"

namespace TowerDefence
{
	class UpgradableBuilding : virtual public Building
	{
	public:
		_INLINE_VAR UpgradableBuilding(const PosF& pos, const int lvl = 1) noexcept :
			Building(pos),
			m_lvl(lvl)
		{ }

		_INLINE_VAR virtual ~UpgradableBuilding() noexcept override = default;

		virtual bool canUpgrade() const = 0;

		virtual bool upgrade() noexcept = 0;

	protected:
		int m_lvl;
	};
}

#endif /* !__UPGRADABLE_BUILDING_HPP_INCLUDED__ */