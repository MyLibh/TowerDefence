#ifndef __CELL_HPP_INCLUDED__
#define __CELL_HPP_INCLUDED__

#include "Pos.hpp"

namespace TowerDefence
{
	class Cell
	{
	public:
		inline constexpr Cell(const PosF& pos) noexcept :
			m_pos(pos)
		{ }

		virtual ~Cell() noexcept = default;

		[[nodiscard]] inline constexpr auto getX() const noexcept { return m_pos.x; }

		[[nodiscard]] inline constexpr auto getY() const noexcept { return m_pos.y; }

		[[nodiscard]] inline constexpr auto getPos() const noexcept { return m_pos; }

	protected:
		PosF m_pos;
	};
} // namespace TowerDefence

#endif /* !__CELL_HPP_INCLUDED__ */