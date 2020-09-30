// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Landscape.hpp"

namespace TowerDefence
{
	void Landscape::update(const float dt)
	{
		for (auto entity : m_entities)
			entity->update(dt);
	}
}