#pragma once

#include "base_iterator.hpp"
#include "iterator_traits.hpp"
#include "../map/AVLTree.hpp"
#include "../utility/pair.hpp"

namespace ft {
	template <	class value_type_pair, class Node, class Tree>
	
	class map_iterator : base_iterator<std::bidirectional_iterator_tag, value_type_pair> {
		
		public:
		typedef typename	base_iterator<std::bidirectional_iterator_tag, value_type_pair >::difference_type	difference_type;
		typedef typename	base_iterator<std::bidirectional_iterator_tag, value_type_pair >::value_type		value_type;
		typedef typename	base_iterator<std::bidirectional_iterator_tag, value_type_pair >::pointer			pointer;
		typedef typename	base_iterator<std::bidirectional_iterator_tag, value_type_pair >::reference			reference;
		typedef typename	base_iterator<std::bidirectional_iterator_tag, value_type_pair >::iterator_category	iterator_category;
		typedef 			map_iterator<const value_type, const Node, Tree>  const_iterator;

			Tree *_tree;
			Node *_node;
		
		map_iterator() {
			this->_node = NULL;
		}

		~map_iterator() {}
		
		map_iterator(const Tree & tree, Node * ptr) {
			this->_tree = (Tree*)&tree;
			this->_node = ptr;
		}

		map_iterator(const Tree * tree, Node * ptr) {
			this->_tree = (Tree*)&tree;
			this->_node = ptr;
		}

		map_iterator(const map_iterator &it) { *this = it; }

		operator const_iterator() {
			return (const_iterator(*_tree, _node));
		}

		Node	*base() const { return (_node); }

		map_iterator & operator = (const map_iterator &it) {
			this->_tree = it._tree;
			this->_node = it._node;
			return (*this);
		}

		map_iterator &operator++() {
            if (this->_node == this->_tree->max_node(this->_tree->_node))
                this->_node = NULL;
            else
                this->_node = this->_tree->getsuccesor(this->_node);
            return (*this);
		}

		map_iterator  operator++(int) {
			Node *tmp = this->_node;
            if (this->_node == this->_tree->max_node(this->_tree->_node))
                this->_node = NULL;
            else
                this->_node = this->_tree->getsuccesor(this->_node);
			return (map_iterator(_tree, tmp));
		}

		map_iterator &operator-- () {
			if (!this->_node || this->_node == this->_tree->_end_node)
				this->_node = _tree->max_node(this->_tree->_node);
			else
				this->_node = this->_tree->getpresuccesor(this->_node);
			return (*this);
		}

		map_iterator  operator-- (int) {
			Node *tmp = _node;
			if (this->_node == NULL || this->_node == this->_tree->_end_node)
				this->_node = _tree->max_node(this->_tree->_node);
			else
				this->_node = this->_tree->getpresuccesor(this->_node);
			return (map_iterator(_tree, tmp));
		}

		map_iterator operator+ (difference_type a) const {
			Node *tmp = _tree->getsuccesor(this->_node);
			while (--a)
				tmp = _tree->getsuccesor(tmp);
			return (map_iterator(_tree, tmp));
		}

		reference operator* () const {
			return (*(_node->value));
		}

		pointer operator-> () const {
			return (_node->value);
		}

		template <class Iter, class Iter2>
		friend	bool	operator== (const Iter &lit, const Iter2 &rit) {
			if ((!lit.base() && rit.base() == rit._tree->_end_node) || (lit.base() == lit._tree->_end_node && !rit.base()))
				return (true);
			return (lit.base() == rit.base());
		}

		template <class Iter, class Iter2>
		friend	bool	operator!= (const Iter &lit, const Iter2 &rit)	{ return !(lit == rit); }

	};

}
