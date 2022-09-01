#pragma once

#include <vector>
#include <iostream>
#include "iterator.hpp"
#include "reverse_iterator.hpp"

#include "enable_if.hpp"
#include "is_integral.hpp"

#include <algorithm>

#include <memory>

namespace ft {
    template < class T, class Alloc = std::allocator<T> >
    class vector{
		public:
        	typedef		T												value_type; // 1st template parameter T
			typedef		Alloc											allocator_type;
			typedef		typename	allocator_type::reference			reference;
			typedef		typename	allocator_type::const_reference		const_reference;
			typedef		typename	allocator_type::pointer				pointer;
			typedef 	typename	allocator_type::const_pointer 		const_pointer;
			typedef		typename	ft::vec_iterator<value_type>		iterator;
			typedef		typename	ft::vec_iterator<const value_type>	const_iterator;
			typedef		typename	ft::reverse_iterator<iterator>		reverse_iterator;
			typedef		typename	ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef 	typename	allocator_type::difference_type 		difference_type;
			typedef 				std::size_t									size_type;

		private:
			allocator_type		_alloc;
			pointer				_container;
			size_type			_size;
			size_type			_capacity;

		public:
			explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _container(NULL), _size(0), _capacity(0) {

			};

			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _container(NULL), _size(n), _capacity(n) {
				this->_container = this->_alloc.allocate(this->_size);
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
				this->_alloc = alloc;
				this->_size = last - first;
				this->_capacity = this->_size;
				this->_container = this->_alloc.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(this->_container + i, *(first + i));
			};

			vector (const vector &x) {
				*this = x;
			};

			vector& operator= (const vector& x) {
				if(this->_capacity){
					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.destroy(this->_container + i);
					this->_alloc.deallocate(this->_container, this->_capacity);
				}
				this->_alloc = x._alloc;
				this->_size = x._size;
				this->_capacity = x._capacity;
				this->_container = this->_alloc.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(this->_container + i, *(x._container + i));
				return (*this);
			};

			~vector(){
				if(this->_size){
					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.destroy(this->_container + i);
					this->_alloc.deallocate(this->_container, this->_capacity);
				}
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
				if (n > this->_size) {
					if (n > this->_capacity) {
						this->reserve(n);
					}
					for (size_type i = this->_size; i < n; i++) {
						this->_alloc.construct(this->_container + i, val);
					}
				}
				else if (n < this->_size) {
					for (size_type i = n; i < this->_size; i++) {
						this->_alloc.destroy(this->_container + i);
					}
				}
				this->_size = n;
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
				if(n > max_size())
					throw std::length_error("vector");
				if(n > this->_capacity){
					pointer tmp;
					tmp = this->_alloc.allocate(n);

					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.construct(tmp + i, *(this->_container + i));
					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.destroy(this->_container + i);
					this->_alloc.deallocate(this->_container, this->_capacity);
					this->_container = tmp;
					this->_capacity = n;
					}
			}

			reference operator[] (size_type n){
				return this->_container[n];
			}

			const_reference operator[] (size_type n) const{
				return this->_container[n];
			}

			reference at (size_type n){
				if(n >= this->_size)
					throw std::out_of_range("vector");
				return this->_container[n];
			}

			const_reference at (size_type n) const{
				if(n >= this->_size)
					throw std::out_of_range("vector");
				return this->_container[n];
			}

			reference front(){
				return this->_container[0];
			}

			const_reference front() const{
				return this->_container[0];
			}

			reference back(){
				return this->_container[this->_size - 1];
			}

			const_reference back() const{
				return this->_container[this->_size - 1];
			}

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0){
				for (size_type i = 0; i < this->_size; i++)
						this->_alloc.destroy(this->_container + i);
				if(this->_size)
					this->_alloc.deallocate(this->_container, this->_capacity);
				this->_size = 0;
				this->_capacity = 0;
				this->_container = NULL;
				this->insert(this->begin(), first, last);
			}

			void assign (size_type n, const value_type& val){
				for (size_type i = 0; i < this->_size; i++)
						this->_alloc.destroy(this->_container + i);
				if(this->_size)
					this->_alloc.deallocate(this->_container, this->_capacity);
				this->_size = 0;
				this->_capacity = 0;
				this->_container = NULL;
				this->insert(this->begin(), n, val);
			}

			void push_back (const value_type& val){
				if(this->_size == this->_capacity)
					this->reserve(this->_capacity * 2);
				if(this->_capacity == 0)
					this->reserve(1);
				this->_alloc.construct(this->_container + this->_size, val);
				this->_size++;
			}

			void pop_back(){
				this->_alloc.destroy(this->_container + this->_size - 1);
				this->_size--;
			}

			//insert
			iterator insert(iterator position, const value_type& val){
				if(this->_size == this->_capacity)
					this->reserve(this->_capacity * 2);
				pointer tmp;
				tmp = this->_alloc.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(tmp + i, *(this->_container + i));
				for (size_type i = 0; i < this->_size; i++)
						this->_alloc.destroy(this->_container + i);
				this->_alloc.deallocate(this->_container, this->_capacity);
				this->_container = tmp;
				size_type i = 0;
				for(iterator it = this->begin(); it != position; it++){
					i++;
				}
				for (size_type j = this->_size; j > i; j--)
					this->_container[j] = this->_container[j - 1];
				this->_alloc.construct(this->_container + i, val);
				this->_size++;
				return iterator(this->_container + i);
			}

			void insert(iterator position, size_type n, const value_type& val){
				if(this->_size + n > this->_capacity){
					if (this->_capacity * 2 >= this->_size + n)
						this->reserve(this->_capacity * 2);
					else
						this->reserve(this->_size + n);
				}
				pointer tmp;
				tmp = this->_alloc.allocate(this->_capacity);
				size_type t = 0;
				for(iterator it = this->begin(); it != position; it++){
					t++;
				}
				for (size_type i = 0; i < t; i++)
					this->_alloc.construct(tmp + i, *(this->_container + i));
				for (size_type j = this->_size; j > t; j--)
					this->_alloc.construct(tmp + j + (n - 1), this->_container[j - 1]);
				for (size_type j = 0; j < n; j++)
					this->_alloc.construct(tmp + t + j, val);
				for (size_type i = 0; i < this->_size; i++)
						this->_alloc.destroy(this->_container + i);
				this->_alloc.deallocate(this->_container, this->_capacity);
				this->_container = tmp;
				this->_size += n;
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0){
				size_type n = 0;
				for (InputIterator it = first; it != last; it++)
					n++;
				if(this->_size + n > this->_capacity)
					this->reserve(this->_capacity * 2);
				pointer tmp;
				tmp = this->_alloc.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(tmp + i, *(this->_container + i));
				for (size_type i = 0; i < this->_size; i++)
						this->_alloc.destroy(this->_container + i);
				this->_alloc.deallocate(this->_container, this->_capacity);
				this->_container = tmp;
				size_type i = 0;
				for(iterator it = this->begin(); it != position; it++){
					i++;
				}
				for (size_type j = this->_size; j > i; j--)
					this->_container[j + n - 1] = this->_container[j - 1];
				for (size_type j = 0; j < n; j++)
					this->_alloc.construct(this->_container + i + j, *(first + j));
				this->_size += n;
			}
			//end insert


			iterator erase (iterator position){
				size_type i = 0;
				for(iterator it = this->begin(); it != position; it++){
					i++;
				}
				for (size_type j = i; j < this->_size - 1; j++)
					this->_container[j] = this->_container[j + 1];
				this->_alloc.destroy(this->_container + this->_size - 1);
				this->_size--;
				return iterator(this->_container + i);
			}

			iterator erase (iterator first, iterator last){
				size_type i = 0;
				for(iterator it = this->begin(); it != first; it++){
					i++;
				}
				size_type n = 0;
				for(iterator it = first; it != last; it++){
					n++;
				}
				for (size_type j = i; j < this->_size - n; j++)
					this->_container[j] = this->_container[j + n];
				for (size_type j = 0; j < n; j++)
					this->_alloc.destroy(this->_container + this->_size - j - 1);
				this->_size -= n;
				return iterator(this->_container + i);
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
				allocator_type tmp_alloc = this->_alloc;
				this->_alloc = x._alloc;
				x._alloc = tmp_alloc;
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
  			return std::equal(lhs.begin(), lhs.end(), rhs.begin());
  		}

		template <class T, class Alloc>
  		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
  			return !(lhs == rhs);
  		}

		template <class T, class Alloc>
  		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
			return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  		}

		template <class T, class Alloc>
  		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
  			return !(lhs > rhs);
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
  		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y){
  			x.swap(y);
  		}
};
