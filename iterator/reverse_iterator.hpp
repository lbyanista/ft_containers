#pragma once
#include <iostream>
#include <iterator>

namespace ft
{
    template <typename T>
    struct reverse_iterator
    {
        typedef T iterator_type;
        typedef iterator_traits<Iterator>::iterator_category iterator_category;
        typedef iterator_traits<Iterator>::value_type value_type;
        typedef iterator_traits<Iterator>::difference_type difference_type;
        typedef iterator_traits<Iterator>::pointer pointer;
        typedef iterator_traits<Iterator>::reference reference;

        private:
            iterator_type current;

        public:
            reverse_iterator() {}
            explicit reverse_iterator (iterator_type it){ current = it; }
            template <class Iter>
            reverse_iterator (const reverse_iterator<Iter>& rev_it){ current = rev_it.base(); }

            iterator_type base() const{
                return current;
            }

            reference operator*() const{
                iterator_type tmp = current;
                return *(--tmp);
            }

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
                return &(operator*());
            }

            reference operator[] (difference_type n) const{
                return *(*this + n);
            }
    };//end of reverse_iterator

    template <class Iterator>
    bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
        return lhs.base() == rhs.base();
    }

    template <class Iterator>
    bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
        return !(lhs == rhs);
    }

    template <class Iterator>
    bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
        return rhs.base() < lhs.base();
    }

    template <class Iterator>
    bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
        return !(rhs < lhs);
    }

    template <class Iterator>
    bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
        return rhs < lhs;
    }

    template <class Iterator>
    bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
        return !(lhs < rhs);
    }

    template <class Iterator>
    reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n,
        const reverse_iterator<Iterator>& rev_it){
        return reverse_iterator<Iterator>(rev_it.base() - n);
    }

    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs,
            const reverse_iterator<Iterator>& rhs){
        return rhs.base() - lhs.base();
    }
};