#pragma once
#include <iostream>

#include "iterator_traits.hpp"


namespace ft
{
    template <typename T>
    struct vec_iterator
    {
        typedef T* iterator_type;
        typedef typename iterator_traits<T*>::value_type value_type;
        typedef typename iterator_traits<T*>::iterator_category iterator_category;
        typedef typename iterator_traits<T*>::difference_type difference_type;
        typedef typename iterator_traits<T*>::pointer pointer;
        typedef typename iterator_traits<T*>::reference reference;

        private:
            iterator_type current;

        public:
            vec_iterator() {}
            explicit vec_iterator (iterator_type it){ current = it; }
            template <class Iter>
            vec_iterator (const vec_iterator<Iter>& v_it){ current = v_it.base(); }

            iterator_type base() const{
                return current;
            }

            reference operator*() const{
                return *(current);
            }

            vec_iterator operator+ (difference_type n) const{
                return vec_iterator(current - n);
            }

            vec_iterator& operator++(){
                ++current;
                return *this;
            }
            vec_iterator operator++ (int){
                vec_iterator tmp = *this;
                ++current;
                return tmp;
            }

            vec_iterator& operator+= (difference_type n){
                current += n;
                return *this;
            }

            vec_iterator operator- (difference_type n) const{
                return vec_iterator(current - n);
            }

            vec_iterator& operator--(){
                --current;
                return *this;
            }

            vec_iterator operator-- (int){
                vec_iterator tmp = *this;
                --current;
                return tmp;
            }

            vec_iterator& operator-= (difference_type n){
                current -= n;
                return *this;
            }

            pointer operator->() const{
                return &(operator*());
            }

            reference operator[] (difference_type n) const{
                return *(*this + n);
            }
    };//end of vec_iterator

    template <class Iterator>
    bool operator== (const vec_iterator<Iterator>& lhs, const vec_iterator<Iterator>& rhs){
        return lhs.base() == rhs.base();
    }

    template <class Iterator>
    bool operator!= (const vec_iterator<Iterator>& lhs, const vec_iterator<Iterator>& rhs){
        return !(lhs == rhs);
    }

    template <class Iterator>
    bool operator<  (const vec_iterator<Iterator>& lhs, const vec_iterator<Iterator>& rhs){
        return rhs.base() > lhs.base();
    }

    template <class Iterator>
    bool operator<= (const vec_iterator<Iterator>& lhs, const vec_iterator<Iterator>& rhs){
        return !(rhs < lhs);
    }

    template <class Iterator>
    bool operator>  (const vec_iterator<Iterator>& lhs, const vec_iterator<Iterator>& rhs){
        return rhs < lhs;
    }

    template <class Iterator>
    bool operator>= (const vec_iterator<Iterator>& lhs, const vec_iterator<Iterator>& rhs){
        return !(lhs < rhs);
    }

    template <class Iterator>
    vec_iterator<Iterator> operator+ (typename vec_iterator<Iterator>::difference_type n,
        const vec_iterator<Iterator>& v_it){
        return vec_iterator<Iterator>(v_it.base() + n);
    }

    template <class Iterator>
    typename vec_iterator<Iterator>::difference_type operator- (const vec_iterator<Iterator>& lhs,
            const vec_iterator<Iterator>& rhs){
        return lhs.base() - rhs.base();
    }
};
