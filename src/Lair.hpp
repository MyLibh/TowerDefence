#ifndef __LIRE_HPP_INCLUDED__
#define __LIRE_HPP_INCLUDED__

#include "Building.hpp"

#include <set>
#include <map>
#include <memory>

namespace TowerDefence
{
	class Enemy;
	class EnemyManager;

	class Lair final : public Building
	{
	private:
		inline static std::shared_ptr<EnemyManager> sEnemyManager{};

	private:
		void spawn(std::shared_ptr<Enemy> enemy);

	public:
		inline static void setEnemyManager(std::shared_ptr<EnemyManager> enemyManager) noexcept { sEnemyManager = std::move(enemyManager); }

	public:
		inline Lair(const PosF& pos, std::multimap<float, std::shared_ptr<Enemy>> shedule) noexcept :
			Building(pos),
			m_timer{},
			m_shedule(std::move(shedule))
		{ }

		inline ~Lair() noexcept override = default;

		void update(float dt) override;

		void spawn();

	private:
		float                                        m_timer;
		std::multimap<float, std::shared_ptr<Enemy>> m_shedule;
	};
} // namespace TowerDefence

#endif /* !__LIRE_HPP_INCLUDED__ */
