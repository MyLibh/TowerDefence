// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "PropsManager.hpp"

#include <fstream>
#include <string>
#include <sstream>

namespace TowerDefence
{
	void PropsManager::loadCastleProps(const std::filesystem::path& path)
	{
		if (!std::filesystem::exists(path))
			throw std::invalid_argument("Path to castle props does not exist");

		std::ifstream input(path);
		if (!input.is_open())
			throw std::runtime_error("Cannot open castle props file");

		PropsManager::sCastleProps.clear();

		std::string tmp;
		while(std::getline(input, tmp))
			if (!tmp.starts_with('#'))
			{
				int lvl{};
				CastleProps cp;
				std::stringstream(tmp) >> lvl >> cp;

				sCastleProps.emplace(lvl, std::move(cp));
			}
	}

	void PropsManager::loadTowerProps(const std::filesystem::path& path)
	{
		if (!std::filesystem::exists(path))
			throw std::invalid_argument("Path to tower props does not exist");

		std::ifstream input(path);
		if (!input.is_open())
			throw std::runtime_error("Cannot open tower props file");

		PropsManager::sTowerProps.clear();

		std::string tmp;
		while (std::getline(input, tmp))
			if (!tmp.starts_with('#'))
			{
				int lvl{};
				TowerProps tp;
				std::stringstream(tmp) >> lvl >> tp;

				sTowerProps.emplace(lvl, std::move(tp));
			}
	}

	void PropsManager::loadEnemyProps(const std::filesystem::path& path)
	{
		if (!std::filesystem::exists(path))
			throw std::invalid_argument("Path to enemy props does not exist");

		PropsManager::sEnemyProps.clear();

		for (auto& propsFile : std::filesystem::directory_iterator(path))
		{
			std::ifstream input(propsFile);
			if (!input.is_open())
				throw std::runtime_error("Cannot open tower props file");

			std::string tmp;
			while (std::getline(input, tmp))
				if (!tmp.starts_with('#'))
				{
					int lvl{};
					EnemyProps props;
					std::stringstream(tmp) >> props;

					sEnemyProps.emplace(propsFile.path().filename().stem().string(), std::make_shared<EnemyProps>(props));
				}
		}
	}
}