#ifndef __CASTLE_PROPS_HPP_INCLUDED__
#define __CASTLE_PROPS_HPP_INCLUDED__

#include <iostream>

namespace TowerDefence
{
	struct CastleProps
	{
		int profit;
		int maxHealth;
		float repairSpeed;
		int price;
	};

	inline std::istream& operator>>(std::istream& istr, CastleProps& props)
	{
		return istr >> props.profit >> props.maxHealth >> props.repairSpeed >> props.price;
	}
} // namespace TowerDefence

#endif /* !__CASTLE_PROPS_HPP_INCLUDED__ */