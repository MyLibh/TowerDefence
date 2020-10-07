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
		inline static constexpr auto WIDTH{ 30 };
		inline static constexpr auto HEIGHT{ 10 };

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