#ifndef __MAP_LOADER_HPP_INCLUDED__
#define __MAP_LOADER_HPP_INCLUDED__

#include <filesystem>
#include <memory>

namespace TowerDefence
{
	class Landscape;

	class MapLoader
	{
	public:
		static std::shared_ptr<Landscape> load(const std::filesystem::path& path);
	};
} // namespace MobileRobots

#endif /* !__MAP_LOADER_HPP_INCLUDED__ */