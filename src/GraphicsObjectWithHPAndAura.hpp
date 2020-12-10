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
		inline GraphicsObjectWithHPAndAura() noexcept = default;

		inline GraphicsObjectWithHPAndAura(
			const PosF& scale,
			std::shared_ptr<QGraphicsScene> scene,
			const QPixmap& pixmap,
			std::shared_ptr<_T> object,
			std::map<std::string, QPixmap>& assets,
			const PosI& size = { HP::WIDTH, HP::HEIGHT }
		) :
			GObject<_T>(scale, scene, pixmap, object),
			GObjectWithHP<_T>(scale, scene, pixmap, object, size),
			GObjectWithAura<_T>(scale, scene, pixmap, object, assets)
		{ }

		GraphicsObjectWithHPAndAura(const GraphicsObjectWithHPAndAura&) = delete;

		inline GraphicsObjectWithHPAndAura(GraphicsObjectWithHPAndAura&& other) noexcept :
			GObject<_T>(std::move(other)),
			GObjectWithHP<_T>(std::move(other)),
			GObjectWithAura<_T>(std::move(other))
		{ }

		inline ~GraphicsObjectWithHPAndAura() noexcept override = default;

		GraphicsObjectWithHPAndAura& operator=(const GraphicsObjectWithHPAndAura&) = delete;

		inline GraphicsObjectWithHPAndAura& operator=(GraphicsObjectWithHPAndAura&& other) noexcept
		{
			GObjectWithHP<_T>::operator=(std::move(other));

			if (this != &other)
				this->m_auras = std::move(other.m_auras);

			return *this;
		}

		inline void setPos(const PosF& pos) noexcept override
		{
			GObjectWithHP<_T>::setPos(pos);
			GObjectWithAura<_T>::setPos(pos);
		}

		inline void update() noexcept override
		{
			GObjectWithAura<_T>::update();
			GObjectWithHP<_T>::update();
		}
	};

	template<typename _T>
	using GObjectWithHPAndAura = GraphicsObjectWithHPAndAura<_T>;
} // namespace TowerDefence

#endif /* !__GRAPHICS_OBJECT_WITH_HP_AND_AURA_HPP_INCLUDED__ */