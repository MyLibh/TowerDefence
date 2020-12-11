// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "TowerDefence.hpp"
#include "Graphics.hpp"
#include "PropsManager.hpp"
#include "MapLoader.hpp"
#include "Landscape.hpp"
#include "Utility.hpp"

#include "ui_TowerDefence.h"

#include <QTimer>
#include <QKeyEvent>
#include <QScrollBar>
#include <QPushButton>
#include <QLayout>

namespace TowerDefence
{
    void TowerDefence::keyPressEvent(QKeyEvent* event)
    {
        if (event->key() == Qt::Key_Escape)
            QMainWindow::close();

        QMainWindow::keyPressEvent(event);
    }

    void TowerDefence::mousePressEvent(QMouseEvent* event)
    {
        if (event->x() <= m_ui->canvas->width())
        {
            m_graphics->setCurrentTilePos(event->x(), event->y());

            updateButtons();
        }

        QMainWindow::mousePressEvent(event);
    }

    void TowerDefence::initWidgets()
    {
        auto canvas = m_ui->canvas;
        canvas->horizontalScrollBar()->blockSignals(true);
        canvas->verticalScrollBar()->blockSignals(true);

        QMainWindow::showFullScreen();
        canvas->resize(QMainWindow::width() - TowerDefence::BUTTON_SIZE, QMainWindow::height());

        m_ui->buildTowerButton->move(canvas->width(), 0);
        m_ui->buildWallButton->move(canvas->width(), TowerDefence::BUTTON_SIZE);
        m_ui->upgradeButton->move(canvas->width(), 2 * TowerDefence::BUTTON_SIZE);
        m_ui->repairButton->move(canvas->width(), 3 * TowerDefence::BUTTON_SIZE);

        m_ui->moneyLabel->move(canvas->width(), QMainWindow::height() - TowerDefence::BUTTON_SIZE);

        auto& scene = m_graphics->getScene();
        canvas->setScene(scene.get());
        scene->setParent(canvas);
    }

    void TowerDefence::initButtons()
    {
        auto _exec = [&](auto func)
        {
            auto pos = m_graphics->getSelectedTilePos();

            func(m_landscape, pos);

            setButtons(pos);
        };

        auto _add = [&](auto tag)
        {
            using type = tag_type_t<decltype(tag)>;
            if (auto field = std::dynamic_pointer_cast<Field>(m_landscape->getCell(m_graphics->getSelectedTilePos())); field && field->isBusy())
                m_graphics->add(std::dynamic_pointer_cast<type>(field->getBuilding()));
        };

        QObject::connect(m_ui->buildTowerButton, &QPushButton::clicked, [=]() { _exec(std::mem_fn(&Landscape::buildTower)); _add(Tag<Tower>{}); });
        QObject::connect(m_ui->buildWallButton, &QPushButton::clicked, [=]() { _exec(std::mem_fn(&Landscape::buildWall)); _add(Tag<Wall>{}); });
        QObject::connect(m_ui->upgradeButton, &QPushButton::clicked, [=]() { _exec(std::mem_fn(&Landscape::upgrade)); });
        QObject::connect(m_ui->repairButton,  &QPushButton::clicked, [=]() { _exec(std::mem_fn(&Landscape::repair)); });
    }

    void TowerDefence::updateMoneyLabel(const int money)
    {
        m_ui->moneyLabel->setText(QString("Money:\n%1").arg(money));
    }

    void TowerDefence::updateButtons()
    {
        if (m_graphics->isTileSelected())
            setButtons(m_graphics->getSelectedTilePos());
        else
            disableButtons();
    }

    void TowerDefence::setButtons(const PosF& pos)
    {
        m_ui->buildTowerButton->setEnabled(m_landscape->canBuildHere(pos));
        m_ui->buildWallButton->setEnabled(m_landscape->canBuildHere(pos));
        m_ui->upgradeButton->setEnabled(m_landscape->canUpgradeHere(pos));
        m_ui->repairButton->setEnabled(m_landscape->canRepairHere(pos));
    }

    void TowerDefence::disableButtons()
    {
        m_ui->buildTowerButton->setEnabled(false);
        m_ui->buildWallButton->setEnabled(false);
        m_ui->upgradeButton->setEnabled(false);
        m_ui->repairButton->setEnabled(false);
    }

    TowerDefence::TowerDefence(QWidget* parent /* = nullptr */) :
        QMainWindow(parent),
        m_ui(std::make_unique<Ui::TowerDefenceClass>()),
        m_timer(std::make_unique<QTimer>(this)),
        m_graphics(std::make_shared<Graphics>())
    {
        m_ui->setupUi(this);

        initWidgets();
        initButtons();

        QObject::connect(m_timer.get(), &QTimer::timeout, this, &TowerDefence::update);
        m_timer->start(TowerDefence::TIMER_INTERVAL);

        PropsManager::loadCastleProps("cfg/castle.props");
        PropsManager::loadTowerProps("cfg/tower.props");
        PropsManager::loadEnemyProps("cfg/enemies/");

        m_landscape = MapLoader::load("cfg/maps/map.json");

        m_graphics->setTileSize(m_ui->canvas->width() * 1. / m_landscape->getWidth(), m_ui->canvas->height() * 1. / m_landscape->getHeight());
        m_graphics->createMap(m_landscape);

        EnemyManager::setGraphics(m_graphics);
        EnemyManager::setLandscape(m_landscape);
    }

    TowerDefence::~TowerDefence() noexcept
    {
        EnemyManager::setGraphics(nullptr);
        EnemyManager::setLandscape(nullptr);
    }

    void TowerDefence::update()
    {
        if (m_landscape->getCastle()->isAlive())
        {
            m_landscape->update(Constants::DT);

            m_graphics->update();

            updateMoneyLabel(m_landscape->getCastle()->getMoney());

            updateButtons();
        }
        else
            m_graphics->showGameOver(QMainWindow::width() / 2, QMainWindow::height() / 2);
    }
} // namespace TowerDefence
