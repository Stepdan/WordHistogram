#pragma once

#include <memory>
#include <vector>

#include <QAbstractListModel>

#include "Proc/Interfaces/IHistogram.h"

class LegendModel : public QAbstractListModel
{
    Q_OBJECT

public:
    LegendModel(QObject *parent = nullptr);
    ~LegendModel();

public:
    int rowCount(const QModelIndex& = QModelIndex()) const override;
    int columnCount(const QModelIndex& = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    void Reset(const Items& data);

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};
