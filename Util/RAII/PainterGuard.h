#pragma once

#include <QPainter>

namespace Util
{

class PainterGuard
{
public:
    PainterGuard(QPainter *obj)
        : m_obj(obj)
    {
        m_obj->save();
    }
    ~PainterGuard()
    {
        m_obj->restore();
    }

private:
    QPainter * const m_obj;
};

}
