#pragma once

#include "Proc/Interfaces/IHistogram.h"

class ILegendModelItem
{
public:
    using Ptr = ILegendModelItem*;

public:
    virtual ~ILegendModelItem() = default;

    virtual const Item& GetItem() const = 0;
    virtual void SetItem(const Item&) = 0;
};
