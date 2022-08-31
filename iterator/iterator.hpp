#pragma once
#include <iostream>

#include "iterator_traits.hpp"


namespace ft
{
    template <typename T>
    class random_access_iterator
    {
        private:
            pointer _ptr;
            random_access_iterator(const reference current){
                _ptr = current;
            }   

        public:
        typedef typename iterator_traits<T>::value_type value_type;
        typedef typename iterator_traits<T>::difference_type difference_type;
        typedef typename iterator_traits<T>::pointer pointer;
        typedef typename iterator_traits<T>::reference reference;
        typedef typename iterator_traits<T>::iterator_category iterator_category;

        pointer base(void) const
        {
            return _ptr;
        }

        random_access_iterator(void) {
            _ptr = T();
        }

        random_access_iterator(pointer ptr) {
            _ptr = ptr;
        }

        template<typename T>
        random_access_iterator(const random_access_iterator<T>& other) {
            *this = other;
        }

        template<typename T>
        random_access_iterator<T>& operator=(const random_access_iterator<T>& other) {
            _ptr = other.base();
            return *this;
        }

        random_access_iterator<T>& operator++(void) {
            ++_ptr;
            return *this;
        }

        random_access_iterator<T> operator++(int) {
            random_access_iterator<T> tmp = *this;
            ++_ptr;
            return tmp;
        }

        random_access_iterator<T>& operator--(void) {
            --_ptr;
            return *this;
        }

        random_access_iterator<T> operator--(int) {
            random_access_iterator<T> tmp = *this;
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

        random_access_iterator<T> operator+(difference_type n) const {
            return random_access_iterator<T>(_ptr + n);
        }

        random_access_iterator<T> operator-(difference_type n) const {
            return random_access_iterator<T>(_ptr - n);
        }

        random_access_iterator<T>& operator+=(difference_type n) {
            _ptr += n;
            return *this;
        }

        random_access_iterator<T>& operator-=(difference_type n) {
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
    bool operator==(const random_access_iterator<TL>& lhs, const random_access_iterator<TR>& rhs) {
        return lhs.base() == rhs.base();
    }

    template <typename TL, typename TR>
    bool operator!=(const random_access_iterator<TL>& lhs, const random_access_iterator<TR>& rhs) {
        return !(lhs == rhs);
    }

    template <typename TL, typename TR>
    bool operator<(const random_access_iterator<TL>& lhs, const random_access_iterator<TR>& rhs) {
        return lhs.base() < rhs.base();
    }

    template <typename TL, typename TR>
    bool operator>(const random_access_iterator<TL>& lhs, const random_access_iterator<TR>& rhs) {
        return lhs.base() > rhs.base();
    }

    template <typename TL, typename TR>
    bool operator<=(const random_access_iterator<TL>& lhs, const random_access_iterator<TR>& rhs) {
        return lhs.base() <= rhs.base();
    }

    template <typename TL, typename TR>
    bool operator>=(const random_access_iterator<TL>& lhs, const random_access_iterator<TR>& rhs) {
        return lhs.base() >= rhs.base();
    }

    template <typename T>
    random_access_iterator<T> operator+(const typename random_access_iterator<T>::different_type &n, const random_access_iterator<T> &it) {
        return n + it.base();
    }

    template <typename TL, typename TR>
    typename random_access_iterator<TL>::difference_type operator-(const random_access_iterator<TL>& lhs, const random_access_iterator<TR>& rhs) {
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
