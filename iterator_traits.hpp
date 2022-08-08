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

//is_integral

    template <class T>
    struct is_integral {static const bool value = false}; //if T not intergal || not found in Fundamental integral types

    template <>
    struct is_integral<bool> {static const bool value = true};

    template <>
    struct is_integral<char> {static const bool value = true};

    template <>
    struct is_integral<char16_t> {static const bool value = true};

    template <>
    struct is_integral<char32_t> {static const bool value = true};

    template <>
    struct is_integral<wchar_t> {static const bool value = true};

    template <>
    struct is_integral<signed char> {static const bool value = true};

    template <>
    struct is_integral<short int> {static const bool value = true};

    template <>
    struct is_integral<int> {static const bool value = true};

    template <>
    struct is_integral<long int> {static const bool value = true};

    template <>
    struct is_integral<long long int> {static const bool value = true};

    template <>
    struct is_integral<unsigned char> {static const bool value = true};

    template <>
    struct is_integral<unsigned short int> {static const bool value = true};

    template <>
    struct is_integral<unsigned int> {static const bool value = true};

    template <>
    struct is_integral<unsigned long int> {static const bool value = true};

    template <>
    struct is_integral<unsigned long long int> {static const bool value = true};
}