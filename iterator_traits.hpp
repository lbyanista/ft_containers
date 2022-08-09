#pragma once

#include <iostream>
#include <iterator>
#include <cstddef>

namespace ft
{
    template <typename T>
    struct iterator_traits
    {
        typedef typename T::difference_type difference_type;
        typedef typename T::value_type value_type;
        typedef typename T::pointer pointer;
        typedef typename T::reference reference;
        typedef typename T::iterator_gategory iterator_category;
    };

    //pointer 
    template <typename T>
    struct iterator_traits<T*>
    {
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference reference;
        typedef std::random_access_iterator_tag iterator_category;//need more info
    };


    //const pointer
    template <typename T>
    struct iterator_traits<const T*>
    {
        typedef const ptrdiff_t difference_type;
        typedef const T value_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef const std::random_access_iterator_tag iterator_category;
    }; 
};