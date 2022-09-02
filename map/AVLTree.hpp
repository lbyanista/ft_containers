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

            Comp _comp;
            _node* _root;
            _node* _snt;
            size_type _lenght;

            bool _comp_node(T const &val, _node *node)const {
                if(node == _snt)
                    return false;
                return _comp(node->value, val);
            }

            static difference_type _balance_factor(_node* node)
            {
                if (!node)
                    return 0;
                return height(node->left) - height(node->right);
            }

            static void _rotate_left(_node **target)
            {
                _node *tmp = (*target)->right;
                _node *parent = (*target)->parent;
                (*target)->parent = tmp;
                tmp->parent = parent;
                (*target)->right = tmp->left;
                tmp->left = *target;
                (*target)->height = max((*target)->left ? (*target)->left->height : -1,
                                        (*target)->right ? (*target)->right->height : -1) + 1;
                *target = tmp;
                tmp->height = max(tmp->left ? tmp->left->height : -1,
                                tmp->right ? tmp->right->height : -1) + 1;
            }

            static void _rotate_right(_node **target)
            {
                _node *tmp = (*target)->left;
                _node *parent = (*target)->parent;
                (*target)->parent = tmp;
                tmp->parent = parent;
                (*target)->left = tmp->right;
                tmp->right = *target;
                (*target)->height = max((*target)->left ? (*target)->left->height : -1,
                                        (*target)->right ? (*target)->right->height : -1) + 1;
                *target = tmp;
                tmp->height = max(tmp->left ? tmp->left->height : -1,
                                tmp->right ? tmp->right->height : -1) + 1;
            }


            void _rebalance(_node *node)
            {
                if (node->left)
                    _reclear(node->left);
                if (node->right)
                    _reclear(node->right);
                if(node != _snt)
                    delete node;
            }

            void _ereas_rebalance(_node *parent)
            {
                for (_node *p = parent; p; p = p->parent){
                    p->height = max(p->left ? p->left->height : -1,
                                    p->right ? p->right->height : -1) + 1;

                    if (_balance_factor(p) <= -2 || _balance_factor(p) >= 2)
                    {
                        _node *x = p;
                        _node *y = x->left->height > x->right->height ? x->left : x->right;
                        _node *z ;

                        if(y->left->height > y->right->height)
                            z = y == x->left ? y->left : y->right;
                        else
                            z = y->left->height > y->right->height ? y->left : y->right;

                        if (y == x->left)
                        {
                            if(z == x->left->right)
                                _rotate_left(y);
                            _rotate_right(x);
                        }

                        else if(y == x->right)
                        {
                            if(z == x->right->left)
                                _rotate_right(y);
                            _rotate_left(x);
                        }
                    }
                }
            }


            // from here 02/09/2022
            void _insert_rebalance(_node *node)
            {
                for (_node *p = node; p; p = p->parent){
                    p->height = max(p->left ? p->left->height : -1,
                                    p->right ? p->right->height : -1) + 1;

                    if (_balance_factor(p) <= -2 || _balance_factor(p) >= 2)
                    {
                        _node *x = p;
                        _node *y = x->left->height > x->right->height ? x->left : x->right;
                        _node *z ;
                        if(y->left->height > y->right->height)
                            z = y == x->left ? y->left : y->right;
                        else
                            z = y->left->height > y->right->height ? y->left : y->right;
                        if (y == x->left)
                        {
                            if(z == x->left->right)
                                _rotate_left(y);
                            _rotate_right(x);
                        }

                        else if(y == x->right)
                        {
                            if(z == x->right->left)
                                _rotate_right(y);
                            _rotate_left(x);
                        }
                    }
                }
            }

    };
};