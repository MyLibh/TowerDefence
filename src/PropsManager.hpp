#ifndef __PROPS_MANAGER_HPP_INCLUDED__
#define __PROPS_MANAGER_HPP_INCLUDED__

#include "CastleProps.hpp"
#include "TowerProps.hpp"
#include "EnemyProps.hpp"

#include <map>
#include <filesystem>

namespace TowerDefence
{
	class PropsManager final
	{
	private:
		inline static std::map<int, CastleProps> sCastleProps;
		inline static std::map<int, TowerProps> sTowerProps;
		inline static std::map<std::string, std::shared_ptr<EnemyProps>> sEnemyProps;

	public:
		static void loadCastleProps(const std::filesystem::path& path);

		static void loadTowerProps(const std::filesystem::path& path);

		static void loadEnemyProps(const std::filesystem::path& path);

		inline static bool canCastleUpgrade(const int lvl) { return sCastleProps.contains(lvl); }

		inline static bool canTowerUpgrade(const int lvl) { return sTowerProps.contains(lvl); }

		inline static auto getCastleProps(const int lvl = 1) { return sCastleProps.at(lvl); }

		inline static auto getTowerProps(const int lvl = 1) { return sTowerProps.at(lvl); }

		inline static auto getEnemyProps(const std::string& enemy) { return sEnemyProps.at(enemy); }
	};
} // namespace TowerDefence

#endif /* !__PROPS_MANAGER_HPP_INCLUDED__ */
