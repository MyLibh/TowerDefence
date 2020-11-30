#ifndef __ENEMY_HPP_INCLUDED__
#define __ENEMY_HPP_INCLUDED__

#include "Entity.hpp"
#include "ObjectWithHP.hpp"
#include "EnemyProps.hpp"
#include "Route.hpp"

#include <vector>
#include <memory>

namespace TowerDefence
{
	class Aura;
	class Enemy : public Entity, public ObjectWithHP
	{
	private:
		void attack();

		void move(const float dt);

		void regenerate();

		void useAuras();

	public:
		inline Enemy(std::shared_ptr<EnemyProps> props) noexcept :
			m_props(std::move(props))
		{}

		inline virtual ~Enemy() noexcept override = default;

		void update(const float dt) override final;

		inline void setRoute(Route route) noexcept { m_route = std::move(route); }

		inline void setProperties(std::shared_ptr<EnemyProps> props) noexcept { m_props = std::move(props); }

	protected:
		std::shared_ptr<EnemyProps>        m_props;
		Route                              m_route;
		std::vector<std::shared_ptr<Aura>> m_auras;
	};
} // namespace TowerDefence

#endif /* !__ENEMY_HPP_INCLUDED__ */