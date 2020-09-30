#ifndef __GRAPHICS_HPP_INCLUDED__
#define __GRAPHICS_HPP_INCLUDED__

#include <memory>
#include <vector>
#include <map>
#include <string>

#include <QtGlobal>

class QGraphicsScene;
class QGraphicsLineItem;
class QPixmap;

namespace TowerDefence
{
	class Landscape;

	class Graphics
	{
	private:
		void loadImages();

		void createGrid(const float width, const float height, const float dx, const float dy);

	public:
		inline Graphics() :
			m_scene(std::make_unique<QGraphicsScene>()),
			m_grid(),
			m_images()
		{ }

		inline ~Graphics() noexcept = default;

		_NODISCARD
		inline auto& getScene() const noexcept { return m_scene; }

		void createMap(const float dx, const float dy, const std::shared_ptr<Landscape> landscape);

		void draw() const;

	private:
		std::unique_ptr<QGraphicsScene> m_scene;
		std::vector<QGraphicsLineItem*> m_grid[2];
		std::map<std::string, QPixmap>  m_images;
	};
} // namespace TowerDefence

#endif /* !__GRAPHICS_HPP_INCLUDED__ */