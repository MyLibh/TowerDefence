// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "MapLoader.hpp"
#include "Landscape.hpp"
#include "Mountain.hpp"
#include "River.hpp"
#include "Field.hpp"
#include "Lair.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

namespace detail
{
    using namespace TowerDefence;

#define loadInt(name) object.value(QString(name)).toInt()
#define loadUInt(name) static_cast<unsigned>(loadInt(name))
#define loadFloat(name) static_cast<float>(object.value(QString(name)).toDouble())
#define loadString(name) object.value(QString(name)).toString().toUtf8()

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

                auto entity = landscape->addEntity<Castle>(loadInt("money"), std::move(pos));
                std::dynamic_pointer_cast<Field>(cell)->build(std::dynamic_pointer_cast<Building>(entity));
            }
            else if (type == "Lair")
            {
                auto pos = PosF{ loadFloat("x"), loadFloat("y") };
                auto cell = landscape->addCell<Field>(pos);

                auto entity = landscape->addEntity<Lair>(std::move(pos));
                std::dynamic_pointer_cast<Field>(cell)->build(std::dynamic_pointer_cast<Building>(entity));
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
    // MapObject::setEnvironmentDescriptor(envDescr->shared_from_this());

    detail::loadCells(json.value(QString("cells")).toArray(), landscape);

    return std::move(landscape);
}