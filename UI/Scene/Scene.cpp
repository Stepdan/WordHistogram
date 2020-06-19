#include <cassert>

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QWheelEvent>

#include "Scene.h"

namespace {

constexpr double SCALE_UP_FACTOR = 1.1;
constexpr double SCALE_DOWN_FACTOR = 0.9;

}

class Scene::Impl
{
public:
    QGraphicsScene& Scene()
    {
        return m_scene;
    }

private:
    QGraphicsScene m_scene;
};

Scene::Scene(QWidget* parent)
    : QGraphicsView(parent)
    , m_impl(std::make_unique<Impl>())
{
    m_impl->Scene().setParent((parent));
    setScene(&m_impl->Scene());
}

//.....................................................................................

Scene::~Scene() = default;

//.....................................................................................

void Scene::wheelEvent(QWheelEvent* event)
{
    static double factor;

    factor = (event->delta() > 0) ? SCALE_UP_FACTOR : SCALE_DOWN_FACTOR;

    const QPointF viewportPos = underMouse() ? mapFromGlobal(QCursor::pos()) : QPointF();
    const QPointF scenePos = mapToScene(viewportPos.toPoint());

    scale(factor, factor);

    if(!viewportPos.isNull())
    {
        centerOn(scenePos);
        QPointF viewportDelta = viewportPos - QPointF(viewport()->width() / 2., viewport()->height() / 2.);
        QPointF viewportCenter = mapFromScene(scenePos) - viewportDelta;
        centerOn(mapToScene(viewportCenter.toPoint()));
    }

    update();
}

//.....................................................................................
