#pragma once

namespace ft
{
    template <typename T, typename Comp, bool Duplicate>
    class AVLTree;

    template <typename T, typename Comp, bool Duplicate, typename Node>
    class AVLTreeIterator
    {
        public:
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;
            typedef bidirectional_iterator_tag iterator_category;

        private:
            typedef AVLTree<T, Comp, Duplicate> tree_type;
            typedef Node node_type;
            typedef AVLTreeIterator<T, Comp, Duplicate, Node> self_type;

            node_type* _current;
            AVLTreeIterator(node_type* current) : _current(current) {}

        public:

        AVLTreeIterator(const self_type& other) : _current(other._current) {}
        AVLTreeIterator(){}

        ~AVLTreeIterator(){}

        self_type& operator=(const self_type& other)
        {
            _current = other._current;
            return *this;
        }

        self_type& operator++()
        {
            if (_current->right)
            {
                _current = _current->right;
                while (_current->left)
                    _current = _current->left;
            }
            else
            {
                node_type* parent = _current->parent;
                while (parent && _current == parent->right)
                {
                    _current = parent;
                    parent = parent->parent;
                }
                _current = parent;
            }
            return *this;
        }

        self_type operator++(int)
        {
            self_type tmp = *this;
            ++(*this);
            return tmp;
        }

        self_type& operator--()
        {
            if (_current->left)
            {
                _current = _current->left;
                while (_current->right)
                    _current = _current->right;
            }
            else
            {
                node_type* parent = _current->parent;
                while (parent && _current == parent->left)
                {
                    _current = parent;
                    parent = parent->parent;
                }
                _current = parent;
            }
            return *this;
        }

        self_type operator--(int)
        {
            self_type tmp = *this;
            --(*this);
            return tmp;
        }

        reference operator*() const
        {
            return _current->value;
        }

        pointer operator->() const
        {
            return &(_current->value);
        }

        template <typename T2, typename Comp2, bool Duplicate2, typename Node2>
        friend bool operator==(const AVLTreeIterator<T2, Comp2, Duplicate2, Node2>& lhs, const AVLTreeIterator<T2, Comp2, Duplicate2, Node2>& rhs);

        template <typename T2, typename Comp2, bool Duplicate2>
        friend class AVLTree;
    };

    template <typename T, typename Comp, bool Duplicate, typename Node>
    bool operator==(const AVLTreeIterator<T, Comp, Duplicate, Node>& lhs, const AVLTreeIterator<T, Comp, Duplicate, Node>& rhs)
    {
        return lhs._current == rhs._current;
    }

    template <typename T, typename Comp, bool Duplicate, typename Node>
    bool operator!=(const AVLTreeIterator<T, Comp, Duplicate, Node>& lhs, const AVLTreeIterator<T, Comp, Duplicate, Node>& rhs)
    {
        return !(lhs == rhs);
    }

    template <typename T, typename Comp, bool Duplicate>
    class AVLTree
    {

        public:
            typedef T value_type;
            typedef Comp key_compare;
            typedef AVLTreeIterator<T, Comp, Duplicate, _node> iterator;
            typedef AVLTreeIterator<const T, Comp, Duplicate, const _node> const_iterator;
            typedef ReverseIterator<iterator> reverse_iterator;
            typedef ReverseIterator<const_iterator> const_reverse_iterator;
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;


        private:
            struct _node{
                T value;
                _node* left;
                _node* right;
                _node* parent;
                int height;
                _node(const T& value) : value(value), left(NULL), right(NULL), parent(NULL), height(1) {}
            };

            typedef AVLTree<T, Comp, Duplicate> tree_type;

            _node* _root;
            size_type _size;
            key_compare _comp;
        

    };
};