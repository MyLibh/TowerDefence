#ifndef __PROPS_MANAGER_HPP_INCLUDED__
#define __PROPS_MANAGER_HPP_INCLUDED__

#include "CastleProps.hpp"
#include "TowerProps.hpp"

#include <map>
#include <filesystem>

namespace TowerDefence
{
	class CastleProps;

	class PropsManager final
	{
	private:
		_INLINE_VAR static std::map<int, CastleProps> sCastleProps;
		_INLINE_VAR static std::map<int, TowerProps> sTowerProps;

	public:
		static void loadCastleProps(const std::filesystem::path& path);

		static void loadTowerProps(const std::filesystem::path& path);

		_INLINE_VAR static bool canCastleUpgrade(const int lvl) { return sCastleProps.contains(lvl); }

		_INLINE_VAR static bool canTowerUpgrade(const int lvl) { return sTowerProps.contains(lvl); }

		_INLINE_VAR static auto getCastleProps(const int lvl) { return sCastleProps.at(lvl); }

		_INLINE_VAR static auto getTowerProps(const int lvl) { return sCastleProps.at(lvl); }
	};
} // namespace TowerDefence

#endif /* !__PROPS_MANAGER_HPP_INCLUDED__ */
