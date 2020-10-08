#ifndef __GRAPHICS_OBJECT_WITH_HP_AND_AURA_HPP_INCLUDED__
#define __GRAPHICS_OBJECT_WITH_HP_AND_AURA_HPP_INCLUDED__

#include "GraphicsObjectWithHP.hpp"
#include "GraphicsObjectWithAura.hpp"

namespace TowerDefence
{
	template<typename _T>
	class GraphicsObjectWithHPAndAura : public GObjectWithHP<_T>, public GObjectWithAura<_T>
	{
	public:
		inline GraphicsObjectWithHPAndAura() noexcept :
			GObjectWithHP<_T>(),
			GObjectWithAura<_T>(),
			GObject<_T>()
		{ }

		inline GraphicsObjectWithHPAndAura(std::shared_ptr<QGraphicsScene> scene, QPixmap pixmap, std::shared_ptr<_T> object, const float rx, const float ry, const PosI& size = { HP::WIDTH, HP::HEIGHT }) :
			GObjectWithHP<_T>(scene, pixmap, object, size),
			GObjectWithAura<_T>(scene, pixmap, object, rx, ry),
			GObject<_T>(scene, pixmap, object)
		{ }

		inline ~GraphicsObjectWithHPAndAura() noexcept override = default;

		inline void setPos(const PosF& pos) noexcept override
		{
			GObjectWithHP<_T>::setPos(pos);
			GObjectWithAura<_T>::setPos(pos);
		}

		inline void update(const float dx, const float dy) noexcept override { GObjectWithHP<_T>::update(dx, dy); }
	};

	template<typename _T>
	using GObjectWithHPAndAura = GraphicsObjectWithHPAndAura<_T>;
} // namespace TowerDefence

#endif /* !__GRAPHICS_OBJECT_WITH_HP_AND_AURA_HPP_INCLUDED__ */