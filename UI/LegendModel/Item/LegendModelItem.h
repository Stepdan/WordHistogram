#pragma once

#include <memory>

#include "ILegendModelItem.h"

class LegendModelItem : public ILegendModelItem
{
public:
    LegendModelItem(const Item&);
    ~LegendModelItem();

public:
    const Item& GetItem() const override;
    void SetItem(const Item&) override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
