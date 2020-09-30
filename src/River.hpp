#ifndef __RIVER_HPP_INCLUDED__
#define __RIVER_HPP_INCLUDED__

#include "Cell.hpp"

namespace TowerDefence
{
	class River final : public Cell
	{
	public:
		inline constexpr River(const PosF& pos) noexcept :
			Cell(pos)
		{ }

		inline ~River() noexcept override = default;
	};
} // namespace TowerDefence

#endif /* !__RIVER_HPP_INCLUDED__ */