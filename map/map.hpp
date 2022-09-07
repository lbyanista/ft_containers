#pragma once

// #include "../utility/pair.hpp"
#include "AVLTree.hpp"
#include <iostream>

namespace ft {
    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
    class map {
    public:
        typedef Key									key_type;
		typedef T									mapped_type;
		typedef Compare								key_comp;
		typedef pair<const key_type, mapped_type>	value_type;


        //binary function is requierd in c++98 to inherit value_type, value_type, bool
        typedef class val_comp : public std::binary_function<value_type, value_type, bool>{
            friend class map;

            protected:
            Compare cmp;

            val_comp(Compare c) : cmp(c){}

            public:
            typedef bool result_type;
			typedef value_type first_arg_type;
			typedef value_type second_arg_type;

            bool operator() (const value_type &x, const value_type &y) const {
                return cmp(x.first, y.first);
            }
        } value_comp;

        typedef		Alloc												allocator_type;
		typedef		typename	allocator_type::reference				reference;
		typedef		typename	allocator_type::const_reference			const_reference;
		typedef		typename	allocator_type::pointer					pointer;
		typedef		typename	allocator_type::const_pointer			const_pointer;
		typedef		std::ptrdiff_t										difference_type;
		typedef		size_t												size_type;

        private:
        typedef		AVLTree<value_type, Compare, Alloc>                 Tree;
		typedef		typename AVLTree<value_type, Compare, Alloc>::Node  Node;
		typename    Alloc::template rebind<Tree>::other                 _alloc_avl;
		Tree				_tree;
		size_type			_size;
		allocator_type		_map_alloc;
		key_compare			_key_map_comp;
		int a;

        public:
        //maybe i need to implement new map_iterator to replace vec_iterator with
        typedef		vec_iterator<value_type, Node, Tree>				iterator;
		typedef		vec_iterator<const value_type, const Node, Tree>	const_iterator;
		typedef		ft::reverse_iterator<iterator>						reverse_iterator;
		typedef		ft::reverse_iterator<const_iterator>				const_reverse_iterator;


        explicit map (const key_compare& comp = key_comp(), const allocator_type& alloc = allocator_type()){
			this->_tree._node = NULL;
			this->_map_alloc = alloc;
			this->_key_map_comp = comp;
			this->_tree._ob_comp = comp;
			this->_size = 0;
			this->a = 0;
		}

        template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_comp(), const allocator_type& alloc = allocator_type())
		{
			this->_tree._node = NULL;
			this->_map_alloc = alloc;
			this->_key_map_comp = comp;
			this->_tree._ob_comp = comp;
			this->_size = 0;
			this->insert(first, last);
		}


        


        // class value_compare {
        //     friend class map;
        // protected:
        //     Compare comp;
        //     value_compare(Compare c) : comp(c) {}
        // public:
        //     typedef bool result_type;
        //     typedef value_type first_argument_type;
        //     typedef value_type second_argument_type;
        //     bool operator()(const value_type& x, const value_type& y) const {
        //         return comp(x.first, y.first);
        //     }

        //     explicit map (const key_compare& comp = key_compare(),
        //       const allocator_type& alloc = allocator_type()){
        //         std::cout << "map constructor" << std::endl;}
        //     template <class InputIterator>
        //     map (InputIterator first, InputIterator last,
        //       const key_compare& comp = key_compare(),
        //       const allocator_type& alloc = allocator_type()){
        //         std::cout << "map constructor" << std::endl;}

        //     map (const map& x){
        //         *this = x;}
        //     }
        //     ~map(){
        //         std::cout << "map destructor" << std::endl;}

        //     map& operator= (const map& x){
        //         return *this;
        //         }
            
        //     };
    };
};