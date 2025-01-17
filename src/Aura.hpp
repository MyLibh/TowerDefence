#ifndef __AURA_HPP_INCLUDED__
#define __AURA_HPP_INCLUDED__

#include "Pos.hpp"
#include "Buffs.hpp"

#include <memory>

namespace TowerDefence
{
	class GameManager;
	class Enemy;
	class Aura
	{
	private:
		inline static std::shared_ptr<GameManager> sGameManager;

	protected:
		virtual void apply(Buffs& buffs) const = 0;

	public:
		static void setGameManager(std::shared_ptr<GameManager> GameManager) noexcept;

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