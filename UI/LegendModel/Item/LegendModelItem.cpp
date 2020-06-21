#include "LegendModelItem.h"

struct LegendModelItem::Impl
{
    Impl(const Item& i)
        : item(i)
    {}

    Item item;
};

//.....................................................................................

LegendModelItem::LegendModelItem(const Item& item)
    : m_impl(new Impl(item))
{}

//.....................................................................................

LegendModelItem::~LegendModelItem() = default;

//.....................................................................................

const Item& LegendModelItem::GetItem() const
{
    return m_impl->item;
}

//.....................................................................................

void LegendModelItem::SetItem(const Item& item)
{
    m_impl->item = item;
}
