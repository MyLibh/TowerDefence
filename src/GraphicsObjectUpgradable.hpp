#ifndef __GRAPHICS_OBJECT_UPGRADABLE_HPP_INCLUDED__
#define __GRAPHICS_OBJECT_UPGRADABLE_HPP_INCLUDED__

#include "GraphicsObject.hpp"
#include "UpgradableBuilding.hpp"

namespace TowerDefence
{
	template<typename _T> requires std::is_base_of_v<UpgradableBuilding, _T>
	class GraphicsObjectUpgradable : virtual public GObject<_T>
	{
	public:
		inline GraphicsObjectUpgradable(std::string name, std::map<std::string, QPixmap>& assets) :
			GObject<_T>(),
			m_name(std::move(name)),
			m_assets(assets),
			m_lvl{}
		{ }

		inline GraphicsObjectUpgradable(
			const PosF& scale,
			std::shared_ptr<QGraphicsScene> scene,
			const QPixmap& pixmap,
			std::shared_ptr<_T> object,
			std::string name,
			std::map<std::string, QPixmap>& assets
		) :
			GObject<_T>(scale, scene, pixmap, object),
			m_name(std::move(name)),
			m_assets(assets),
			m_lvl(1)
		{ }

		GraphicsObjectUpgradable(const GraphicsObjectUpgradable&) = delete;

		inline GraphicsObjectUpgradable(GraphicsObjectUpgradable&& other) noexcept :
			GObject<_T>(std::move(other)),
			m_assets(other.m_assets),
			m_name(std::move(other.m_name)),
			m_lvl(std::move(other.m_lvl))
		{
			other.m_lvl = 0;
		}

		inline virtual ~GraphicsObjectUpgradable() noexcept override = default;

		GraphicsObjectUpgradable& operator=(const GraphicsObjectUpgradable&) = delete;

		inline GraphicsObjectUpgradable& operator=(GraphicsObjectUpgradable&& other) noexcept
		{
			GObject<_T>::operator=(std::move(other));

			if (this != &other)
			{
				m_assets = other.assets;
				m_name = std::move(other.m_name);
				m_lvl = std::move(other.m_lvl);

				other.m_lvl = 0;
			}

			return *this;
		}

		inline virtual void update() noexcept override
		{
			if (auto lvl = this->m_object->getLvl(); m_lvl != lvl)
			{
				m_lvl = lvl;

				if (auto name = m_name + std::to_string(m_lvl); m_assets.find(name) != std::end(m_assets))
					this->m_item->setPixmap(m_assets.at(name).scaled(this->getScaleX(), this->getScaleY()));
			}

			GObject<_T>::update();
		}

	private:
		std::map<std::string, QPixmap>& m_assets;
		std::string m_name;
		int m_lvl;
	};

	template<typename _T>
	using GObjectUpgradable = GraphicsObjectUpgradable<_T>;
} // namespace TowerDefence 

#endif /* !__GRAPHICS_OBJECT_UPGRADABLE_HPP_INCLUDED__ */