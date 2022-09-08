#pragma once

#include <iostream>
#include <memory>
#include "iterator_traits.hpp"


namespace ft{

    template<class T>
    class iterator 
    {
        public:
		typedef	std::ptrdiff_t						difference_type;
		typedef	T									value_type;
		typedef	T*									pointer;
		typedef	T&									reference;
		typedef	std::random_access_iterator_tag		iterator_category;

        private:
        pointer _ptr;

        public:
        // constructors
        iterator() : _ptr(NULL) { }
        explicit iterator(pointer it) : _ptr(it) { }
        template<typename it2>
        iterator(const iterator<it2> &i) : _ptr(i.base()){ }

        // getter
        pointer base() const
        {
            return (this->_ptr);
        }

        // operators
        iterator& operator=(const iterator& i)
        {
            this->_ptr = i._ptr;
            return (*this);
        }

        reference operator*()
        {
            return *this->_ptr;
        }

        pointer operator->()
        {
            return this->_ptr;
        }

        iterator& operator++()
        {
            ++this->_ptr;
            return (*this);
        }

        iterator operator++(int)
        {
            iterator tmp;

            tmp._ptr = this->_ptr++;
            return (tmp);
        }

        iterator& operator--()
        {
            --this->_ptr;
            return (*this);
        }

        iterator operator--(int)
        {
            iterator tmp;

            tmp._ptr = this->_ptr--;
            return (tmp);
        }

        iterator operator+ (difference_type index)
        {
            iterator tmp;

            tmp._ptr = this->_ptr + index;
            return (tmp);
        }

        iterator operator- (difference_type index)  const
        {
            return (iterator(this->_ptr - index));
        }

        iterator &operator+= (difference_type index)
        {
            this->_ptr = this->_ptr + index;
            return (*this);
        }

        iterator &operator-= (difference_type index)
        {
            this->_ptr = this->_ptr - index;
            return (*this);
        }

        reference operator[] (difference_type index)
        {
            return (this->_ptr[index]);
        }

        template<class it1, class it2>
        friend bool operator== (const iterator<it1> &ob1, const iterator<it2> &ob2);

        template<class it1, class it2>
        friend bool operator!= (const iterator<it1> &ob1, const iterator<it2> &ob2);

        template<class it1, class it2>
        friend bool operator> (const iterator<it1> &ob1, const iterator<it2> &ob2);

        template<class it1, class it2>
        friend bool operator< (const iterator<it1> &ob1, const iterator<it2> &ob2);

        template<class it1, class it2>
        friend bool operator>= (const iterator<it1> &ob1, const iterator<it2> &ob2);

        template<class it1, class it2>
        friend bool operator<= (const iterator<it1> &ob1, const iterator<it2> &ob2);

        template<class it1, class it2>
        friend typename iterator<it1>::difference_type operator-(const iterator<it1> &a, const iterator<it2> &b);


        template<class it>
        friend iterator<it> operator+(typename iterator<it>::difference_type a, const iterator<it> &b);

   };

    template<class it1, class it2>
    bool operator== (const iterator<it1> &ob1, const iterator<it2> &ob2)
    {
        return (ob1.base() == ob2.base());
    }
    template<class it1, class it2>
    bool operator!= (const iterator<it1> &ob1, const iterator<it2> &ob2)
    {
        return (ob1.base() != ob2.base());
    }
    template<class it1, class it2>
    bool operator> (const iterator<it1> &ob1, const iterator<it2> &ob2)
    {
        return (ob1.base() > ob2.base());
    }
    template<class it1, class it2>
    bool operator< (const iterator<it1> &ob1, const iterator<it2> &ob2)
    {
        return (ob1.base() < ob2.base());
    }
    template<class it1, class it2>
    bool operator>= (const iterator<it1> &ob1, const iterator<it2> &ob2)
    {
        return (ob1.base() >= ob2.base());
    }
    template<class it1, class it2>
    bool operator<= (const iterator<it1> &ob1, const iterator<it2> &ob2)
    {
        return (ob1.base() <= ob2.base());
    }
    template<class it1, class it2>
    typename iterator<it1>::difference_type operator-(const iterator<it1> &a, const iterator<it2> &b)
    {
        return (a.base() - b.base());
    }
    template<class it>
    iterator<it> operator+(typename iterator<it>::difference_type a, const iterator<it> &b)
    {
        return (iterator<it>(a + b.base()));
    }

}


// namespace ft
// {
//     template <typename T>
//     class iterator
//     {
//         public:
//         typedef typename iterator_traits<T*>::value_type value_type;
//         typedef typename iterator_traits<T*>::difference_type difference_type;
//         typedef typename iterator_traits<T*>::pointer pointer;
//         typedef typename iterator_traits<T*>::reference reference;
//         typedef typename iterator_traits<T*>::iterator_category iterator_category;

//         private:
//             pointer _ptr;

//         public:
//         vec_iterator(const reference current){
//             _ptr = current;
//         }   

//         pointer base(void) const
//         {
//             return _ptr;
//         }

//         vec_iterator(void) {
//             // _ptr = int();
//         }

//         vec_iterator(pointer ptr) {
//             _ptr = ptr;
//         }

//         template<typename U>
//         vec_iterator(const vec_iterator<U> &other) {
//             // *this = other;
//             this->_ptr = other.base();
//         }

//         template<typename U, typename V>
//         vec_iterator<U>& operator=(const vec_iterator<V>& other) {
//             _ptr = other.base();
//             return *this;
//         }

//         vec_iterator<T>& operator++(void) {
//             ++_ptr;
//             return *this;
//         }

//         vec_iterator<T> operator++(int) {
//             vec_iterator<T> tmp = *this;
//             ++_ptr;
//             return tmp;
//         }

//         vec_iterator<T>& operator--(void) {
//             --_ptr;
//             return *this;
//         }

//         vec_iterator<T> operator--(int) {
//             vec_iterator<T> tmp = *this;
//             --_ptr;
//             return tmp;
//         }

//         reference operator*(void) const {
//             return *_ptr;
//         }

//         pointer operator->(void) const {
//             return _ptr;
//         }

//         reference operator[](difference_type n) const {
//             return _ptr[n];
//         }

//         vec_iterator<T> operator+(difference_type n) const {
//             return vec_iterator<T>(_ptr + n);
//         }

//         vec_iterator<T> operator-(difference_type n) const {
//             return vec_iterator<T>(_ptr - n);
//         }

//         vec_iterator<T>& operator+=(difference_type n) {
//             _ptr += n;
//             return *this;
//         }

//         vec_iterator<T>& operator-=(difference_type n) {
//             _ptr -= n;
//             return *this;
//         }
//     };


//     // struct vec_iterator
//     // {
//     //     typedef T* iterator_type;
//     //     typedef typename iterator_traits<T*>::value_type value_type;
//     //     typedef typename iterator_traits<T*>::iterator_category iterator_category;
//     //     typedef typename iterator_traits<T*>::difference_type difference_type;
//     //     typedef typename iterator_traits<T*>::pointer pointer;
//     //     typedef typename iterator_traits<T*>::reference reference;

//     //     private:
//     //         iterator_type current;

//     //     public:
//     //         vec_iterator() {}
//     //         explicit vec_iterator (iterator_type it){ current = it; }
//     //         template <class Iter>
//     //         vec_iterator (const vec_iterator<Iter>& v_it){ current = v_it.base(); }

//     //         iterator_type base() const{
//     //             return current;
//     //         }

//     //         reference operator*() const{
//     //             return *(current);
//     //         }

//     //         vec_iterator operator+ (difference_type n) const{
//     //             return vec_iterator(current - n);
//     //         }

//     //         vec_iterator& operator++(){
//     //             ++current;
//     //             return *this;
//     //         }
//     //         vec_iterator operator++ (int){
//     //             vec_iterator tmp = *this;
//     //             ++current;
//     //             return tmp;
//     //         }

//     //         vec_iterator& operator+= (difference_type n){
//     //             current += n;
//     //             return *this;
//     //         }

//     //         vec_iterator operator- (difference_type n) const{
//     //             return vec_iterator(current - n);
//     //         }

//     //         vec_iterator& operator--(){
//     //             --current;
//     //             return *this;
//     //         }

//     //         vec_iterator operator-- (int){
//     //             vec_iterator tmp = *this;
//     //             --current;
//     //             return tmp;
//     //         }

//     //         vec_iterator& operator-= (difference_type n){
//     //             current -= n;
//     //             return *this;
//     //         }

//     //         pointer operator->() const{
//     //             return &(operator*());
//     //         }

//     //         reference operator[] (difference_type n) const{
//     //             return *(*this + n);
//     //         }
//     // };//end of vec_iterator


//     template <typename TL, typename TR>
//     bool operator==(const vec_iterator<TL>& lhs, const vec_iterator<TR>& rhs) {
//         return lhs.base() == rhs.base();
//     }

//     template <typename TL, typename TR>
//     bool operator!=(const vec_iterator<TL>& lhs, const vec_iterator<TR>& rhs) {
//         return !(lhs == rhs);
//     }

//     template <typename TL, typename TR>
//     bool operator<(const vec_iterator<TL>& lhs, const vec_iterator<TR>& rhs) {
//         return lhs.base() < rhs.base();
//     }

//     template <typename TL, typename TR>
//     bool operator>(const vec_iterator<TL>& lhs, const vec_iterator<TR>& rhs) {
//         return lhs.base() > rhs.base();
//     }

//     template <typename TL, typename TR>
//     bool operator<=(const vec_iterator<TL>& lhs, const vec_iterator<TR>& rhs) {
//         return lhs.base() <= rhs.base();
//     }

//     template <typename TL, typename TR>
//     bool operator>=(const vec_iterator<TL>& lhs, const vec_iterator<TR>& rhs) {
//         return lhs.base() >= rhs.base();
//     }

//     template <typename T>
//     vec_iterator<T> operator+(const typename vec_iterator<T>::difference_type &n, const vec_iterator<T> &it) {
//         return n + it.base();
//     }

//     template <typename TL, typename TR>
//     typename vec_iterator<TL>::difference_type operator-(const vec_iterator<TL>& lhs, const vec_iterator<TR>& rhs) {
//         return lhs.base() - rhs.base();
//     }

//     // template <class Iterator>
//     // bool operator== (const vec_iterator<Iterator>& lhs, const vec_iterator<Iterator>& rhs){
//     //     return lhs.base() == rhs.base();
//     // }

//     // template <class Iterator>
//     // bool operator!= (const vec_iterator<Iterator>& lhs, const vec_iterator<Iterator>& rhs){
//     //     return !(lhs == rhs);
//     // }

//     // template <class Iterator>
//     // bool operator<  (const vec_iterator<Iterator>& lhs, const vec_iterator<Iterator>& rhs){
//     //     return rhs.base() > lhs.base();
//     // }

//     // template <class Iterator>
//     // bool operator<= (const vec_iterator<Iterator>& lhs, const vec_iterator<Iterator>& rhs){
//     //     return !(rhs < lhs);
//     // }

//     // template <class Iterator>
//     // bool operator>  (const vec_iterator<Iterator>& lhs, const vec_iterator<Iterator>& rhs){
//     //     return rhs < lhs;
//     // }

//     // template <class Iterator>
//     // bool operator>= (const vec_iterator<Iterator>& lhs, const vec_iterator<Iterator>& rhs){
//     //     return !(lhs < rhs);
//     // }

//     // template <class Iterator>
//     // vec_iterator<Iterator> operator+ (typename vec_iterator<Iterator>::difference_type n,
//     //     const vec_iterator<Iterator>& v_it){
//     //     return vec_iterator<Iterator>(v_it.base() + n);
//     // }

//     // template <class Iterator>
//     // typename vec_iterator<Iterator>::difference_type operator- (const vec_iterator<Iterator>& lhs,
//     //         const vec_iterator<Iterator>& rhs){
//     //     return lhs.base() - rhs.base();
//     // }
// };
