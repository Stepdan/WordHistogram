#include <map>

#include <QStringList>

#include "Util/FindPair.h"

#include "Histogram.h"

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
        if(auto findIt(Util::FindIteratorByFirst(m_items.begin(), m_items.end(), item.first)); findIt != m_items.cend())
            findIt->second = item.second;
        else if(m_items.size() < TOP_SIZE)
            m_items.push_back(item);
        else if(auto minIt(std::min_element(m_items.begin(), m_items.end(), [](const Item& i0, const Item& i1) { return i0.second < i1.second; })); minIt->second < item.second)
            *minIt = item;
    }

    Items GetItems() const noexcept { return m_items; }

    void Clear() { m_items.clear(); }

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
        {
            const auto lowerWord = word.toLower();
            m_topList.AddItem({ lowerWord, ++m_histogram[lowerWord] });
        }
    }

    Items GetItems() const noexcept
    {
        return m_topList.GetItems();
    }

    void Clear()
    {
        m_histogram.clear();
        m_topList.Clear();
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

//.....................................................................................

void Histogram::Clear()
{
    m_impl->Clear();
}

}
