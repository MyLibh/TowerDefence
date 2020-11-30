#ifndef __ENEMY_PROPS_HPP_INCLUDED__
#define __ENEMY_PROPS_HPP_INCLUDED__

#include <iostream>

namespace TowerDefence
{
	struct EnemyProps
	{
		float speed;
		float regen;
		int damage;
		int maxHealth;
	};

	inline std::istream& operator>>(std::istream& istr, EnemyProps& props)
	{
		return istr >> props.speed >> props.regen >> props.damage >> props.maxHealth;
	}
} // namespace TowerDefence

#endif /* !__ENEMY_PROPS_HPP_INCLUDED__ */