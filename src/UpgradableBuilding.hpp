#ifndef __UPGRADABLE_BUILDING_HPP_INCLUDED__
#define __UPGRADABLE_BUILDING_HPP_INCLUDED__

#include "Building.hpp"

namespace TowerDefence
{
	class UpgradableBuilding : virtual public Building
	{
	public:
		inline UpgradableBuilding(const PosF pos, const int lvl = 1) noexcept :
			Building(pos),
			m_lvl(lvl)
		{ }

		inline virtual ~UpgradableBuilding() noexcept override = default;

		virtual bool upgrade() noexcept = 0;

	protected:
		int m_lvl;
	};
}

#endif /* !__UPGRADABLE_BUILDING_HPP_INCLUDED__ */