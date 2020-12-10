// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "MapLoader.hpp"
#include "Landscape.hpp"
#include "Cells.hpp"
#include "Enemies.hpp"
#include "PropsManager.hpp"
#include "Auras.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

#include <span>

namespace detail
{
    using namespace TowerDefence;

#define loadInt(name) object.value(QString(name)).toInt()
#define loadUInt(name) static_cast<unsigned>(loadInt(name))
#define loadFloat(name) static_cast<float>(object.value(QString(name)).toDouble())
#define loadString(name) object.value(QString(name)).toString().toUtf8()

    auto loadAuras(const QJsonArray& array)
    {
        std::vector<std::shared_ptr<Aura>> auras;

        for (const auto& item : array)
        {
            const auto&& object = item.toObject();
            if (const auto&& type = loadString("type"); type == "heal")
                auras.emplace_back(std::make_shared<HealingAura>(loadInt("heal"), loadFloat("r")));
            else if (type == "speed")
                auras.emplace_back(std::make_shared<SpeedAura>(loadFloat("speed"), loadFloat("r")));
            else if (type == "damage")
                auras.emplace_back(std::make_shared<DamageAura>(loadInt("damage"), loadFloat("r")));
        }

        return std::move(auras);
    }

    template<typename _EnemyType> requires std::is_base_of_v<Enemy, _EnemyType>
    void loadEnemy(std::multimap<float, std::shared_ptr<Enemy>>& shedule, std::string&& type, const float time, std::vector<std::shared_ptr<Aura>>&& auras)
    {
        type.front() = std::tolower(type.front());

        shedule.emplace(time, std::make_shared<_EnemyType>(PropsManager::getEnemyProps(type), std::move(auras)));
    }

    auto loadLairInfo(const QJsonArray& array, std::shared_ptr<Landscape> landscape)
    {
        std::multimap<float, std::shared_ptr<Enemy>> shedule;
        for (const auto& item : array)
        {
            const auto&& object = item.toObject();

            auto&& auras = loadAuras(object.value(QString("auras")).toArray());
            const auto&& time = loadFloat("time");
            if (std::string type = loadString("type").data(); type == "Air")
                loadEnemy<AirEnemy>(shedule, std::move(type), time, std::move(auras));
            else if (type == "Heavy")
                loadEnemy<HeavyEnemy>(shedule, std::move(type), time, std::move(auras));
            else if (type == "Light")
                loadEnemy<LightEnemy>(shedule, std::move(type), time, std::move(auras));
        }

        return std::move(shedule);
    }

    void loadCells(const QJsonArray& array, std::shared_ptr<Landscape> landscape)
    {
        for (const auto& item : array)
        {
            const auto&& object = item.toObject();

            if (const auto&& type = loadString("type"); type == "Mountain")
                landscape->addCell<Mountain>(PosF{ loadFloat("x"), loadFloat("y") });
            else if (type == "River")
                landscape->addCell<River>(PosF{ loadFloat("x"), loadFloat("y") });
            else if (type == "Field")
                landscape->addCell<Field>(PosF{ loadFloat("x"), loadFloat("y") });
            else if (type == "Castle")
            {
                auto pos = PosF{ loadFloat("x"), loadFloat("y") };
                auto cell = landscape->addCell<Field>(pos);

                auto castle = landscape->addEntity<Castle>(loadInt("money"), std::move(pos));
                std::dynamic_pointer_cast<Field>(cell)->build(std::dynamic_pointer_cast<Building>(castle));
            }
            else if (type == "Lair")
            {
                auto pos = PosF{ loadFloat("x"), loadFloat("y") };
                auto cell = landscape->addCell<Field>(pos);

                auto lair = landscape->addEntity<Lair>(std::move(pos), loadLairInfo(object.value(QString("spawn")).toArray(), landscape));
                std::dynamic_pointer_cast<Field>(cell)->build(std::dynamic_pointer_cast<Building>(lair));
            }
        }
    }

#undef loadString
#undef loadFloat
#undef loadUInt
#undef loadInt
} // namespace detail

std::shared_ptr<TowerDefence::Landscape> TowerDefence::MapLoader::load(const std::filesystem::path& path)
{
    QFile file(path.string().data());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error(file.errorString().toStdString());

    QJsonObject json = QJsonDocument::fromJson(file.readAll()).object();

    file.close();

    auto landscape = std::make_shared<Landscape>(json.value(QString("width")).toInt(), json.value(QString("height")).toInt());

    detail::loadCells(json.value(QString("cells")).toArray(), landscape);

    return std::move(landscape);
}