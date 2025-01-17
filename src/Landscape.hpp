#ifndef __LANDSCAPE_HPP_INCLUDED__
#define __LANDSCAPE_HPP_INCLUDED__

#include "Field.hpp"
#include "GameManager.hpp"
#include "Enemy.hpp"
#include "Buildings.hpp"

#include <set>
#include <memory>

namespace TowerDefence
{
	class Landscape
	{
	private:
		template<typename _T>
		using matrix_t = std::vector<std::vector<_T>>;

	private:
		template<typename _Pred>
		inline bool canDoHere(const PosF& pos, _Pred pred) const
		{
			return std::find_if(std::begin(m_cells), std::end(m_cells),
				[&pos, p = std::move(pred)](const std::shared_ptr<Cell>& cell)
				{
					if (cell->getPos() != pos || typeid(*cell) != typeid(Field))
						return false;

					return p(std::dynamic_pointer_cast<Field>(cell));
				}) != std::end(m_cells);
		}

	public:
		inline Landscape(const unsigned width, const unsigned height) :
			m_width(width),
			m_height(height),
			m_entities(),
			m_cells(),
			m_castle{},
			m_gameManager(std::make_shared<GameManager>())
		{
			Lair::setGameManager(m_gameManager);
			Enemy::setGameManager(m_gameManager);
			Tower::setGameManager(m_gameManager);
			Aura::setGameManager(m_gameManager);
		}

		inline ~Landscape() noexcept
		{
			Lair::setGameManager(nullptr);
			Enemy::setGameManager(nullptr);
			Tower::setGameManager(nullptr);
			Aura::setGameManager(nullptr);
		}

		[[nodiscard]] inline constexpr auto getWidth() const noexcept { return m_width; }

		[[nodiscard]] inline constexpr auto getHeight() const noexcept { return m_height; }

		[[nodiscard]] inline const auto& getEntities() const noexcept { return m_entities; }

		[[nodiscard]] inline const std::shared_ptr<Cell> getCell(const PosF& pos) const noexcept
		{
			const auto cell = std::find_if(std::cbegin(m_cells), std::cend(m_cells), [&pos](const auto& el) { return el->getPos() == pos; });
			if (cell == std::end(m_cells)) [[unlikely]]
				return nullptr;

			return *cell;
		}

		[[nodiscard]] inline const auto& getCells() const noexcept { return m_cells; }

		[[nodiscard]] inline auto getCastle() const noexcept { return m_castle; }

		[[nodiscard]] inline auto getGameManager() const noexcept { return m_gameManager; }

		inline bool isInField(const PosF& pos) const noexcept { return pos.x >= 0.f && pos.x < m_width&& pos.y >= 0.f && pos.y <= m_height; }

		void update(const float dt);

		template<typename _EntityType, typename... _Args, typename = std::enable_if_t<std::is_base_of_v<Entity, _EntityType>>>
		inline auto& addEntity(_Args&&... args)
		{
			auto& entity = *m_entities.emplace(std::make_shared<_EntityType>(std::forward<_Args>(args)...)).first;

			if constexpr (std::is_same_v<_EntityType, Castle>)
			{
				m_castle = std::dynamic_pointer_cast<Castle>(entity);

				m_gameManager->setCastle(m_castle);
			}

			return entity;
		}

		template<typename _CellType, typename... _Args, typename = std::enable_if_t<std::is_base_of_v<Cell, _CellType>>>
		inline auto& addCell(_Args&&... args)
		{
			return *m_cells.emplace(std::make_shared<_CellType>(std::forward<_Args>(args)...)).first;
		}

		inline bool canBuildHere(const PosF& pos) const
		{
			return canDoHere(pos,
				[&](const auto& field)
				{
					return !field->isBusy() && m_castle->hasMoney(PropsManager::getTowerProps().price); // TODO: enemy should move than
				});
		}

		inline bool canUpgradeHere(const PosF& pos) const
		{
			return canDoHere(pos,
				[&](const auto& field)
				{
					const auto upgradable = std::dynamic_pointer_cast<UpgradableBuilding>(field->getBuilding());

					return field->isBusy() && upgradable && upgradable->canUpgrade() && m_castle->hasMoney(upgradable->getUpgradePrice());
				});
		}

		inline bool canRepairHere(const PosF& pos) const
		{
			return canDoHere(pos, 
				[&](const auto& field)
				{
					const auto obj = std::dynamic_pointer_cast<ObjectWithHP>(field->getBuilding());

					return field->isBusy() && obj && obj->isAlive() && obj->getHealth() != obj->getMaxHealth() && m_castle->hasMoney(Constants::REPAIR_COST);
				});
		}

		inline void buildTower(const PosF& pos)
		{
			if (auto field = std::dynamic_pointer_cast<Field>(getCell(pos)); field)
			{
				m_castle->withdraw(PropsManager::getTowerProps().price);

				field->build(std::dynamic_pointer_cast<Building>(addEntity<Tower>(pos)));

				m_gameManager->updateRoutes();
			}
		}

		inline void buildWall(const PosF& pos)
		{
			if (auto field = std::dynamic_pointer_cast<Field>(getCell(pos)); field)
			{
				m_castle->withdraw(Constants::WALL_COST);

				field->build(std::dynamic_pointer_cast<Building>(addEntity<Wall>(pos)));

				// m_gameManager->updateLightRoutes();
			}
		}

		inline void upgrade(const PosF& pos)
		{
			if (auto field = std::dynamic_pointer_cast<Field>(getCell(pos)); field)
				if (auto upgradable = std::dynamic_pointer_cast<UpgradableBuilding>(field->getBuilding()); upgradable && upgradable->canUpgrade())
				{
					m_castle->withdraw(upgradable->getUpgradePrice());

					upgradable->upgrade();
				}
		}

		inline void repair(const PosF& pos)
		{
			if (auto field = std::dynamic_pointer_cast<Field>(getCell(pos)); field)
				if (auto repairable = std::dynamic_pointer_cast<ObjectWithHP>(field->getBuilding()); repairable && repairable->getHealth() != repairable->getMaxHealth())
				{
					m_castle->withdraw(Constants::REPAIR_COST);

					repairable->increaseHealth(repairable->getMaxHealth());
				}
		}

	private:
		unsigned                          m_width;
		unsigned                          m_height;
		std::set<std::shared_ptr<Entity>> m_entities;
		std::set<std::shared_ptr<Cell>>   m_cells;
		std::shared_ptr<Castle>           m_castle;
		std::shared_ptr<GameManager>      m_gameManager;
	};
} // namespace TowerDefence

#endif /* !__LANDSCAPE_HPP_INCLUDED__ */