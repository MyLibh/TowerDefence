#ifndef __ENTITY_HPP_INCLUDED__
#define __ENTITY_HPP_INCLUDED__

namespace TowerDefence
{
	class Entity
	{
	public:
		inline Entity() noexcept = default;

		virtual ~Entity() noexcept = default;

		virtual void update(float dt) = 0;
	};
} // namespace TowerDefence

#endif /* !__ENTITY_HPP_INCLUDED__ */