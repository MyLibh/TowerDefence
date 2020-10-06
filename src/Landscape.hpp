#ifndef __LANDSCAPE_HPP_INCLUDED__
#define __LANDSCAPE_HPP_INCLUDED__

#include "Castle.hpp"
#include "Field.hpp"
#include "Tower.hpp"

#include <set>
#include <memory>

namespace TowerDefence
{
	class Landscape
	{
	private:
		template<typename _Pred>
		_INLINE_VAR bool canDoHere(const PosF& pos, _Pred pred) const
		{
			return std::find_if(std::begin(m_cells), std::end(m_cells),
				[&pos, p = std::move(pred)](const std::shared_ptr<Cell>& cell)
			{
				if (cell->getPos() != pos || typeid(*cell) != typeid(Field))
					return false;

				return p(std::dynamic_pointer_cast<Field>(cell)); // TODO: check money?
			}) != std::end(m_cells);
		}

	public:
		_INLINE_VAR Landscape() noexcept = default;

		_INLINE_VAR Landscape(const unsigned width, const unsigned height) noexcept :
			m_width(width),
			m_height(height),
			m_entities(),
			m_cells(),
			m_castle{}
		{ }

		_NODISCARD _INLINE_VAR _CONSTEXPR20 auto getWidth() const noexcept { return m_width; }

		_NODISCARD _INLINE_VAR _CONSTEXPR20 auto getHeight() const noexcept { return m_height; }

		_NODISCARD _INLINE_VAR const auto& getEntities() const noexcept { return m_entities; }

		_NODISCARD _INLINE_VAR const std::shared_ptr<Cell> getCell(const PosF& pos) const noexcept
		{
			const auto cell = std::find_if(std::cbegin(m_cells), std::cend(m_cells), [&pos](const auto& el) { return el->getPos() == pos; });
			if (cell == std::end(m_cells)) [[unlikely]]
				return nullptr;

			return *cell;
		}

		_NODISCARD _INLINE_VAR const auto& getCells() const noexcept { return m_cells; }

		_NODISCARD _INLINE_VAR auto getCastle() const noexcept { return m_castle; }

		void update(const float dt);

		template<typename _EntityType, typename... _Args, typename = std::enable_if_t<std::is_base_of_v<Entity, _EntityType>>>
		_INLINE_VAR auto& addEntity(_Args&&... args)
		{
			auto& entity = *m_entities.emplace(std::make_shared<_EntityType>(std::forward<_Args>(args)...)).first;

			if _CONSTEXPR_IF(std::is_same_v<_EntityType, Castle>)
				m_castle = std::dynamic_pointer_cast<Castle>(entity);

			return entity;
		}

		template<typename _CellType, typename... _Args, typename = std::enable_if_t<std::is_base_of_v<Cell, _CellType>>>
		_INLINE_VAR auto& addCell(_Args&&... args)
		{
			return *m_cells.emplace(std::make_shared<_CellType>(std::forward<_Args>(args)...)).first;
		}

		_INLINE_VAR bool canBuildHere(const PosF& pos) const
		{
			return canDoHere(pos,
				[&](const auto& field)
				{
					return !field->isBusy() && m_castle->hasMoney(PropsManager::getTowerProps().price); // TODO: enemy should move than
				});
		}

		_INLINE_VAR bool canUpgradeHere(const PosF& pos) const
		{
			return canDoHere(pos,
				[&](const auto& field)
				{
					const auto ptr = std::dynamic_pointer_cast<UpgradableBuilding>(field->getBuilding());

					return field->isBusy() && ptr && ptr->canUpgrade() && m_castle->hasMoney(ptr->getUpgradePrice());
				});
		}

		_INLINE_VAR bool canRepairHere(const PosF& pos) const
		{
			return canDoHere(pos, [](const auto&) { return false; });
		}

		_INLINE_VAR void build(const PosF& pos)
		{
			if (auto field = std::dynamic_pointer_cast<Field>(getCell(pos)); field)
			{
				m_castle->withdraw(PropsManager::getTowerProps().price);

				auto tower = addEntity<Tower>(pos);
				field->build(std::dynamic_pointer_cast<Building>(tower));
			}
		}

		_INLINE_VAR void upgrade(const PosF& pos)
		{
			if (auto field = std::dynamic_pointer_cast<Field>(getCell(pos)); field)
				if (auto upgradable = std::dynamic_pointer_cast<UpgradableBuilding>(field->getBuilding()); upgradable && upgradable->canUpgrade())
				{
					m_castle->withdraw(upgradable->getUpgradePrice());

					upgradable->upgrade();
				}
		}

		_INLINE_VAR void repair(const PosF& pos)
		{

		}

	private:
		unsigned                          m_width;
		unsigned                          m_height;
		std::set<std::shared_ptr<Entity>> m_entities;
		std::set<std::shared_ptr<Cell>>   m_cells;
		std::shared_ptr<Castle>           m_castle;
	};
} // namespace TowerDefence

#endif /* !__LANDSCAPE_HPP_INCLUDED__ */