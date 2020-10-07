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
		inline constexpr Field(const PosF& pos) noexcept :
			Cell(pos),
			m_building{}
		{ }

		inline ~Field() noexcept override = default;

		_NODISCARD inline const auto getBuilding() const noexcept { return m_building; }

		inline bool isBusy() const noexcept { return m_building != nullptr; }

		inline void build(std::shared_ptr<Building> building) noexcept
		{
			if (!isBusy())
				m_building = std::move(building);
		}

	private:
		std::shared_ptr<Building> m_building;
	};
} // namespace TowerDefence

#endif /* !__FIELD_HPP_INCLUDED__ */