#ifndef __ENEMY_MANAGER_HPP_INCLUDED__
#define __ENEMY_MANAGER_HPP_INCLUDED__

#include <vector>
#include <memory>

namespace TowerDefence
{
	class Enemy;

	class EnemyManager
	{
	public:
		void update(const float dt);

		void updateRoutes();

		void add(std::shared_ptr<Enemy> enemy);

	private:
		std::vector<std::shared_ptr<Enemy>> m_enemies;
	};
} // namespace TowerDefence

#endif /* !__ENEMY_MANAGER_HPP_INCLUDED__ */