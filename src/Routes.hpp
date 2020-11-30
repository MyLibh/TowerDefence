#ifndef __ROUTES_HPP_INCLUDED__
#define __ROUTES_HPP_INCLUDED__

#include <memory>

namespace TowerDefence
{
	class Route;

	struct Routes
	{
		std::shared_ptr<Route> light;
		std::shared_ptr<Route> heavy;
		std::shared_ptr<Route> air;
	};

	enum class RouteType
	{
		Air,
		Heavy,
		Light
	};
} // namespace TowerDefence

#endif /* !__ROUTES_hPP_INCLUDED__*/