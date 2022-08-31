#pragma once
#include "iterator.hpp"

namespace ft
{
    template <typename T>
    class reverse_iterator
    {
        typedef T iterator_type;
        typedef typename iterator_traits<T>::iterator_category iterator_category;
        typedef typename iterator_traits<T>::value_type value_type;
        typedef typename iterator_traits<T>::difference_type difference_type;
        typedef typename iterator_traits<T>::pointer pointer;
        typedef typename iterator_traits<T>::reference reference;

        private:
            iterator_type current;

        public:
            reverse_iterator(): current() {}
            explicit reverse_iterator (iterator_type it){ current = it; }
            template <class Iter>
            reverse_iterator (const reverse_iterator<Iter>& rev_it){ *this = rev_it; }
            template <class Iter>
            reverse_iterator& operator= (const reverse_iterator<Iter>& rev_it){ current = rev_it.base(); return *this; }

            iterator_type base() const{
                return current;
            }

            // reference operator*() const{
            //     iterator_type tmp = current;
            //     return *(--tmp);
            // }

            reverse_iterator operator+ (difference_type n) const{
                return reverse_iterator(current - n);
            }

            reverse_iterator& operator++(){
                --current;
                return *this;
            }
            reverse_iterator operator++ (int){
                reverse_iterator tmp = *this;
                --current;
                return tmp;
            }

            reverse_iterator& operator+= (difference_type n){
                current -= n;
                return *this;
            }

            reverse_iterator operator- (difference_type n) const{
                return reverse_iterator(current + n);
            }

            reverse_iterator& operator--(){
                ++current;
                return *this;
            }

            reverse_iterator operator-- (int){
                reverse_iterator tmp = *this;
                ++current;
                return tmp;
            }

            reverse_iterator& operator-= (difference_type n){
                current += n;
                return *this;
            }

            pointer operator->() const{
                iterator_type tmp = current;
                return &(*(--tmp));
            }

            reference operator[] (difference_type n) const{
                return ((current - 1).operator[](n));
            }
    };//end of reverse_iterator


    template <typename TL, typename TR>
    bool operator== (const reverse_iterator<TL>& lhs, const reverse_iterator<TR>& rhs){
        return (lhs.base() == rhs.base());
    }

    template <typename TL, typename TR>
    bool operator!= (const reverse_iterator<TL>& lhs, const reverse_iterator<TR>& rhs){
        return (lhs.base() != rhs.base());
    }

    template <typename TL, typename TR>
    bool operator< (const reverse_iterator<TL>& lhs, const reverse_iterator<TR>& rhs){
        return (lhs.base() > rhs.base());
    }

    template <typename TL, typename TR>
    bool operator<= (const reverse_iterator<TL>& lhs, const reverse_iterator<TR>& rhs){
        return (lhs.base() >= rhs.base());
    }

    template <typename TL, typename TR>
    bool operator> (const reverse_iterator<TL>& lhs, const reverse_iterator<TR>& rhs){
        return (lhs.base() < rhs.base());
    }

    template <typename TL, typename TR>
    bool operator>= (const reverse_iterator<TL>& lhs, const reverse_iterator<TR>& rhs){
        return (lhs.base() <= rhs.base());
    }

    template <typename T>
    reverse_iterator<T> operator+ (typename reverse_iterator<T>::difference_type n, const reverse_iterator<T>& rev_it){
        return reverse_iterator<T>(rev_it.base() - n);
    }

    template <typename T>
    typename reverse_iterator<T>::difference_type operator- (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs){
        return (rhs.base() - lhs.base());
    }

    // template <class Iterator>
    // bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
    //     return lhs.base() == rhs.base();
    // }

    // template <class Iterator>
    // bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
    //     return !(lhs == rhs);
    // }

    // template <class Iterator>
    // bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
    //     return rhs.base() < lhs.base();
    // }

    // template <class Iterator>
    // bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
    //     return !(rhs < lhs);
    // }

    // template <class Iterator>
    // bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
    //     return rhs < lhs;
    // }

    // template <class Iterator>
    // bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
    //     return !(lhs < rhs);
    // }

    // template <class Iterator>
    // reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n,
    //     const reverse_iterator<Iterator>& rev_it){
    //     return reverse_iterator<Iterator>(rev_it.base() - n);
    // }

    // template <class Iterator>
    // typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs,
    //         const reverse_iterator<Iterator>& rhs){
    //     return rhs.base() - lhs.base();
    // }
};