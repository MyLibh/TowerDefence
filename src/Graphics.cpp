// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Graphics.hpp"
#include "Landscape.hpp"
#include "Mountain.hpp"
#include "River.hpp"
#include "Field.hpp"
#include "Lair.hpp"
#include "Tower.hpp"

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
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

	void Graphics::createGrid(const float width, const float height)
	{
		for (float x{}; x <= width; x += m_tileWidth)
			m_grid[0].emplace_back(m_scene->addLine(x, 0., x, height, QPen(Qt::black)));

		for (float y{}; y <= height; y += m_tileHeight)
			m_grid[1].emplace_back(m_scene->addLine(0., y, width, y, QPen(Qt::black)));
	}

	void Graphics::createSelectionTile()
	{
		m_currentTile = m_scene->addRect(0., 0., m_tileWidth, m_tileHeight, QPen(Qt::green));
		m_currentTile->setVisible(false);
	}

	void Graphics::addCastle(std::shared_ptr<Castle> castle)
	{
		m_castle = std::make_unique<CastleGraphics>(m_scene, m_images.at("Castle").scaled(m_tileWidth, m_tileHeight), castle);
	}

	PosF Graphics::getSelectedTilePos() const noexcept
	{
		return { static_cast<float>(m_currentTile->x()) / m_tileWidth, static_cast<float>(m_currentTile->y()) / m_tileHeight };
	}

	bool Graphics::isTileSelected() const noexcept
	{
		return m_currentTile->isVisible();
	}

	void Graphics::createMap(const std::shared_ptr<Landscape>& landscape)
	{
		loadImages();

		m_scene->setBackgroundBrush(Qt::black);

		for (const auto& cell : landscape->getCells())
			if (const auto& id = typeid(*cell); id == typeid(Mountain))
			{
				auto [x, y] = std::dynamic_pointer_cast<Mountain>(cell)->getPos();
				auto pm = m_scene->addPixmap(m_images.at("Mountain").scaled(m_tileWidth, m_tileHeight));
				pm->setPos(1. * x * m_tileWidth, 1. * y * m_tileHeight);
			}
			else if (id == typeid(River))
			{
				auto [x, y] = std::dynamic_pointer_cast<River>(cell)->getPos();
				auto pm = m_scene->addPixmap(m_images.at("Water").scaled(m_tileWidth, m_tileHeight));
				pm->setPos(1. * x * m_tileWidth, 1. * y * m_tileHeight);
			}
			else if(id == typeid(Field))
			{
				auto field = std::dynamic_pointer_cast<Field>(cell);
				auto [x, y] = field->getPos();
				auto pm = m_scene->addPixmap(m_images.at("Grass").scaled(m_tileWidth, m_tileHeight));
				pm->setPos(1. * x * m_tileWidth, 1. * y * m_tileHeight);

				if (field->isBusy())
					if (typeid(*field->getBuilding()) == typeid(Castle))
					{
						addCastle(std::dynamic_pointer_cast<Castle>(field->getBuilding()));
						m_castle->setPos({ x * m_tileWidth, y * m_tileHeight });
					}
					else if (typeid(*field->getBuilding()) == typeid(Lair))
					{
						auto pm = m_scene->addPixmap(m_images.at("Lair").scaled(m_tileWidth, m_tileHeight));
						pm->setPos(1. * x * m_tileWidth, 1. * y * m_tileHeight);
					}
			}

		createGrid(landscape->getWidth() * m_tileWidth, landscape->getHeight() * m_tileHeight);
		createSelectionTile();
	}

	void Graphics::draw() const
	{
		m_castle->draw();
	}

	void Graphics::setCurrentTilePos(int x, int y)
	{
		x -= x % static_cast<int>(m_tileWidth);
		y -= y % static_cast<int>(m_tileHeight);

		if (m_currentTile->isVisible())
		{
			if (auto pos = m_currentTile->pos(); pos.x() == x && pos.y() == y)
				m_currentTile->setVisible(false);
		}
		else
			m_currentTile->setVisible(true);

		m_currentTile->setPos(x - x % static_cast<int>(m_tileWidth), y - y % static_cast<int>(m_tileHeight));
	}

	void Graphics::addTower(std::shared_ptr<Tower> tower)
	{
		m_towers.emplace_back(m_scene, m_images.at("Tower").scaled(m_tileWidth, m_tileHeight), tower);

		m_towers.back().setPos({ tower->getX() * m_tileWidth, tower->getY() * m_tileHeight });
	}
} // namespace TowerDefence