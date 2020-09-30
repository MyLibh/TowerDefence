#ifndef __LANDSCAPE_HPP_INCLUDED__
#define __LANDSCAPE_HPP_INCLUDED__

#include "Castle.hpp"
#include "Cell.hpp"

#include <set>
#include <memory>

namespace TowerDefence
{
	class Landscape
	{
	public:
		inline Landscape() noexcept = default;

		inline Landscape(const unsigned width, const unsigned height) noexcept :
			m_width(width),
			m_height(height),
			m_entities()
		{ }

		_NODISCARD inline constexpr auto getWidth() const noexcept { return m_width; }

		_NODISCARD inline constexpr auto getHeight() const noexcept { return m_height; }

		_NODISCARD inline const auto& getEntities() const noexcept { return m_entities; }

		_NODISCARD inline const auto& getCells() const noexcept { return m_cells; }

		void update(const float dt);

		template<typename _EntityType, typename... _Args, typename = std::enable_if_t<std::is_base_of_v<Entity, _EntityType>>>
		inline auto& addEntity(_Args&&... args)
		{
			return *m_entities.emplace(std::make_shared<_EntityType>(std::forward<_Args>(args)...)).first;
		}

		template<typename _CellType, typename... _Args, typename = std::enable_if_t<std::is_base_of_v<Cell, _CellType>>>
		inline auto& addCell(_Args&&... args)
		{
			return *m_cells.emplace(std::make_shared<_CellType>(std::forward<_Args>(args)...)).first;
		}

	private:
		unsigned                          m_width;
		unsigned                          m_height;
		std::set<std::shared_ptr<Entity>> m_entities;
		std::set<std::shared_ptr<Cell>>   m_cells;
	};
} // namespace TowerDefence

#endif /* !__LANDSCAPE_HPP_INCLUDED__ */