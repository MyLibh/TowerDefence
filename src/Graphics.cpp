// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Graphics.hpp"
#include "Landscape.hpp"
#include "Mountain.hpp"
#include "River.hpp"
#include "Field.hpp"
#include "Lair.hpp"

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QDir>
#include <QPixmap>

namespace TowerDefence
{
	void Graphics::loadImages()
	{
		QString path = ":/assets/";
		for (const auto& file : QDir(path).entryList())
			m_images.emplace(file.section(".", 0, 0).toStdString(), QPixmap(path + file));
	}

	void Graphics::createGrid(const float width, const float height, const float dx, const float dy)
	{
		for (float x{}; x <= width; x += dx)
			m_grid[0].emplace_back(m_scene->addLine(x, 0., x, height, QPen(Qt::black)));

		for (float y{}; y <= height; y += dy)
			m_grid[1].emplace_back(m_scene->addLine(0., y, width, y, QPen(Qt::black)));
	}

	void Graphics::createMap(const float dx, const float dy, const std::shared_ptr<Landscape> landscape)
	{
		loadImages();

		const float width = landscape->getWidth() * dx;
		const float height = landscape->getHeight() * dy;

		for (const auto& cell : landscape->getCells())
			if (const auto& id = typeid(*cell); id == typeid(Mountain))
			{
				auto [x, y] = std::dynamic_pointer_cast<Mountain>(cell)->getPos();
				auto pm = m_scene->addPixmap(m_images.at("Mountain").scaled(dx, dy));
				pm->setPos(1. * x * dx, 1. * y * dy);
			}
			else if (id == typeid(River))
			{
				auto [x, y] = std::dynamic_pointer_cast<River>(cell)->getPos();
				auto pm = m_scene->addPixmap(m_images.at("Water").scaled(dx, dy));
				pm->setPos(1. * x * dx, 1. * y * dy);
			}
			else if(id == typeid(Field))
			{
				auto field = std::dynamic_pointer_cast<Field>(cell);
				auto [x, y] = field->getPos();
				auto pm = m_scene->addPixmap(m_images.at("Grass").scaled(dx, dy));
				pm->setPos(1. * x * dx, 1. * y * dy);

				if (field->isBusy())
					if (typeid(*field->getBuilding()) == typeid(Castle))
					{
						auto pm = m_scene->addPixmap(m_images.at("Castle").scaled(dx, dy));
						pm->setPos(1. * x * dx, 1. * y * dy);
					}
					else if (typeid(*field->getBuilding()) == typeid(Lair))
					{
						auto pm = m_scene->addPixmap(m_images.at("Lair").scaled(dx, dy));
						pm->setPos(1. * x * dx, 1. * y * dy);
					}
			}

		createGrid(width, height, dx, dy);
	}

	void Graphics::draw() const
	{
	}
} // namespace TowerDefence