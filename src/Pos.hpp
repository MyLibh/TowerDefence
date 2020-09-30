#ifndef __POS_HPP_INCLUDED__
#define __POS_HPP_INCLUDED__

#include <type_traits>

namespace TowerDefence
{
	template<typename _T>
	concept Numeric = std::is_arithmetic_v<_T>;

	template<Numeric _T>
	struct Pos
	{
		_T x;
		_T y;
	};

	using PosF = Pos<float>;
} // namespace TowerDefence

#endif /* !__POS_HPP_INCLUDED__ */