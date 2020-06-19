#pragma once

#include <utility>
#include <vector>

#include <QString>

class QStringList;

using Item = std::pair<QString, size_t>;
using Items = std::vector<Item>;

namespace WordHistogram::Interfaces
{

class IHistogram
{
public:
    virtual ~IHistogram() = default;

    virtual void AddItems(const QStringList&) = 0;

    virtual Items GetItems() const = 0;
};

}
