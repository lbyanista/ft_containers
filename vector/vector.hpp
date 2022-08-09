#pragma once

// #include <memory>

namespace ft {
    template < class T, class Alloc = allocator<T> >
    class vector{
		public:
        	typedef		T	value_type; // 1st template parameter T
			typedef		typename	Alloc								allocator_type;
			typedef		typename	allocator_type::reference			reference;
			typedef		typename	allocator_type::const_reference		const_reference;
			typedef		typename	allocator_type::pointer				pointer;
			typedef 	typename	allocator_type::const_pointer 		const_pointer;

		private:


		public:
			explicit vector (const allocator_type& alloc = allocator_type()){};
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {};
			template <class InputIterator>
         	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {};

			vector (const vector& x) {};

			vector& operator= (const vector& x) {};

			~vector(){};
    };
};