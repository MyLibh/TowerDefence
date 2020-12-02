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
			std::shared_ptr<QGraphicsScene> scene,
			QPixmap pixmap,
			std::shared_ptr<_T> object,
			std::string name,
			std::map<std::string, QPixmap>& assets,
			const PosI& size = { HP::WIDTH, HP::HEIGHT }
		) :
			GObject<_T>(scene, pixmap, object),
			GObjectWithHP<_T>(scene, pixmap, object, size),
			GObjectUpgradable<_T>(scene, pixmap, object, std::move(name), assets)
		{ }

		inline virtual void update(const float dx, const float dy) noexcept override
		{
			GObjectWithHP<_T>::update(dx, dy);
			GObjectUpgradable<_T>::update(dx, dy);
		}
	};

	template<typename _T>
	using GObjectUpgradableWithHP = GraphicsObjectUpgradableWithHP<_T>;
} // namespace TowerDefence 

#endif /* !__GRAPHICS_OBJECT_UPGRADABLE_WITH_HP_HPP_INCLUDED__ */