#ifndef __AURA_HPP_INCLUDED__
#define __AURA_HPP_INCLUDED__

#include "Pos.hpp"

#include <memory>

namespace TowerDefence
{
	class EnemyManager;
	class Enemy;
	class Aura
	{
	private:
		inline static std::shared_ptr<EnemyManager> sEnemyManager;

	protected:
		virtual void apply(std::shared_ptr<Enemy> enemy) const = 0;

	public:
		static void setEnemyManager(std::shared_ptr<EnemyManager> enemyManager) noexcept;

	public:
		Aura() = delete;

		explicit inline Aura(const float r) :
			m_r(r)
		{ }

		[[nodiscard]] inline constexpr auto getRadius() const noexcept { return m_r; }

		void applyEffect(const PosF& pos) const;

	private:
		float m_r;
	};
} // namespace TowerDefence

#endif /* !__AURA_HPP_INCLUDED__ */