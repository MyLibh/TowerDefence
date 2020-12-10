#ifndef __WALL_HPP_INCLUDED__
#define __WALL_HPP_INCLUDED__

#include "Building.hpp"
#include "ObjectWithHP.hpp"

namespace TowerDefence
{
	class Wall final : public Building, public ObjectWithHP
	{
	public:
		inline Wall(const PosF& pos) noexcept :
			Building(pos),
			ObjectWithHP(Constants::WALL_MAX_HEALTH)
		{ }

		inline ~Wall() noexcept override = default;

		inline void update(const float dt) { }

		[[nodiscard]] inline int getMaxHealth() const noexcept override { return Constants::WALL_MAX_HEALTH; }
	};
} // namespace TowerDefence

#endif /* !__WALL_HPP_INCLUDED__ */