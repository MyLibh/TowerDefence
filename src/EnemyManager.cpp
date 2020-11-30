// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "EnemyManager.hpp"
#include "AirEnemy.hpp"
#include "HeavyEnemy.hpp"
#include "LightEnemy.hpp"
#include "Graphics.hpp"
#include "Route.hpp"
#include "Lair.hpp"
#include "Landscape.hpp"
#include "Mountain.hpp"
#include "PropsManager.hpp"
#include "Castle.hpp"

#include <algorithm>

namespace detail
{
	namespace TD = TowerDefence;
	bool checkByType(TD::RouteType type, std::shared_ptr<TD::Cell> cell)
	{
		if (type == TD::RouteType::Air)
			return typeid(*cell) != typeid(TD::Mountain);
		else if (type == TD::RouteType::Heavy)
			return typeid(*cell) == typeid(TD::Field); // TODO: check not tower
		else if (type == TD::RouteType::Light)
			return typeid(*cell) == typeid(TD::Field);// && std::dynamic_pointer_cast<TD::Field>(cell)->getBuilding() == nullptr;

		return false;
	}
}

namespace TowerDefence
{
	std::shared_ptr<Route> EnemyManager::createRoute(const PosF& from, RouteType routeType)
	{
		PosF to = m_castle ? m_castle->getPos() : from;

		std::map<PosF, bool> used;
		std::map<PosF, PosF> prev;
		std::queue<PosF>     queue;

		auto wasUsed = [&](const PosF& coord) { return used.find(coord) != std::end(used); };

		auto tryAdd = [&](const PosF& cur, const PosF& coord)
		{
			if (auto cell = sLandscape->getCell(coord); sLandscape->isInField(coord) &&
				!wasUsed(coord) &&
				cell &&
				detail::checkByType(routeType, cell)
				)
			{
				queue.push(coord);

				used.emplace(coord, true);

				prev.emplace(coord, cur);
			}
		};

		queue.push(from);
		used.emplace(from, true);
		prev.insert({ from, { -1, -1 } });
		while (!queue.empty())
		{
			auto cur = queue.front();
			queue.pop();

			tryAdd(cur, { cur.x - 1, cur.y }); // left
			tryAdd(cur, { cur.x    , cur.y + 1 }); // below
			tryAdd(cur, { cur.x + 1, cur.y }); // right
			tryAdd(cur, { cur.x    , cur.y - 1 }); // above
		}

		if (prev.find(to) == std::end(prev))
			return { };

		PosF cur = to;
		std::vector<PosF> revPath;
		while (prev.at(cur) != PosF{ -1, -1 })
		{
			revPath.push_back(cur);
			cur = prev.at(cur);
		}

		std::queue<PosF> path;
		for (auto it = std::rbegin(revPath); it != std::rend(revPath); ++it)
			path.push(*it);

		return std::make_shared<Route>(to, std::move(path));
	}
	
	void EnemyManager::createRoutes(const Lair* lair)
	{
		auto from = lair->getPos();

		m_routes.try_emplace(lair, Routes{ createRoute(from, RouteType::Light), createRoute(from, RouteType::Heavy), createRoute(from, RouteType::Air) });
	}

	void EnemyManager::updateRoutes()
	{
		// std::for_each(std::begin(m_routes), std::end(m_routes), [&](auto& p) { p.second.light = createRoute(p.first->getPos()); });
	}

	void EnemyManager::updateExistingRoutes()
	{
		//std::for_each(std::begin(m_enemies), std::end(m_enemies), [&](auto& enemy) { enemy->setRoute(createRoute(enemy->getPos(), RouteType::Light)); });
	}

	std::vector<std::shared_ptr<Enemy>> EnemyManager::getEnemiesAround(const PosF& pos, const float r) const
	{
		std::vector<std::shared_ptr<Enemy>> res;
		for (const auto& enemy : m_enemies)
			if (Distance(enemy->getPos(), pos) <= r)
				res.push_back(enemy);

		return res;
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

		if (typeid(*enemy) == typeid(AirEnemy))
			enemy->setRoute(*m_routes.at(lair).air);
		else if (typeid(*enemy) == typeid(LightEnemy))
			enemy->setRoute(*m_routes.at(lair).light);
		else if (typeid(*enemy) == typeid(HeavyEnemy))
			enemy->setRoute(*m_routes.at(lair).heavy);

		sGraphics->add(enemy);
	}
} // namespace TowerDefence