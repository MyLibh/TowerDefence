#ifndef __OBJECT_WITH_HP_HPP_INCLUDED__
#define __OBJECT_WITH_HP_HPP_INCLUDED__

#include <algorithm>

namespace TowerDefence
{
	class ObjectWithHP
	{
	public:
		inline explicit constexpr ObjectWithHP(const int health = 0) noexcept :
			m_health(health)
		{ }

		inline virtual ~ObjectWithHP() noexcept = default;

		[[nodiscard]] inline constexpr auto getHealth() const noexcept { return m_health; }

		[[nodiscard]] inline bool isAlive() const noexcept { return m_health != 0; }

		virtual int getMaxHealth() const noexcept = 0;

		void decreaseHealth(const int amount) { m_health = std::max(0, m_health - amount); }

		void increaseHealth(const int amount)
		{
			if (m_health)
				m_health = std::min(m_health + amount, getMaxHealth());
		}

	protected:
		int m_health;
	};
} // namespace TowerDefence

#endif /* !__OBJECT_WITH_HP_HPP_INCLUDED__ */