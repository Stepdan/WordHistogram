#pragma once

#include <algorithm>
#include <cassert>
#include <functional>
#include <iterator>
#include <type_traits>

namespace Util
{

template<typename FuncType, typename ArgType> struct isBoolResultOfFunctionWithTwoSameTypeParams
{
private:
    static void detect(...);
    template<typename Func, typename Arg>
    static decltype(std::declval<Func>()(std::declval<Arg>(), std::declval<Arg>())) detect(const Func&, const Arg&);

public:
    static constexpr bool value = std::is_same<bool, decltype(detect(std::declval<FuncType>(), std::declval<ArgType>()))>::value;
};

//.............................................................................

template
    < typename InputIterator
    , typename Value = typename std::iterator_traits<InputIterator>::value_type
    , typename KeyEqual = std::equal_to<typename Value::first_type>
    >
const typename std::enable_if_t<isBoolResultOfFunctionWithTwoSameTypeParams<KeyEqual, typename Value::first_type>::value, InputIterator>
FindIteratorByFirst(InputIterator begin, InputIterator end, const typename Value::first_type &key, KeyEqual comparer = KeyEqual{})
{
    return std::find_if(begin, end, std::bind(comparer, key, std::bind(&Value::first, std::placeholders::_1)));
}

//.............................................................................

template
    < typename InputIterator
    , typename Value = typename std::iterator_traits<InputIterator>::value_type
    , typename KeyEqual = std::equal_to<typename Value::first_type>
    >
const typename std::enable_if_t<isBoolResultOfFunctionWithTwoSameTypeParams<KeyEqual, typename Value::first_type>::value, const typename Value::second_type&>
FindSecond(InputIterator begin, InputIterator end, const typename Value::first_type &key, KeyEqual comparer = KeyEqual{})
{
    const auto it = FindPairIteratorByFirst(begin, end, key, comparer);
    assert(it != end);
    return it->second;
}

}
