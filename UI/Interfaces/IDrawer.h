#pragma once

#include "Proc/Interfaces/IHistogram.h"

namespace Interfaces
{

class IDrawer
{
public:
    virtual ~IDrawer() = default;

    virtual void Draw(const Items&) = 0;
};

}
