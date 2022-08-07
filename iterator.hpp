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


    //pointer 
    template <typename T>
    struct iterator_traits<T*>
    {
        typedef typename T::difference_type difference_type;
        typedef typename T::value_type value_type;
        typedef typename T::pointer pointer;
        typedef typename T::reference reference;
        typedef typename T::iterator_gategory iteraror_gategory;
    };


    //const pointer
    template <typename T>
    struct iterator_traits<const T*>
    {
        typedef typename T::difference_type difference_type;
        typedef typename T::value_type value_type;
        typedef typename T::pointer pointer;
        typedef typename T::reference reference;
        typedef typename T::iterator_gategory iteraror_gategory;
    }; 

    //enable_if
    template<bool Cond, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { 
        typedef T type;
    };

    
}


