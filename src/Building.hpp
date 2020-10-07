#ifndef __BUILDING_HPP_INCLUDED__
#define __BUILDING_HPP_INCLUDED__

#include "Entity.hpp"

namespace TowerDefence
{
	class Building : public Entity
	{
	public:
		inline explicit constexpr Building(const PosF& pos) noexcept :
			Entity(pos)
		{ }

		inline virtual ~Building() noexcept override = default;
	};
} // namespace TowerDefence

#endif /* !__BUILDING_HPP_INCLUDED__ */