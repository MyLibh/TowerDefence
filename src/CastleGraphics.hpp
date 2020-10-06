#ifndef __CASTLE_GRAPHICS_HPP_INCLUDED__
#define __CASTLE_GRAPHICS_HPP_INCLUDED__

#include "Pos.hpp"
#include "HP.hpp"

#include <memory>

class QGraphicsScene;
class QGraphicsPixmapItem;
class QPixmap;

namespace TowerDefence
{
	class Castle;

	class CastleGraphics final
	{
	public:
		CastleGraphics(std::shared_ptr<QGraphicsScene> scene, QPixmap pixmap, std::shared_ptr<Castle> castle);

		void setPos(const PosF& pos);

		void draw() const;

	private:
		QGraphicsPixmapItem*    m_item;
		std::shared_ptr<Castle> m_castle;
		mutable HP              m_hp;
	};
} // namespace TowerDefence

#endif /* !__CASTLE_GRAPHICS_HPP_INCLUDED__ */