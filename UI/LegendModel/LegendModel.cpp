#include <QAction>
#include <QApplication>
#include <QClipboard>

#include "Item/LegendModelItem.h"
#include "DeclareMetatype.h"
#include "LegendModelRoles.h"

#include "LegendModel.h"

class LegendModel::Impl
{
public:
    std::vector<std::unique_ptr<ILegendModelItem>> m_items;
};

//.............................................................................

LegendModel::LegendModel(QObject *parent/* = nullptr*/)
    : QAbstractListModel(parent)
    , m_impl(new Impl())
{
}

//.............................................................................

LegendModel::~LegendModel() = default;

//.............................................................................

int LegendModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(m_impl->m_items.size() / columnCount());
}

//.............................................................................

int LegendModel::columnCount(const QModelIndex&) const
{
    return 1;
}

//.............................................................................

QVariant LegendModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
    {
        switch (static_cast<LegendModelRoles>(role))
        {
            case LegendModelRoles::Count:
                return QVariant::fromValue(static_cast<int>(m_impl->m_items.size()));

            default:
                assert(!"Invalid role");
                return QVariant();
        }
    }

    const auto r = index.row();

    if (r >= rowCount())
    {
        assert(!"Invalid row");
        return QVariant();
    }

    switch (static_cast<LegendModelRoles>(role))
    {
        case LegendModelRoles::Item:
            return QVariant::fromValue(m_impl->m_items[r]->GetItem());

        default:
            break;
    }

    return QVariant();
}

//.............................................................................

bool LegendModel::setData(const QModelIndex& index, const QVariant& value, int role /*= Qt::EditRole*/)
{
    if (!index.isValid())
    {
        switch (static_cast<LegendModelRoles>(role))
        {
            case LegendModelRoles::Items:
            {
                this->beginResetModel();
                Reset(value.value<Items>());
                this->endResetModel();
                return true;
            }

            default:
                assert(!"Invalid role");
                break;
        }
    }

    assert(index.isValid());

    const auto r = index.row();

    if (r >= rowCount())
        assert(!"Invalid row");

    switch (static_cast<LegendModelRoles>(role))
    {
        case LegendModelRoles::Item:
            m_impl->m_items[r]->SetItem(value.value<Item>());
            break;

        default:
            assert(!"Invalid role");
            break;
    }

    return true;
}

//.............................................................................

Qt::ItemFlags LegendModel::flags(const QModelIndex& index) const
{
    return QAbstractListModel::flags(index);
}

//.............................................................................

void LegendModel::Reset(const Items& data)
{
    m_impl->m_items.clear();
    std::transform(data.cbegin(), data.cend(), std::back_inserter(m_impl->m_items), [](const Item& item) { return std::make_unique<LegendModelItem>(item); });
}
