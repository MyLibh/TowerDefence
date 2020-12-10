#ifndef __BULLET_HPP_INCLUDED__
#define __BULLET_HPP_INCLUDED__

#include "Entity.hpp"

#include <memory>

namespace TowerDefence
{
	class Enemy;
	class Bullet : public Entity
	{
	public:
		inline Bullet(const int power, const PosF& pos, std::shared_ptr<Enemy> target) noexcept :
			Entity(pos),
			m_power(power),
			m_target(target),
			m_isAlive(true)
		{ }

		[[nodiscard]] inline const auto getTarget() const noexcept { return m_target; }

		inline const bool isAlive() const noexcept { return m_isAlive; }

		void update(const float dt) override;

	private:
		int m_power;
		std::shared_ptr<Enemy> m_target;
		bool m_isAlive;
	};
} // namespace TowerDefence

#endif /* !__BULLET_HPP_INCLUDED__ */