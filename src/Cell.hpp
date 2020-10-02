#ifndef __CELL_HPP_INCLUDED__
#define __CELL_HPP_INCLUDED__

#include "Pos.hpp"

namespace TowerDefence
{
	class Cell
	{
	public:
		_INLINE_VAR _CONSTEXPR20 Cell(const PosF& pos) noexcept :
			m_pos(pos)
		{ }

		virtual ~Cell() noexcept = default;

		_NODISCARD _INLINE_VAR _CONSTEXPR20 auto getX() const noexcept { return m_pos.x; }

		_NODISCARD _INLINE_VAR _CONSTEXPR20 auto getY() const noexcept { return m_pos.y; }

		_NODISCARD _INLINE_VAR _CONSTEXPR20 auto getPos() const noexcept { return m_pos; }

	protected:
		PosF m_pos;
	};
} // namespace TowerDefence

#endif /* !__CELL_HPP_INCLUDED__ */