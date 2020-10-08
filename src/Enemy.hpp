#ifndef __ENEMY_HPP_INCLUDED__
#define __ENEMY_HPP_INCLUDED__

#include "Entity.hpp"
#include "ObjectWithHP.hpp"

namespace TowerDefence
{
	class Route;

	class Enemy : public Entity, public ObjectWithHP
	{
	public:
		inline Enemy() noexcept = default;

		inline virtual ~Enemy() noexcept override = default;

		void update(const float dt) override final { m_pos.x += dt * m_v.x - 1; m_pos.y += dt * m_v.y; }

		inline void setRoute(std::shared_ptr<Route> route) noexcept { m_route = std::move(route); }

	protected:
		std::shared_ptr<Route> m_route;
		PosF m_v;
	};
} // namespace TowerDefence

#endif /* !__ENEMY_HPP_INCLUDED__ */