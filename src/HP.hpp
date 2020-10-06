#ifndef __HP_HPP_INCLUDED__
#define __HP_HPP_INCLUDED__

#include "Pos.hpp"

#include <memory>

class QGraphicsScene;
class QGraphicsRectItem;

namespace TowerDefence
{
	class HP
	{
	private:
		_INLINE_VAR static _CONSTEXPR20 auto WIDTH{ 30 };
		_INLINE_VAR static _CONSTEXPR20 auto HEIGHT{ 10 };

	public:
		HP(std::shared_ptr<QGraphicsScene> scene);

		void setPos(const PosF& pos);

		void setHP(const float percent);

	private:
		QGraphicsRectItem* m_back;
		QGraphicsRectItem* m_front;
	};
} // namespace TowerDefence

#endif /* !__HP_HPP_INCLUDED__ */