#pragma once

#include <QStyledItemDelegate>
#include <QPointer>

class LegendModelDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit LegendModelDelegate(QObject* parent = nullptr);

public:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};
