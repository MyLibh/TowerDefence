#ifndef __BUFFS_HPP_INCLUDED__
#define __BUFFS_HPP_INCLUDED__

namespace TowerDefence
{
	struct Buffs
	{
		int regen{};
		int damage{};
		float speed{};
	};

	inline void ClearBuffs(Buffs& buffs) { buffs = {}; }
} // namespace TowerDefence

#endif /* !__BUFFS_HPP_INCLUDED__ */