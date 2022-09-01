#pragma once
#include <iostream>

#include "iterator_traits.hpp"

namespace ft
{
    template <typename T>
    class vec_iterator
    {
        public:
        typedef typename iterator_traits<T*>::value_type value_type;
        typedef typename iterator_traits<T*>::difference_type difference_type;
        typedef typename iterator_traits<T*>::pointer pointer;
        typedef typename iterator_traits<T*>::reference reference;
        typedef typename iterator_traits<T*>::iterator_category iterator_category;

        private:
            pointer _ptr;

        public:
        vec_iterator(const reference current){
            _ptr = current;
        }   

        pointer base(void) const
        {
            return _ptr;
        }

        vec_iterator(void) {
            // _ptr = int();
        }

        vec_iterator(pointer ptr) {
            _ptr = ptr;
        }

        template<typename U>
        vec_iterator(const vec_iterator<U> &other) {
            // *this = other;
            this->_ptr = other.base();
        }

        template<typename U, typename V>
        vec_iterator<U>& operator=(const vec_iterator<V>& other) {
            _ptr = other.base();
            return *this;
        }

        vec_iterator<T>& operator++(void) {
            ++_ptr;
            return *this;
        }

        vec_iterator<T> operator++(int) {
            vec_iterator<T> tmp = *this;
            ++_ptr;
            return tmp;
        }

        vec_iterator<T>& operator--(void) {
            --_ptr;
            return *this;
        }

        vec_iterator<T> operator--(int) {
            vec_iterator<T> tmp = *this;
            --_ptr;
            return tmp;
        }

        reference operator*(void) const {
            return *_ptr;
        }

        pointer operator->(void) const {
            return _ptr;
        }

        reference operator[](difference_type n) const {
            return _ptr[n];
        }

        vec_iterator<T> operator+(difference_type n) const {
            return vec_iterator<T>(_ptr + n);
        }

        vec_iterator<T> operator-(difference_type n) const {
            return vec_iterator<T>(_ptr - n);
        }

        vec_iterator<T>& operator+=(difference_type n) {
            _ptr += n;
            return *this;
        }

        vec_iterator<T>& operator-=(difference_type n) {
            _ptr -= n;
            return *this;
        }
    };


    // struct vec_iterator
    // {
    //     typedef T* iterator_type;
    //     typedef typename iterator_traits<T*>::value_type value_type;
    //     typedef typename iterator_traits<T*>::iterator_category iterator_category;
    //     typedef typename iterator_traits<T*>::difference_type difference_type;
    //     typedef typename iterator_traits<T*>::pointer pointer;
    //     typedef typename iterator_traits<T*>::reference reference;

    //     private:
    //         iterator_type current;

    //     public:
    //         vec_iterator() {}
    //         explicit vec_iterator (iterator_type it){ current = it; }
    //         template <class Iter>
    //         vec_iterator (const vec_iterator<Iter>& v_it){ current = v_it.base(); }

    //         iterator_type base() const{
    //             return current;
    //         }

    //         reference operator*() const{
    //             return *(current);
    //         }

    //         vec_iterator operator+ (difference_type n) const{
    //             return vec_iterator(current - n);
    //         }

    //         vec_iterator& operator++(){
    //             ++current;
    //             return *this;
    //         }
    //         vec_iterator operator++ (int){
    //             vec_iterator tmp = *this;
    //             ++current;
    //             return tmp;
    //         }

    //         vec_iterator& operator+= (difference_type n){
    //             current += n;
    //             return *this;
    //         }

    //         vec_iterator operator- (difference_type n) const{
    //             return vec_iterator(current - n);
    //         }

    //         vec_iterator& operator--(){
    //             --current;
    //             return *this;
    //         }

    //         vec_iterator operator-- (int){
    //             vec_iterator tmp = *this;
    //             --current;
    //             return tmp;
    //         }

    //         vec_iterator& operator-= (difference_type n){
    //             current -= n;
    //             return *this;
    //         }

    //         pointer operator->() const{
    //             return &(operator*());
    //         }

    //         reference operator[] (difference_type n) const{
    //             return *(*this + n);
    //         }
    // };//end of vec_iterator


    template <typename TL, typename TR>
    bool operator==(const vec_iterator<TL>& lhs, const vec_iterator<TR>& rhs) {
        return lhs.base() == rhs.base();
    }

    template <typename TL, typename TR>
    bool operator!=(const vec_iterator<TL>& lhs, const vec_iterator<TR>& rhs) {
        return !(lhs == rhs);
    }

    template <typename TL, typename TR>
    bool operator<(const vec_iterator<TL>& lhs, const vec_iterator<TR>& rhs) {
        return lhs.base() < rhs.base();
    }

    template <typename TL, typename TR>
    bool operator>(const vec_iterator<TL>& lhs, const vec_iterator<TR>& rhs) {
        return lhs.base() > rhs.base();
    }

    template <typename TL, typename TR>
    bool operator<=(const vec_iterator<TL>& lhs, const vec_iterator<TR>& rhs) {
        return lhs.base() <= rhs.base();
    }

    template <typename TL, typename TR>
    bool operator>=(const vec_iterator<TL>& lhs, const vec_iterator<TR>& rhs) {
        return lhs.base() >= rhs.base();
    }

    template <typename T>
    vec_iterator<T> operator+(const typename vec_iterator<T>::difference_type &n, const vec_iterator<T> &it) {
        return n + it.base();
    }

    template <typename TL, typename TR>
    typename vec_iterator<TL>::difference_type operator-(const vec_iterator<TL>& lhs, const vec_iterator<TR>& rhs) {
        return lhs.base() - rhs.base();
    }

    // template <class Iterator>
    // bool operator== (const vec_iterator<Iterator>& lhs, const vec_iterator<Iterator>& rhs){
    //     return lhs.base() == rhs.base();
    // }

    // template <class Iterator>
    // bool operator!= (const vec_iterator<Iterator>& lhs, const vec_iterator<Iterator>& rhs){
    //     return !(lhs == rhs);
    // }

    // template <class Iterator>
    // bool operator<  (const vec_iterator<Iterator>& lhs, const vec_iterator<Iterator>& rhs){
    //     return rhs.base() > lhs.base();
    // }

    // template <class Iterator>
    // bool operator<= (const vec_iterator<Iterator>& lhs, const vec_iterator<Iterator>& rhs){
    //     return !(rhs < lhs);
    // }

    // template <class Iterator>
    // bool operator>  (const vec_iterator<Iterator>& lhs, const vec_iterator<Iterator>& rhs){
    //     return rhs < lhs;
    // }

    // template <class Iterator>
    // bool operator>= (const vec_iterator<Iterator>& lhs, const vec_iterator<Iterator>& rhs){
    //     return !(lhs < rhs);
    // }

    // template <class Iterator>
    // vec_iterator<Iterator> operator+ (typename vec_iterator<Iterator>::difference_type n,
    //     const vec_iterator<Iterator>& v_it){
    //     return vec_iterator<Iterator>(v_it.base() + n);
    // }

    // template <class Iterator>
    // typename vec_iterator<Iterator>::difference_type operator- (const vec_iterator<Iterator>& lhs,
    //         const vec_iterator<Iterator>& rhs){
    //     return lhs.base() - rhs.base();
    // }
};
