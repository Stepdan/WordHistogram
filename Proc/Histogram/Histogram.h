#pragma once

#include <memory>

#include "Proc/Interfaces/IHistogram.h"

namespace Proc
{

class Histogram : public Interfaces::IHistogram
{
public:
    Histogram();
    ~Histogram();

public:
    void AddItems(const QStringList&) override;
    Items GetItems() const override;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

}
