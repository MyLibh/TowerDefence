#ifndef __GRAPHICS_OBJECT_WITH_AURA_HPP_INCLUDED__
#define __GRAPHICS_OBJECT_WITH_AURA_HPP_INCLUDED__

#include "GraphicsObject.hpp"
#include "GraphicsAura.hpp"
#include "HealingAura.hpp"

namespace TowerDefence
{
	template<typename _T> requires std::is_base_of_v<Enemy, _T>
	class GraphicsObjectWithAura : virtual public GObject<_T>
	{
	public:
		inline GraphicsObjectWithAura() noexcept = default;

		inline GraphicsObjectWithAura(const PosF& scale, std::shared_ptr<QGraphicsScene> scene, QPixmap pixmap, std::shared_ptr<_T> object, std::map<std::string, QPixmap>& assets) :
			GObject<_T>(scale, scene, pixmap, object)
		{
			for (const auto& aura : object->getAuras())
				if (typeid(*aura) == typeid(HealingAura))
					m_auras.emplace_back(scene, aura->getRadius(), scale, Qt::GlobalColor::green, assets.at("HealParticle"));
		}

		GraphicsObjectWithAura(const GraphicsObjectWithAura&) = delete;

		inline GraphicsObjectWithAura(GraphicsObjectWithAura&& other) noexcept :
			GObject<_T>(std::move(other)),
			m_auras(std::move(other.m_auras))
		{ }

		inline virtual ~GraphicsObjectWithAura() noexcept override = default;

		GraphicsObjectWithAura& operator=(const GraphicsObjectWithAura&) = delete;

		inline GraphicsObjectWithAura& operator=(GraphicsObjectWithAura&& other) noexcept
		{
			GObject<_T>::operator=(std::move(other));

			if (this != &other)
				m_auras = std::move(other.m_auras);

			return *this;
		}

		inline virtual void setPos(const PosF& pos) noexcept override
		{
			if (this->getItem())
			{
				this->getItem()->setPos(pos.x, pos.y);

				for (auto& aura : m_auras)
					aura.setPos({ pos.x + static_cast<float>(this->getItem()->boundingRect().width() / 2), pos.y });
			}
		}

		inline virtual void update() noexcept override
		{
			GObject<_T>::update();

			for (auto& aura : m_auras)
				aura.update();
		}

	protected:
		std::vector<GraphicsAura> m_auras;
	};

	template<typename _T>
	using GObjectWithAura = GraphicsObjectWithAura<_T>;
} // namespace TowerDefence

#endif /* !__GRAPHICS_OBJECT_WITH_AURA_HPP_INCLUDED__ */