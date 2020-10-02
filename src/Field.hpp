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
		_INLINE_VAR _CONSTEXPR20 Field(const PosF& pos) noexcept :
			Cell(pos),
			m_building{}
		{ }

		_INLINE_VAR ~Field() noexcept override = default;

		_NODISCARD _INLINE_VAR const auto getBuilding() const noexcept { return m_building; }

		_INLINE_VAR bool isBusy() const noexcept { return m_building != nullptr; }

		_INLINE_VAR void build(std::shared_ptr<Building> building) noexcept
		{
			if (!isBusy())
				m_building = std::move(building);
		}

	private:
		std::shared_ptr<Building> m_building;
	};
} // namespace TowerDefence

#endif /* !__FIELD_HPP_INCLUDED__ */