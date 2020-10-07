#ifndef __MOUNTAIN_HPP_INCLUDED__
#define __MOUNTAIN_HPP_INCLUDED__

#include "Cell.hpp"

namespace TowerDefence
{
	class Mountain final : public Cell
	{
	public:
		inline constexpr Mountain(const PosF& pos) noexcept :
			Cell(pos)
		{ }

		inline~Mountain() noexcept override = default;
	};
} // namespace TowerDefence

#endif /* !__MOUNTAIN_HPP_INCLUDED__ */