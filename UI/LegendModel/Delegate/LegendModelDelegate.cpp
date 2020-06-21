#include <QAbstractItemView>
#include <QImage>
#include <QPainter>

#include "Util/RAII/PainterGuard.h"

#include "UI/LegendModel/DeclareMetatype.h"
#include "UI/LegendModel/LegendModelRoles.h"

#include "LegendModelDelegate.h"

constexpr int FONT_SIZE    = 12;
constexpr int TEXT_X_SHIFT = 125;

const QPoint ITEM_POINT0 = QPoint(10, 10);

const std::vector<int> g_shifts = { 20, 50, 80 };

//.............................................................................

LegendModelDelegate::LegendModelDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{}

//.............................................................................

void LegendModelDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    Util::PainterGuard guard(painter);

    const auto itemRect = option.rect;

    const QPoint startPoint(option.rect.left(), option.rect.top());

    const auto [ word, frequency ] = index.data(static_cast<int>(LegendModelRoles::Item)).value<Item>();

    auto font = painter->font();
    font.setPixelSize(FONT_SIZE);
    painter->setFont(font);
    painter->drawText(QPoint(startPoint.x() + 60, startPoint.y() + 25), word + " - " + QString::number(frequency));

    // @todo Сделать универсальное получение цвета. Прошу прощения, не успел.
    painter->setBrush(QColor::fromHsv((1.0 * index.row() / 15) * 360, 255, 255));
    painter->drawRect(startPoint.x() + 10, startPoint.y() + 10, 30, 30);

    painter->drawLine(itemRect.bottomLeft(), itemRect.bottomRight());
}

//.............................................................................

QSize LegendModelDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return QSize(250, 50);
}
