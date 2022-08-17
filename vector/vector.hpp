#pragma once

#include <vector>
#include <iostream>

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
			typedef		typename	std::vector<T>::iterator			iterator;
			typedef		typename	std::vector<T>::const_iterator		const_iterator;
			typedef		typename	std::vector<T>::reverse_iterator	reverse_iterator;
			typedef		typename	std::vector<T>::const_reverse_iterator	const_reverse_iterator;
			typedef 	typename	allocator_type::difference_type 		difference_type;
			typedef 				size_t									size_type;

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
         	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {
				this->_size = last - first;
				this->_capacity = this->_size;
			};

			vector (const vector &x) {
				*this = x;
			};

			vector& operator= (const vector& x) {
				this->_alloc = x._alloc;
				this->_container = x._container;
				this->_size = x.size;
				this->_capacity = x._capacity;
				return (*this);
			};

			~vector(){
				delete this->_container;
			};

			// iterator begin(){
			// 	return _arr[0];
			// }

			// const_iterator begin() const {
			// 	return _arr;
			// }

			// iterator end(){
			// 	return _arr[size];
			// };
			// const_iterator end() const{
			// 	return _arr[size];
			// };
    };
};
