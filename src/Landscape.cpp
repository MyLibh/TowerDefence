// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Landscape.hpp"
#include "Utility.hpp"

namespace TowerDefence
{
	void Landscape::update(const float dt)
	{
		std::for_each(std::begin(m_entities), std::end(m_entities), [dt](auto& entity) { entity->update(dt); });

		discard_if(m_entities,
			[](auto& entity)
			{
				const auto& obj = std::dynamic_pointer_cast<const ObjectWithHP>(entity);

				return obj && !obj->isAlive();
			}
		);

		m_enemyManager->update(dt);
	}
}