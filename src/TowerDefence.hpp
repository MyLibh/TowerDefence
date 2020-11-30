#ifndef __TOWER_DEFENCE_HPP_INCLUDED__
#define __TOWER_DEFENCE_HPP_INCLUDED__

#include <QtWidgets/QMainWindow>
#include <memory>
#include <chrono>

#include "Pos.hpp"

using namespace std::chrono_literals;

namespace Ui
{
    class TowerDefenceClass;
}

class QTimer;

namespace TowerDefence
{
    class Graphics;
    class Landscape;

    class TowerDefence final : public QMainWindow
    {
        Q_OBJECT

    private:
        inline static constexpr auto TIMER_INTERVAL{ 100ms };
        inline static constexpr auto BUTTON_SIZE{ 100 };

    private:
        void keyPressEvent(QKeyEvent* event) override;

        void mousePressEvent(QMouseEvent* event) override;

        void initWidgets();

        void initButtons();

        void updateMoneyLabel(const int money);

        void updateButtons();

        void setButtons(const PosF& pos);

        void disableButtons();

    public:
        TowerDefence(QWidget* parent = nullptr);

        ~TowerDefence() noexcept;

        void update();

    private:
        std::unique_ptr<Ui::TowerDefenceClass> m_ui;
        std::unique_ptr<QTimer>                m_timer;
        std::shared_ptr<Graphics>              m_graphics;
        std::shared_ptr<Landscape>             m_landscape;
    };
} // namespace TowerDefense
#endif /* !__TOWER_DEFENCE_HPP_INCLUDED__ */