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

	class EnemyManager
	{
	private:
		inline static std::shared_ptr<Graphics> sGraphics;

	public:
		inline static void setGraphics(std::shared_ptr<Graphics> graphics) noexcept { sGraphics = std::move(graphics); }

	private:
		std::shared_ptr<Route> createRoute(const PosF& from);

		void createRoutes(const Lair* lair);

		void updateRoutes();

		void updateExistingRoutes();

	public:
		inline explicit EnemyManager() noexcept :
			m_enemies(),
			m_castlePos(),
			m_currentRoute()
		{ }

		[[nodiscard]] const auto getCurrentRoute() const noexcept { return m_currentRoute; }

		void setCastlePos(const PosF& castlePos)
		{
			m_castlePos = castlePos;

			updateRoutes();
			updateExistingRoutes();
		}

		void update(const float dt);

		void add(std::shared_ptr<Enemy> enemy, const Lair* lairId);
		
	private:
		std::vector<std::shared_ptr<Enemy>> m_enemies;
		PosF                                m_castlePos;
		std::shared_ptr<Route>              m_currentRoute;
		std::map<const Lair*, Routes>       m_routes;
	};
} // namespace TowerDefence

#endif /* !__ENEMY_MANAGER_HPP_INCLUDED__ */