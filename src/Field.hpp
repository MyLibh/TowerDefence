#ifndef __FIELD_HPP_INCLUDED__
#define __FIELD_HPP_INCLUDED__

#include "Cell.hpp"
#include "Building.hpp"

#include <memory>

namespace TowerDefence
{
	class Field final : public Cell
	{
	public:
		explicit inline constexpr Field(const PosF& pos) noexcept :
			Cell(pos)
		{ }

		inline ~Field() noexcept override = default;

		[[nodiscard]] inline const auto getBuilding() const noexcept { return m_building.lock(); }

		inline bool isBusy() const noexcept { return !m_building.expired(); }

		inline void build(std::weak_ptr<Building> building) noexcept
		{
			if (!isBusy())
				m_building = std::move(building);
		}

	private:
		std::weak_ptr<Building> m_building;
	};
} // namespace TowerDefence

#endif /* !__FIELD_HPP_INCLUDED__ */