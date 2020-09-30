#ifndef __TOWER_HPP_INCLUDED__
#define __TOWER_HPP_INCLUDED__

#include <QtWidgets/QMainWindow>
#include <memory>
#include <chrono>

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

    class TowerDefence : public QMainWindow
    {
        Q_OBJECT

    private:
        inline static constexpr auto TIMER_INTERVAL{ 1s };

    private:
        void keyPressEvent(QKeyEvent* event) override;

        void initWidgets();

    public:
        TowerDefence(QWidget* parent = nullptr);

        ~TowerDefence() noexcept;

        void update();

    private:
        std::unique_ptr<Ui::TowerDefenceClass> m_ui;
        std::unique_ptr<QTimer>                m_timer;
        std::unique_ptr<Graphics>              m_graphics;
        std::shared_ptr<Landscape>             m_landscape;
    };
} // namespace TowerDefense
#endif /* !__TOWER_HPP_INCLUDED__ */