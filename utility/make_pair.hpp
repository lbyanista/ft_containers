#pragma once
#include "pair.hpp"

namespace ft
{
    template <class T1, class T2>
    pair<T1, T2> make_pair(const T1& x, const T2& y)
    {
        return pair<T1, T2>(x, y);
    }
};