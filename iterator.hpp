#pragma once

#include <iostream>

namespace ft
{
    template <typename T>
    struct iterator_traits
    {
        typedef typename T::difference_type difference_type;
        typedef typename T::value_type value_type;
        typedef typename T::pointer pointer;
        typedef typename T::reference reference;
        typedef typename T::iterator_gategory iteraror_gategory;
    };

    template <typename T>
    struct iterator_traits<T*>
    {
        typedef typename T::difference_type difference_type;
        typedef typename T::value_type value_type;
        typedef typename T::pointer pointer;
        typedef typename T::reference reference;
        typedef typename T::iterator_gategory iteraror_gategory;
    };

    template <typename T>
    struct iterator_traits<const T*>
    {
        typedef typename T::difference_type difference_type;
        typedef typename T::value_type value_type;
        typedef typename T::pointer pointer;
        typedef typename T::reference reference;
        typedef typename T::iterator_gategory iteraror_gategory;
    }; 
}


