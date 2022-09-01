#pragma once
#include <iostream>

namespace ft
{
    template <class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        T1 first;
        T2 second;

        pair() : first(), second(){}

        template <class U1, class U2>
        pair(const pair<U1, U2>& p) : first(p.first), second(p.second){}

        pair(const T1& x, const T2& y) : first(x), second(y){}

        pair &operator=(const pair& p)
        {
            first = p.first;
            second = p.second;
            return *this;
        }
    };

    template <class T1, class T2>
    bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return x.first == y.first && x.second == y.second;
    }

    template <class T1, class T2>
    bool operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return !(x == y);
    }

    template <class T1, class T2>
    bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
    }

    template <class T1, class T2>
    bool operator>(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return y < x;
    }

    template <class T1, class T2>
    bool operator<=(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return !(y < x);
    }

    template <class T1, class T2>
    bool operator>=(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return !(x < y);
    }

    template <class T1, class T2>
    std::ostream& operator<<(std::ostream& os, const pair<T1, T2>& p)
    {
        os << '(' << p.first << ", " << p.second << ')';
        return os;
    }
    
};