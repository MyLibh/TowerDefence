// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Graphics.hpp"
#include "Landscape.hpp"
#include "Cells.hpp"
#include "Lair.hpp"
#include "Utility.hpp"

#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QDir>
#include <QDebug>

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
	}

	PosF Graphics::getSelectedTilePos() const noexcept
	{
		return { std::ceil(static_cast<int>(m_currentTile->x()) / m_tileWidth), std::ceil(static_cast<int>(m_currentTile->y()) / m_tileHeight) };
	}

	bool Graphics::isTileSelected() const noexcept
	{
		return m_currentTile->isVisible();
	}

	void Graphics::createMap(const std::shared_ptr<Landscape>& landscape)
	{
		loadImages();

		m_scene->setBackgroundBrush(Qt::black);

		auto addCell = [&]<typename _T> (Tag<_T> tag, auto&& cell, const std::string& name) requires std::is_base_of_v<Cell, _T>
		{
			using type = tag_type_t<decltype(tag)>;

			auto [x, y] = std::dynamic_pointer_cast<type>(cell)->getPos();
			auto pm = m_scene->addPixmap(m_images.at(name).scaled(m_tileWidth, m_tileHeight));
			pm->setPos(1. * x * m_tileWidth, 1. * y * m_tileHeight);
		};

		for (const auto& cell : landscape->getCells())
			if (const auto& id = typeid(*cell); id == typeid(Mountain))
				addCell(Tag<Mountain>{}, cell, "Mountain");
			else if (id == typeid(River))
				addCell(Tag<River>{}, cell, "Water");
			else if(id == typeid(Field))
			{
				addCell(Tag<Field>{}, cell, "Grass");

				if (auto field = std::dynamic_pointer_cast<Field>(cell); field->isBusy())
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
		m_castle->update();

		auto _remove = [](auto& collection)
		{
			collection.erase(
				std::remove_if(std::begin(collection), std::end(collection),
					[](const auto& item)
					{
						auto obj = item.getObject();

						return !obj || !obj->isAlive();
					}),
				std::end(collection));
		};

		for (const auto& o : m_enemies)
			qDebug() << o.getObject().get();

		_remove(m_walls);
		_remove(m_enemies);
		_remove(m_bullets);

		auto _update = [](auto& collection)
		{
			std::for_each(std::begin(collection), std::end(collection), [&](auto& item) { item.update(); });
		};

		_update(m_walls);
		_update(m_towers);
		_update(m_enemies);
		_update(m_bullets);
	}

	void Graphics::showGameOver(const int width, const int height)
	{
		if (!m_gameOver)
		{
			m_gameOver = m_scene->addPixmap(m_images.at("GameOver").scaled(width, height));
			m_gameOver->setPos(width / 2.f, height / 2.f);
		}
	}

	void Graphics::setCurrentTilePos(int x, int y)
	{
		x = std::floor(x / m_tileWidth);
		y = std::floor(y / m_tileHeight);

		m_currentTile->setPos(static_cast<double>(x) * m_tileWidth, static_cast<double>(y) * m_tileHeight);
	}
} // namespace TowerDefence