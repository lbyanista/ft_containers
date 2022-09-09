#pragma once

// #include <vector>
#include <iostream>
#include "../iterator/iterator.hpp"
#include "../iterator/reverse_iterator.hpp"

#include "../utility/enable_if.hpp"
#include "../utility/is_integral.hpp"
// #include "../utility/distance.hpp"
#include "../utility/equal.hpp"
#include "../utility/lexicographical_compare.hpp"

#include <algorithm>

#include <memory>

namespace ft {
    template < class T, class Alloc = std::allocator<T> >
    class vector{
		public:
        	typedef T                                         				value_type;
        	typedef Alloc                                  			        allocator_type;
        	typedef typename allocator_type::reference	        			reference;
        	typedef typename allocator_type::const_reference    			const_reference;
        	typedef typename allocator_type::pointer           				pointer;
        	typedef typename allocator_type::const_pointer      			const_pointer;
        	typedef std::size_t												size_type;
        	typedef ft::iterator<T>											iterator;
        	typedef ft::iterator<const T>							        const_iterator;
        	typedef ft::reverse_iterator<iterator>						    reverse_iterator;
        	typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
        	typedef std::ptrdiff_t 											difference_type;

		private:
			allocator_type		_alloc;
			pointer				_container;
			size_type			_size;
			size_type			_capacity;

		public:
			explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _container(NULL), _size(0), _capacity(0) {

			};

			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _container(NULL), _size(n), _capacity(n) {
				this->_container = this->_alloc.allocate(n);
				for (size_type i = 0; i < this->_size; i++)
				{
					// this->_container[i] = val;

					// *(pointer + i)
					// pointer[i]

					this->_alloc.construct(this->_container + i, val);
				}
			};
			template <class InputIterator>
         	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), 
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) {
				size_type d = (size_type)std::distance(first, last);
				this->_alloc = alloc;
				this->_size = d;
				this->_capacity = d;
				this->_container = NULL;
				this->_container = this->_alloc.allocate(d);
				for (size_type i = 0; i < d; i++)
					this->_alloc.construct(this->_container + i, *(first + i));
			};

			vector (const vector &x) {
				this->_container = nullptr;
				this->_size = 0;
				this->_capacity = 0;
				this->_alloc = allocator_type();
				*this = x;
			};

			~vector(){
				if(this->_container){
					clear();
					this->_alloc.deallocate(this->_container, this->_capacity);
				}
			};

			vector& operator= (const vector& x) {
				if (*this != x)
            	{
                	// this->this->_alloc = x.this->_alloc;
                	for (size_type i = 0; i < this->_size; i++)
                	    this->_alloc.destroy(this->_container + i);
                	if (this->_capacity > 0)
                	    this->_alloc.deallocate(this->_container, this->_capacity);
                	if (this->capacity() < x.capacity())
                	        this->_capacity = x._capacity;
                	this->_size = x._size;
                	this->_container = this->_alloc.allocate(this->_capacity);
                	for(size_type i = 0; i < x._size; i++)
                	    this->_alloc.construct(this->_container + i, x._container[i]);
            	}
            	return *this;
			};


			iterator begin(){
				return iterator(this->_container);
			}
			const_iterator begin() const{
				return const_iterator(this->_container);
			}

			iterator end(){
				return iterator(this->_container + this->_size);
			}
			const_iterator end() const{
				return const_iterator(this->_container + this->_size);
			}

			reverse_iterator rbegin(){
				return reverse_iterator(end());
			}
			const_reverse_iterator rbegin() const{
				return const_reverse_iterator(end());
			}

			reverse_iterator rend(){
				return reverse_iterator(begin());
			}
			const_reverse_iterator rend() const{
				return const_reverse_iterator(begin());
			}

			size_type size() const{
				return this->_size;
			}

			size_type max_size() const{
				return this->_alloc.max_size();
			}

			// void resize (size_type n, value_type val = value_type()){


			// }

			void resize(size_type n, value_type val = value_type()) {
				if (n < this->_size)
            	{
					for (size_type i = n; i < this->_size; i++)
            	        this->_alloc.destroy(this->_container + i);
                this->_size = n;
            	}
            	else if (n > this->_capacity)
            	{
            	    if (n > this->_capacity && n < this->_capacity * 2)
            	        reserve(n * 2);
            	    else if (n > this->_capacity)
            	        reserve(n);
            	    for (size_type i = this->_size; i < n; i++)
            	        this->_alloc.construct(this->_container + i, val);
            	    this->_size = n;
            	}
            	else if (n > this->_size)
            	{
            	    for (size_type i = this->_size; i < n; i++)
            	        this->_alloc.construct(this->_container + i, val);
            	    this->_size = n;
            	}
			}

			size_type capacity() const{
				return this->_capacity;
			}

			bool empty() const{
				if(this->_size){
					return false;
				}
				return true;
			}

			void reserve (size_type n){
				if (n > this->_capacity) {
					if (n > max_size())
                    	throw std::length_error("more than maximum supported size");
                	pointer tmp;
                	tmp = this->_alloc.allocate(n);
                	for (size_type i = 0; i < this->_size; i++)
                	    this->_alloc.construct(tmp + i, this->_container[i]);
                	for (size_type i = 0; i < this->_size; i++)
                	    this->_alloc.destroy(this->_container + i);
                	this->_alloc.deallocate(this->_container, this->_capacity);
                	this->_container = tmp;
                	this->_capacity = n;
				}
			}

			reference operator[] (size_type n){
				if(n >= this->_size)
					throw std::out_of_range("outside of pointer(_container)");
				return this->_container[n];
			}

			const_reference operator[] (size_type n) const{
				if(n >= this->_size)
					throw std::out_of_range("outside of pointer(_container)");
				return this->_container[n];
			}

			reference at (size_type n){
				if(n >= this->_size)
					throw std::out_of_range("outside of pointer(_container)");
				return this->_container[n];
			}

			const_reference at (size_type n) const{
				if(n >= this->_size)
					throw std::out_of_range("outside of pointer(_container)");
				return this->_container[n];
			}

			reference front(){
				return *this->_container;
			}

			const_reference front() const{
				return *this->_container;
			}

			reference back(){
				return this->_container[this->_size - 1];
			}

			const_reference back() const{
				return this->_container[this->_size - 1];
			}

			//any of ft::distance can replace with std::distance
			//modifier
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last){
				size_type n = (size_type)std::distance(first, last);
            	if (n > this->_capacity)
                	reserve(n);
            	for (size_type i = 0; i < this->_size; i++)
                	this->_alloc.destroy(this->_container + i);
            	for (size_type i = 0; i < n; i++)
                	this->_alloc.construct(this->_container + i, *(first + 1));
            	this->_size = n;
			}

			void assign (size_type n, const value_type& val){
				if (n > this->_capacity)
                	reserve(n);
            	for (size_type i = 0; i < this->_size; i++)
                	this->_alloc.destroy(this->_container + i);
            	for (size_type i = 0; i < n; i++)
                	this->_alloc.construct(this->_container + i, val);
            	this->_size = n;
			}

			void push_back (const value_type& val){
				if (this->_capacity == 0)
                	reserve(1);
            	else if (this->_size == this->_capacity)
                	reserve(this->_size * 2);
            	this->_alloc.construct(this->_container + this->_size, val);
            	this->_size++;
			}

			void pop_back(){
				if (this->_size > 0)
            	{
                	this->_size--;
                	this->_alloc.destroy(this->_container + this->_size);
            	}
			}

			//insert
			iterator insert(iterator position, const value_type& val){
				size_type d = (size_type)std::distance(begin(), position);
            	if (this->_capacity == 0)
                	reserve(1);
            	else if (this->_size == this->_capacity)
                	reserve(this->_size * 2);
            	for (size_type i = this->_size; i > d; i--)
                	this->_alloc.construct(this->_container + i, this->_container[i - 1]);
            	this->_alloc.construct(this->_container + d, val);
            	this->_size++;
            	return (iterator(this->_container + d));
			}

			void insert(iterator position, size_type n, const value_type& val){
				difference_type d = std::distance(begin(), position);
            	if (this->_capacity == 0 || (this->_size + n) > (this->_capacity * 2))
                	reserve(this->_size + n);
            	else if ((this->_size + n) > this->_capacity)
                	reserve(this->_size * 2);
				for (difference_type i = this->_size - 1;i >= d;--i)
					this->_alloc.construct(this->_container + (i + n), this->_container[i]);
            	for (size_type i = 0; i < n; i++)
                	this->_alloc.construct(this->_container + d++, val);
            	this->_size += n;
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last){
				difference_type d = std::distance(begin(), position);
            	size_type n = std::distance(first, last);

            	if (this->_capacity == 0 || (this->_size + n) > (this->_capacity * 2))
                	reserve(this->_size + n);
            	else if ((this->_size + n) > this->_capacity)
                	reserve(this->_size * 2);

            	for (difference_type i = this->_size - 1; i >= d; i--)
                	this->_alloc.construct(this->_container + i + n, this->_container[i]);
            	for (size_type i = 0; i < n; i++)
                	this->_alloc.construct(this->_container + d++, *(first++));
            	this->_size += n;
			}
			//end insert


			iterator erase (iterator position){
				size_type d = (size_type)std::distance(begin(), position);
            	this->_alloc.destroy(this->_container + d);
            	for (size_type i = d; i < this->_size; i++)
                	this->_alloc.construct(this->_container + i, this->_container[i + 1]);
            	this->_size--;
            	return (iterator(this->_container + d));
			}

			iterator erase (iterator first, iterator last){
				size_type d = std::distance(begin(), first);
            	size_type n = std::distance(first, last);
            	for (size_type i = d; i < n + d; i++)
                	this->_alloc.destroy(this->_container + i);
            	this->_size -= n;
            	for (size_type i = d; i < this->_size; i++)
                	this->_alloc.construct(this->_container + i, this->_container[i + n]);
            	return (iterator(this->_container + d));
			}

			void swap(vector& x){
				pointer tmp = this->_container;
				this->_container = x._container;
				x._container = tmp;

				size_type tmp_size = this->_size;
				this->_size = x._size;
				x._size = tmp_size;

				size_type tmp_capacity = this->_capacity;
				this->_capacity = x._capacity;
				x._capacity = tmp_capacity;
				// allocator_type tmp_alloc = this->_alloc;
				// this->_alloc = x._alloc;
				// x._alloc = tmp_alloc;
			}

			void clear(){
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_container + i);
				this->_size = 0;
			}

			allocator_type get_allocator() const{
				return this->_alloc;
			}
		};// end class vector


		//relational operators

		template <class T, class Alloc>
  		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
  			if(lhs.size() != rhs.size())
  				return false;
  			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
  		}

		template <class T, class Alloc>
  		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
  			return !(lhs == rhs);
  		}

		template <class T, class Alloc>
  		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
  			return rhs < lhs;
  		}

		template <class T, class Alloc>
  		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
  			return !(lhs < rhs);
  		}
		template <class T, class Alloc>
  		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  		}

		template <class T, class Alloc>
  		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
  			return !(lhs > rhs);
  		}

		template <class T, class Alloc>
  		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y){
  			x.swap(y);
  		}
};
