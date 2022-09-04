#pragma once
#include "../utility/distance.hpp"
#include "../utility/enable_if.hpp"

namespace ft
{
    template <class Key, class T, class Compare, class Alloc>
    class map;
    template <typename T>
    class bidirectional_iterator
    {

        public:
            typedef ptrdiff_t           difference_type;
            typedef T                   value_type;
            typedef T*                  pointer;
            typedef T&                  reference;
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef typename ft::node<value_type> node;
            typedef typename ft::node<const value_type> const_node;
            typedef node* node_pointer;
            typedef const_node* const_node_pointer;


            //getters

            node_pointer get_ptr() const
            {
                return _ptr;
            }

            node_pointer get_current() const
            {
                return _current;
            }

            //constructors

            bidirectional_iterator()
            {
                _current = NULL;
                _ptr = NULL;
            }

            bidirectional_iterator(node_pointer _current, node_pointer* _ptr)
            {
                this->_current = _current;
                this->_ptr = _ptr;
            }

            bidirectional_iterator(const bidirectional_iterator& other)
            {
                *this = other;
            }

            bidirectional_iterator& operator=(const bidirectional_iterator& other)
            {
                _current = other._current;
                _ptr = other._ptr;
                return *this;
            }

            template <typename A>
            bidirectional_iterator(const bidirectional_iterator<A>& other, typename ft::enable_if<ft::is_convertible<A*, T*>::value>::type* = 0)
            {
                _ptr = (node_pointer*)other.get_ptr();
                _current = (node_pointer)other.get_current();
            }

            bidirectional_iterator &operator++()
            {
                if (_current->right)
                {
                    _current = _current->right;
                    while (_current->left)
                        _current = _current->left;
                }
                else
                {
                    node_pointer tmp = _current->parent;
                    while (tmp && _current == tmp->right)
                    {
                        _current = tmp;
                        tmp = tmp->parent;
                    }
                    _current = tmp;
                }
                return *this;
            }

            bidirectional_iterator operator++(int)
            {
                node_pointer tmp = _current;

                if(_current == _current->max(*_ptr))
                    _current = NULL;
                else
                    ++(*this);

                return bidirectional_iterator(tmp, _ptr);
            }

            bidirectional_iterator &operator--()
            {
                if (_current == NULL)
                    _current = _current->max(*_ptr);
                else if (_current->left)
                {
                    _current = _current->left;
                    while (_current->right)
                        _current = _current->right;
                }
                else
                {
                    node_pointer tmp = _current->parent;
                    while (tmp && _current == tmp->left)
                    {
                        _current = tmp;
                        tmp = tmp->parent;
                    }
                    _current = tmp;
                }
                return *this;
            }


            bidirectional_iterator operator--(int)
            {
                node_pointer tmp = _current;

                if (_current == _current->min(*_ptr))
                    _current = NULL;
                else
                    --(*this);

                return bidirectional_iterator(tmp, _ptr);
            }

            reference operator*() const
            {
                return _current->data;
            }

            pointer operator->() const
            {
                return &(_current->data);
            }

            bool operator==(const bidirectional_iterator& other) const
            {
                return _current == other._current;
            }

            bool operator!=(const bidirectional_iterator& other) const
            {
                return _current != other._current;
            }

            private:
            node_pointer _current;
            node_pointer* _ptr;
    };
};