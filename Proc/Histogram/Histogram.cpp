#include <map>

#include <QStringList>

#include "Histogram.h"

namespace
{

bool operator<(const Item& i0, const Item& i1)
{
    return i0.second < i1.second;
}

bool operator==(const Item& i0, const Item& i1)
{
    return i0.first == i1.first;
}

}

namespace
{

constexpr int TOP_SIZE = 15;

class TopList
{
public:
    TopList()
    {
         m_items.reserve(TOP_SIZE);
    }

    void AddItem(const Item& item)
    {
        if(auto findIt(std::find(m_items.begin(), m_items.end(), item)); findIt != m_items.cend())
            findIt->second = item.second;
        else if(m_items.size() < TOP_SIZE)
            m_items.push_back(item);
        else if(auto minIt(std::min_element(m_items.begin(), m_items.end())); minIt->second < item.second)
            *minIt = item;
    }

    Items GetItems() const noexcept { return m_items; }

private:
    Items m_items;
};

}

namespace Proc
{

class Histogram::Impl
{
public:
    void AddItems(const QStringList& list)
    {
        for(const auto& word : list)
            m_topList.AddItem({ word, ++m_histogram[word] });
    }

    Items GetItems() const noexcept
    {
        return m_topList.GetItems();
    }

private:
    std::map<QString, size_t> m_histogram;
    TopList m_topList;
};

//.....................................................................................

Histogram::Histogram()
    : m_impl(std::make_unique<Impl>())
{}

//.....................................................................................

Histogram::~Histogram() = default;

//.....................................................................................

void Histogram::AddItems(const QStringList& list)
{
    m_impl->AddItems(list);
}

//.....................................................................................

Items Histogram::GetItems() const
{
    return m_impl->GetItems();
}

}
