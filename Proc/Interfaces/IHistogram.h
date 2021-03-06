#pragma once

#include <utility>
#include <vector>

#include <QString>

class QStringList;

using Item = std::pair<QString, size_t>;
using Items = std::vector<Item>;

namespace Proc::Interfaces
{

class IHistogram
{
public:
    virtual ~IHistogram() = default;

    virtual void AddItems(const QStringList&) = 0;

    virtual Items GetItems() const = 0;

    virtual void Clear() = 0;
};

}
