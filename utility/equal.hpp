#pragma once

namespace ft
{
    template<class InputIteratorL, class InputIteratorR>
    bool equal(InputIteratorL first1, InputIteratorL last1, InputIteratorR first2)
    {
        while (first1 != last1)
        {
            if (*first1 != *first2)
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }

    template<class InputIteratorL, class InputIteratorR, class BinaryPredicate>
    bool equal(InputIteratorL first1, InputIteratorL last1, InputIteratorR first2, BinaryPredicate binary_pred)
    {
        while (first1 != last1)
        {
            if (!binary_pred(*first1, *first2))
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }
};