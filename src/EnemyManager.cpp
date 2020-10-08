// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "EnemyManager.hpp"
#include "AirEnemy.hpp"
#include "Graphics.hpp"
#include "Route.hpp"
#include "Lair.hpp"

#include <algorithm>

namespace TowerDefence
{
	std::shared_ptr<Route> EnemyManager::createRoute(const PosF& from)
	{
		return std::shared_ptr<Route>();
	}
	
	void EnemyManager::createRoutes(const Lair* lair)
	{
		auto from = lair->getPos();

		m_routes.try_emplace(lair, Routes{ createRoute(from), createRoute(from), createRoute(from) });
	}

	void EnemyManager::updateRoutes()
	{
		std::for_each(std::begin(m_routes), std::end(m_routes), [&](auto& p) { p.second.light = createRoute(p.first->getPos()); });
	}

	void EnemyManager::updateExistingRoutes()
	{
		std::for_each(std::begin(m_enemies), std::end(m_enemies), [&](auto& enemy) { enemy->setRoute(createRoute(enemy->getPos())); });
	}
	
	void EnemyManager::update(const float dt)
	{
		std::for_each(std::begin(m_enemies), std::end(m_enemies), [dt](auto& enemy) { enemy->update(dt); });
	}

	void EnemyManager::add(std::shared_ptr<Enemy> enemy, const Lair* lair)
	{
		m_enemies.emplace_back(enemy);

		if (m_routes.find(lair) == std::end(m_routes))
			createRoutes(lair);

		/*if (typeid(*enemy) == typeid(AirEnemy))
			enemy->setRoute(m_routes.at(lair).air);
		else if (typeid(*enemy) == typeid(LightEnemy))
			enemy->setRoute(m_routes.at(lair).light);
		else if (typeid(*enemy) == typeid(HeavyEnemy))
			enemy->setRoute(m_routes.at(lairId).heavy);
		*/

		sGraphics->add(enemy);
	}
} // namespace TowerDefence