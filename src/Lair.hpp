#ifndef __LIRE_HPP_INCLUDED__
#define __LIRE_HPP_INCLUDED__

#include "Building.hpp"

#include <set>
#include <map>
#include <memory>

namespace TowerDefence
{
	class Enemy;
	class GameManager;

	class Lair final : public Building
	{
	private:
		inline static std::shared_ptr<GameManager> sGameManager{};

	private:
		void spawn(std::shared_ptr<Enemy> enemy);

	public:
		inline static void setGameManager(std::shared_ptr<GameManager> GameManager) noexcept { sGameManager = std::move(GameManager); }

	public:
		inline Lair(const PosF& pos, std::multimap<float, std::shared_ptr<Enemy>> shedule) noexcept :
			Building(pos),
			m_shedule(std::move(shedule))
		{ }

		inline ~Lair() noexcept override = default;

		void update(const float dt) override;

	private:
		std::multimap<float, std::shared_ptr<Enemy>> m_shedule;
	};
} // namespace TowerDefence

#endif /* !__LIRE_HPP_INCLUDED__ */
