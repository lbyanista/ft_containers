#pragma once

namespace ft
{
    template <class InputIteratorL, class InputIteratorR>
    bool lexicographical_compare(InputIteratorL first1, InputIteratorL last1, InputIteratorR first2, InputIteratorR last2)
    {
        while (first1 != last1)
        {
            if(first2 == last2 || *first2 < *first1)
                return false;
            else if(*first1 < *first2)
                return true;
            ++first1;
            ++first2;
        }
        return first2 != last2;
    }

    template <class InputIteratorL, class InputIteratorR, class Compare>
    bool lexicographical_compare(InputIteratorL first1, InputIteratorL last1, InputIteratorR first2, InputIteratorR last2, Compare comp)
    {
        while (first1 != last1)
        {
            if(first2 == last2 || comp(*first2, *first1))
                return false;
            else if(comp(*first1, *first2))
                return true;
            ++first1;
            ++first2;
        }
        return first2 != last2;
    }
};