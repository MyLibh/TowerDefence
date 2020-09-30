// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "TowerDefence.hpp"
#include "Graphics.hpp"
#include "PropsManager.hpp"
#include "MapLoader.hpp"
#include "Landscape.hpp"

#include "ui_TowerDefence.h"

#include <QTimer>
#include <QKeyEvent>
#include <QScrollBar>

namespace TowerDefence
{
    void TowerDefence::keyPressEvent(QKeyEvent* event)
    {
        if (event->key() == Qt::Key_Escape)
            QMainWindow::close();

        QMainWindow::keyPressEvent(event);
    }

    void TowerDefence::initWidgets()
    {
        auto canvas = m_ui->canvas;
        canvas->horizontalScrollBar()->blockSignals(true);
        canvas->verticalScrollBar()->blockSignals(true);

        QMainWindow::showFullScreen();
        m_ui->canvas->resize(QMainWindow::size());

        auto& scene = m_graphics->getScene();
        canvas->setScene(scene.get());
        scene->setParent(canvas);
    }

    TowerDefence::TowerDefence(QWidget* parent /* = nullptr */) :
        QMainWindow(parent),
        m_ui(std::make_unique<Ui::TowerDefenceClass>()),
        m_timer(std::make_unique<QTimer>(this)),
        m_graphics(std::make_unique<Graphics>())
    {
        m_ui->setupUi(this);

        initWidgets();

        QObject::connect(m_timer.get(), &QTimer::timeout, this, &TowerDefence::update);
        m_timer->start(TowerDefence::TIMER_INTERVAL);

        PropsManager::loadCastleProps("cfg/castle.props");
        PropsManager::loadTowerProps("cfg/tower.props");

        m_landscape = MapLoader::load("cfg/maps/empty.json");

        m_graphics->createMap(QMainWindow::width() * 1. / m_landscape->getWidth(), QMainWindow::height() * 1. / m_landscape->getHeight(), m_landscape);
    }

    TowerDefence::~TowerDefence() noexcept = default;

    void TowerDefence::update()
    {
        m_landscape->update(1.f);
    
        m_graphics->draw();
    }
} // namespace TowerDefence
