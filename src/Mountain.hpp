#ifndef __MOUNTAIN_HPP_INCLUDED__
#define __MOUNTAIN_HPP_INCLUDED__

#include "Cell.hpp"

namespace TowerDefence
{
	class Mountain final : public Cell
	{
	public:
		_INLINE_VAR _CONSTEXPR20 Mountain(const PosF& pos) noexcept :
			Cell(pos)
		{ }

		_INLINE_VAR~Mountain() noexcept override = default;
	};
} // namespace TowerDefence

#endif /* !__MOUNTAIN_HPP_INCLUDED__ */