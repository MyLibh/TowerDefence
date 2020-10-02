#ifndef __ENTITY_HPP_INCLUDED__
#define __ENTITY_HPP_INCLUDED__

#include <yvals_core.h>

namespace TowerDefence
{
	class Entity
	{
	public:
		_INLINE_VAR Entity() noexcept = default;

		_INLINE_VAR virtual ~Entity() noexcept = default;

		virtual void update(float dt) = 0;
	};
} // namespace TowerDefence

#endif /* !__ENTITY_HPP_INCLUDED__ */