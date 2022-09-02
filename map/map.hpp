#pragma once

#include "../utility/pair.hpp"
#include <iostream>

namespace ft {
    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
    class map {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef std::pair<const Key, T> value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef T& reference;
        typedef const T& const_reference;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef std::ptrdiff_t difference_type;
        typedef size_t size_type;

        class value_compare {
            friend class map;
        protected:
            Compare comp;
            value_compare(Compare c) : comp(c) {}
        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator()(const value_type& x, const value_type& y) const {
                return comp(x.first, y.first);
            }

            explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()){
                std::cout << "map constructor" << std::endl;}
            template <class InputIterator>
            map (InputIterator first, InputIterator last,
              const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()){
                std::cout << "map constructor" << std::endl;}

            map (const map& x){
                *this = x;}
            }
            ~map(){
                std::cout << "map destructor" << std::endl;}

            map& operator= (const map& x){
                return *this;
                }
            
            };
};