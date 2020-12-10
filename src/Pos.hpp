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

		inline constexpr Pos() noexcept = default;

		inline constexpr Pos(const _T& x, const _T& y) noexcept :
			x(x),
			y(y)
		{ }

		auto operator<=>(const Pos<_T>& other) const noexcept = default;
	};

	template<typename _T, typename _U>
	inline constexpr auto Distance(const Pos<_T>& pos1, const Pos<_U>& pos2)
	{
		return std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));
	}

	template<typename _T>
	inline constexpr auto Magnitude(const Pos<_T>& pos)
	{
		return Distance(pos, Pos<_T>{});
	}

	template<typename _T>
	inline constexpr auto Normalize(const Pos<_T>& pos)
	{
		const _T magn = Magnitude(pos);
		return Pos<_T>{ pos.x / magn, pos.y / magn };
	}

	template<typename _T>
	int Angle(const Pos<_T>& pos) {
		if (pos.x == 0)
			return (pos.y > 0) ? 90
			: (pos.y == 0) ? 0
			: 270;
		else if (pos.y == 0)
			return (pos.x >= 0) ? 0
			: 180;

		int ret = std::atan(pos.y / pos.x) * (180 / 3.1415);
		if (pos.x < 0 && pos.y < 0)
			ret += 180;
		else if (pos.x < 0)
			ret += 180;
		else if (pos.y < 0)
			ret += 360;

		return ret;
	}

	using PosF = Pos<float>;
	using PosI = Pos<int>;
} // namespace TowerDefence

#endif /* !__POS_HPP_INCLUDED__ */