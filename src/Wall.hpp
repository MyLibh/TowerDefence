#ifndef __WALL_HPP_INCLUDED__
#define __WALL_HPP_INCLUDED__

#include "Building.hpp"
#include "ObjectWithHP.hpp"

namespace TowerDefence
{
	class Wall final : public Building, public ObjectWithHP
	{
	private:
		inline static constexpr auto MAX_HEALTH{ 100 };

	public:
		inline Wall(const PosF& pos) noexcept :
			Building(pos),
			ObjectWithHP(Wall::MAX_HEALTH)
		{ }

		inline ~Wall() noexcept override = default;

		[[nodiscard]] inline int getMaxHealth() const noexcept override { return Wall::MAX_HEALTH; }
	};
} // namespace TowerDefence

#endif /* !__WALL_HPP_INCLUDED__ */