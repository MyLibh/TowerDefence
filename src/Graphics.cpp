// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Graphics.hpp"
#include "Landscape.hpp"
#include "Mountain.hpp"
#include "River.hpp"
#include "Field.hpp"
#include "Lair.hpp"

#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QDir>

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

	PosF Graphics::getSelectedTilePos() const noexcept
	{
		return { std::ceil(static_cast<float>(m_currentTile->x()) / m_tileWidth), std::ceil(static_cast<float>(m_currentTile->y()) / m_tileHeight) };
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
						add(std::dynamic_pointer_cast<Castle>(field->getBuilding()));
					else if (typeid(*field->getBuilding()) == typeid(Lair))
						add(std::dynamic_pointer_cast<Lair>(field->getBuilding()));
			}

		createGrid(landscape->getWidth() * m_tileWidth, landscape->getHeight() * m_tileHeight);
		createSelectionTile();
	}

	void Graphics::update()
	{
		m_castle.update(m_tileWidth, m_tileHeight);

		//m_enemies.erase(std::remove_if(std::begin(m_enemies), std::end(m_enemies), [](const auto& enemy) { return enemy.getObject()->isAlive(); }), std::end(m_enemies));

		// std::for_each(std::begin(m_walls), std::end(m_walls), [](auto& wall) { wall.update(); });
		std::for_each(std::begin(m_enemies), std::end(m_enemies), [&](auto& enemy) { enemy.update(m_tileWidth, m_tileHeight); });
	}

	void Graphics::showGameOver(const int width, const int height)
	{
		if (!m_gameOver)
		{
			m_gameOver = m_scene->addPixmap(m_images.at("GameOver").scaled(width, height));
			m_gameOver->setPos(width / 2, height / 2);
		}
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
} // namespace TowerDefence