#ifndef __ENEMY_MANAGER_HPP_INCLUDED__
#define __ENEMY_MANAGER_HPP_INCLUDED__

#include "Pos.hpp"
#include "Routes.hpp"

#include <vector>
#include <memory>
#include <map>

namespace TowerDefence
{
	class Enemy;
	class Graphics;
	class Castle;
	class Lair;
	class Landscape;

	class EnemyManager : std::enable_shared_from_this<EnemyManager>
	{
	private:
		inline static std::shared_ptr<Graphics> sGraphics;
		inline static std::shared_ptr<Landscape> sLandscape;
		
	public:
		inline static void setGraphics(std::shared_ptr<Graphics> graphics) noexcept { sGraphics = std::move(graphics); }

		inline static void setLandscape(std::shared_ptr<Landscape> landscape) noexcept { sLandscape = std::move(landscape); }

	private:
		std::shared_ptr<Route> createRoute(const PosF& from, RouteType routeType);

		void createRoutes(const Lair* lair);

		void updateRoutes();

		void updateExistingRoutes();

	public:
		[[nodiscard]] std::vector<std::shared_ptr<Enemy>> getEnemiesAround(const PosF& pos, const float r) const;

		[[nodiscard]] inline auto getCastle() const noexcept { return m_castle; }

		void setCastle(std::shared_ptr<Castle> castle)
		{
			m_castle = std::move(castle);

			updateRoutes();
			updateExistingRoutes();
		}

		void update(const float dt);

		void add(std::shared_ptr<Enemy> enemy, const Lair* lairId);
		
	private:
		std::shared_ptr<Castle>             m_castle;
		std::vector<std::shared_ptr<Enemy>> m_enemies;
		std::map<const Lair*, Routes>       m_routes;
	};
} // namespace TowerDefence

#endif /* !__ENEMY_MANAGER_HPP_INCLUDED__ */