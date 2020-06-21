#include <functional>

#include <QBrush>
#include <QGraphicsRectItem>

#include "Drawer.h"

namespace
{

constexpr int WIDTH  = 600;
constexpr int HEIGHT = 600;

const QPoint g_point0 = QPoint(0, 0);

}

class Drawer::Impl
{
public:
    Impl(QGraphicsScene* scene)
        : m_scene(scene)
    {}

    void Draw(const Items& items)
    {
        m_scene->clear();

        const auto maxValue = std::max_element(items.cbegin(), items.cend(), std::bind(std::less<size_t>{}, std::bind(&Item::second, std::placeholders::_1), std::bind(&Item::second, std::placeholders::_2)))->second;
        const auto colWidth = WIDTH / items.size();

        for(size_t i = 0, size = items.size(); i < size; ++i)
        {
            const auto height = (1.0 * items[i].second / maxValue) * HEIGHT;
            QGraphicsRectItem* rectItem = new QGraphicsRectItem(g_point0.x() + i * colWidth, 0, colWidth, -height);
            rectItem->setBrush(QBrush(GetColor(i, size)));
            m_scene->addItem(rectItem);
        }
    }

private:
    QColor GetColor(size_t index, size_t count)
    {
        return QColor::fromHsv((1.0 * index / count) * 360, 255, 255);
    }

private:
    QGraphicsScene* m_scene;
};

//.....................................................................................

Drawer::Drawer(QGraphicsScene* scene)
    : m_impl(std::make_unique<Impl>(scene))
{

}

//.....................................................................................

Drawer::~Drawer() = default;

//.....................................................................................

void Drawer::Draw(const Items& items)
{
    m_impl->Draw(items);
}
