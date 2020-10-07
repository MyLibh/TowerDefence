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

		// void setRoute(const Route& route);
	};
} // namespace TowerDefence

#endif /* !__ENEMY_HPP_INCLUDED__ */