#ifndef __RIVER_HPP_INCLUDED__
#define __RIVER_HPP_INCLUDED__

#include "Cell.hpp"

namespace TowerDefence
{
	class River final : public Cell
	{
	public:
		_INLINE_VAR _CONSTEXPR20 River(const PosF& pos) noexcept :
			Cell(pos)
		{ }

		_INLINE_VAR ~River() noexcept override = default;
	};
} // namespace TowerDefence

#endif /* !__RIVER_HPP_INCLUDED__ */