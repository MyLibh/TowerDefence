#ifndef __GRAPHICS_OBJECT_UPGRADABLE_WITH_HP_HPP_INCLUDED__
#define __GRAPHICS_OBJECT_UPGRADABLE_WITH_HP_HPP_INCLUDED__

#include "GraphicsObjectUpgradable.hpp"
#include "GraphicsObjectWithHP.hpp"

namespace TowerDefence
{
	template<typename _T>
	class GraphicsObjectUpgradableWithHP : public GObjectWithHP<_T>, public GObjectUpgradable<_T>
	{
	public:
		inline GraphicsObjectUpgradableWithHP(std::string name, std::map<std::string, QPixmap>& assets) :
			GObject<_T>(),
			GObjectWithHP<_T>(),
			GObjectUpgradable<_T>(std::move(name), assets)
		{ }

		inline GraphicsObjectUpgradableWithHP(
			const PosF& scale,
			std::shared_ptr<QGraphicsScene> scene,
			const QPixmap& pixmap,
			std::shared_ptr<_T> object,
			std::string name,
			std::map<std::string, QPixmap>& assets,
			const PosI& size = { HP::WIDTH, HP::HEIGHT }
		) :
			GObject<_T>(scale, scene, pixmap, object),
			GObjectWithHP<_T>(scale, scene, pixmap, object, size),
			GObjectUpgradable<_T>(scale, scene, pixmap, object, std::move(name), assets)
		{ }

		GraphicsObjectUpgradableWithHP(const GraphicsObjectUpgradableWithHP&) = delete;

		inline GraphicsObjectUpgradableWithHP(GraphicsObjectUpgradableWithHP&& other) noexcept :
			GObject<_T>(std::move(other)),
			GObjectWithHP<_T>(std::move(other)),
			GObjectUpgradable<_T>(std::move(other))
		{ }

		inline ~GraphicsObjectUpgradableWithHP() noexcept override = default;

		GraphicsObjectUpgradableWithHP& operator=(const GraphicsObjectUpgradableWithHP&) = delete;

		inline GraphicsObjectUpgradableWithHP& operator=(GraphicsObjectUpgradableWithHP&& other)
		{
			GObjectUpgradable<_T>::operator=(std::move(other));

			if (this != &other)
				this->m_hp = std::move(other.m_hp);

			return *this;
		}

		inline virtual void update() noexcept override
		{
			GObjectWithHP<_T>::update();
			GObjectUpgradable<_T>::update();
		}
	};

	template<typename _T>
	using GObjectUpgradableWithHP = GraphicsObjectUpgradableWithHP<_T>;
} // namespace TowerDefence 

#endif /* !__GRAPHICS_OBJECT_UPGRADABLE_WITH_HP_HPP_INCLUDED__ */