#pragma once
#include "iterator_traits.hpp"

namespace ft
{
    template <class iterator>
    class reverse_iterator
    {
        public:
        typedef iterator                                                    iterator_type;
        typedef typename ft::iterator_traits<iterator>::value_type          value_type;
        typedef typename ft::iterator_traits<iterator>::iterator_category   iterator_category;
        typedef typename ft::iterator_traits<iterator>::difference_type     difference_type;
        typedef typename ft::iterator_traits<iterator>::pointer             pointer;
        typedef typename ft::iterator_traits<iterator>::reference           reference;

        private:
            iterator_type _current;

        public:
        // constructors
        reverse_iterator() : _current() { }
        explicit reverse_iterator(iterator_type it) : _current(it) { }
        template<typename it2>
        reverse_iterator(const reverse_iterator<it2> &i) : _current(i.base()){ }

        // getter
        iterator_type base() const
        {
            return  (_current);
        }

        // operators

        reverse_iterator& operator=(const reverse_iterator& i)
        {
            this->_current = i._current;
            return (*this);
        }

        reference operator*()
        {
            iterator_type tmp;
            tmp = this->_current;
            return (*(--tmp));
        }

        pointer operator->()
        {
            return &(operator*());
        }

        reverse_iterator& operator++()
        {
            --this->_current;
            return (*this);
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator tmp;

            tmp._current = this->_current--;
            return (tmp);
        }

        reverse_iterator& operator--()
        {
            ++this->_current;
            return (*this);
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator tmp;

            tmp._current = this->_current++;
            return (tmp);
        }

        reverse_iterator operator+ (difference_type index)
        {
            reverse_iterator tmp;

            tmp._current = this->_current - index;
            return (tmp);
        }

        reverse_iterator operator-(difference_type index)
        {
            return (reverse_iterator(this->_current + index));
        }

        reverse_iterator &operator+= (difference_type index)
        {
            this->_current = this->_current - index;
            return (*this);
        }

        reverse_iterator &operator-= (difference_type index)
        {
            this->_current = this->_current + index;
            return (*this);
        }

        reference operator[] (difference_type index)
        {
            return (this->_current[index - 1]);
        }

        template<class it1, class it2>
        friend bool operator== (const reverse_iterator<it1> &ob1, const reverse_iterator<it2> &ob2);

        template<class it1, class it2>
        friend bool operator!= (const reverse_iterator<it1> &ob1, const reverse_iterator<it2> &ob2);

        template<class it1, class it2>
        friend bool operator> (const reverse_iterator<it1> &ob1, const reverse_iterator<it2> &ob2);

        template<class it1, class it2>
        friend bool operator< (const reverse_iterator<it1> &ob1, const reverse_iterator<it2> &ob2);

        template<class it1, class it2>
        friend bool operator>= (const reverse_iterator<it1> &ob1, const reverse_iterator<it2> &ob2);

        template<class it1, class it2>
        friend bool operator<= (const reverse_iterator<it1> &ob1, const reverse_iterator<it2> &ob2);

        template<class it1, class it2>
        friend typename reverse_iterator<it1>::difference_type operator-(const reverse_iterator<it1> &a, const reverse_iterator<it2> &b);


        template<class it>
        friend reverse_iterator<it> operator+(typename reverse_iterator<it>::difference_type a, const reverse_iterator<it> &b);

   };

    template<class it1, class it2>
    bool operator== (const reverse_iterator<it1> &ob1, const reverse_iterator<it2> &ob2)
    {
        return (ob1.base() == ob2.base());
    }
    template<class it1, class it2>
    bool operator!= (const reverse_iterator<it1> &ob1, const reverse_iterator<it2> &ob2)
    {
        return (ob1.base() != ob2.base());
    }
    template<class it1, class it2>
    bool operator> (const reverse_iterator<it1> &ob1, const reverse_iterator<it2> &ob2)
    {
        return (ob1.base() < ob2.base());
    }
    template<class it1, class it2>
    bool operator< (const reverse_iterator<it1> &ob1, const reverse_iterator<it2> &ob2)
    {
        return (ob1.base() > ob2.base());
    }
    template<class it1, class it2>
    bool operator>= (const reverse_iterator<it1> &ob1, const reverse_iterator<it2> &ob2)
    {
        return (ob1.base() <= ob2.base());
    }
    template<class it1, class it2>
    bool operator<= (const reverse_iterator<it1> &ob1, const reverse_iterator<it2> &ob2)
    {
        return (ob1.base() >= ob2.base());
    }
    template<class it1, class it2>
    typename reverse_iterator<it1>::difference_type operator-(const reverse_iterator<it1> &a, const reverse_iterator<it2> &b)
    {
        return (b.base() - a.base());
    }
    template<class it>
    reverse_iterator<it> operator+(typename reverse_iterator<it>::difference_type a, const reverse_iterator<it> &b)
    {
        return (reverse_iterator<it>(b.base() - a));
    }
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