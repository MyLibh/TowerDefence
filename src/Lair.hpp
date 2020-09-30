#ifndef __LIRE_HPP_INCLUDED__
#define __LIRE_HPP_INCLUDED__

#include "Building.hpp"

#include <set>
#include <map>
#include <memory>

namespace TowerDefence
{
	class Enemy;

	class Lair final : public Building
	{
	private:
		void spawn(std::shared_ptr<Enemy> enemy);

	public:
		inline Lair(const PosF& pos) noexcept :
			Building(pos)
		{ }

		~Lair() noexcept override = default;

		void update(float dt) override;

		void spawn();

	private:
		float                                             m_timer;
		std::shared_ptr<std::set<std::shared_ptr<Enemy>>> m_enemies;
		std::multimap<float, std::shared_ptr<Enemy>>      m_shedule;
	};
} // namespace TowerDefence

#endif /* !__LIRE_HPP_INCLUDED__ */
