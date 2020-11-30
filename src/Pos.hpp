#ifndef __POS_HPP_INCLUDED__
#define __POS_HPP_INCLUDED__

#include <type_traits>
#include <compare>
#include <cmath>

namespace TowerDefence
{
	template<typename _T>
	concept Numeric = std::is_arithmetic_v<_T>;

	template<Numeric _T>
	struct Pos
	{
		_T x;
		_T y;

		auto operator<=>(const Pos<_T>& other) const noexcept = default;
	};

	template<typename _T, typename _U>
	inline constexpr auto Distance(const Pos<_T>& pos1, const Pos<_U>& pos2)
	{
		return std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));
	}

	using PosF = Pos<float>;
	using PosI = Pos<int>;
} // namespace TowerDefence

#endif /* !__POS_HPP_INCLUDED__ */