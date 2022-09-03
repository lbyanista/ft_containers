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
            void _insert_rebalance(_node *insert)
            {
                for(_node *node = insert; node; node = node->parent){
                    node->height = max(node->left ? node->left->height : -1,
                                        node->right ? node->right->height : -1) + 1;

                    _node **x ;
                    if(!node->parent)
                        x = &_root;
                    else
                        x = node->parent->left == node ? &node->parent->left : &node->parent->right;
                    if(_balance_factor(node) < -1)
                    {
                        if(_balance_factor(node->right) > 0)
                            _rotate_right(&(*x)->right);
                        _rotate_left(x);
                        break;
                    }

                    else if(_balance_factor(node) > 1)
                    {
                        if(_balance_factor(node->left) < 0)
                            _rotate_left(&(*x)->left);
                        _rotate_right(x);
                        break;
                    }
                }
            }

            public:
                AVLTree(const Comp& comp = Comp()) : _comp(comp), _lenght(0)
                {
                    _root = new _node(E(), NULL, NULL, NULL, 0);
                    _snt = _root;
                }

                AVLTree(const _Self &o): _comp (o._comp), _lenght(0)
                {
                    _root = new _node(E(), NULL, NULL, NULL, 0);
                    _snt = _root;
                    insert(o.begin(), o.end());
                }

                Comp const &compare()const {
                    return _comp;
                }

                ~AVLTree()
                {
                    clear();
                    delete _snt;
                }

                _self &operator=(const _Self &o)
                {
                    if (this != &o)
                    {
                        clear();
                        insert(o.begin(), o.end());
                    }
                    return *this;
                }

                iterator begin()
                {
                    _node *node = _root;
                    while (node->left != _snt)
                        node = node->left;
                    return iterator(node);
                }

                const_iterator begin() const
                {
                    _node *node = _root;
                    while (node->left != _snt)
                        node = node->left;
                    return const_iterator(node);
                }

                iterator end()
                {
                    return iterator(_snt);
                }

                const_iterator end() const
                {
                    return const_iterator(_snt);
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

                bool empty() const
                {
                    return _lenght == 0;
                }

                size_type size() const
                {
                    return _lenght;
                }

                size_type max_size() const
                {
                    return std::numeric_limits<size_type>::max() / sizeof(value_type); // maybe delete /
                }

                Pair<iterator, bool> insert(const value_type &val){
                    return insert(iterator(_root), val);
                }

                Pair<iterator, bool> insert(iterator h, const value_type &val){
                    (void)h;
                    _node *part = _root;
                    _node *new_node;

                    while(1){
                        if(part == _snt){
                            _node *parent = _snt->parent;
                            _node *&place = parent ? parent->right : _root;

                            new_node = new _node(val, parent, NULL, _snt, 0);
                            place = new_node;
                            _snt->parent = new_node;
                            break;
                        }

                        bool res = _comp(val, part->e1);

                        if(!Duplicate && !res && !_comp(part->e1, val)){
                            return make_pair(iterator(part), false);
                        }

                        if(res){
                            if(part->left)
                                part = part->left;
                            else 
                            {
                                new_node = new _node(val, part, NULL, NULL, 0);
                                part->left = new_node;
                                break;
                            }
                        }

                        else 
                        {
                            if(part->right)
                                part = part->right;
                            else 
                            {
                                new_node = new _node(val, part, NULL, NULL, 0);
                                part->right = new_node;
                                break;
                            }
                        }
                    }
                    
                    _lenght++;
                    return make_pair(iterator(new_node), true);
                }

                template <class InputIterator>
                void insert(InputIterator first, InputIterator last)
                {
                    for (; first != last; ++first)
                        insert(*first);
                }

                void erase(iterator position)
                {
                    _node *node = position._node;
                    _node *parent = node->parent;
                    _node *left = node->left;
                    _node *right = node->right;

                    if(left == _snt && right == _snt){
                        if(parent){
                            if(parent->left == node)
                                parent->left = NULL;
                            else
                                parent->right = NULL;
                        }
                        else
                            _root = NULL;
                    }

                    else if(left == _snt){
                        if(parent){
                            if(parent->left == node)
                                parent->left = right;
                            else
                                parent->right = right;
                        }
                        else
                            _root = right;
                        right->parent = parent;
                    }

                    else if(right == _snt){
                        if(parent){
                            if(parent->left == node)
                                parent->left = left;
                            else
                                parent->right = left;
                        }
                        else
                            _root = left;
                        left->parent = parent;
                    }

                    else{
                        _node *next = node->right;
                        while(next->left != _snt)
                            next = next->left;

                        _node *next_parent = next->parent;
                        _node *next_right = next->right;

                        if(next_parent->left == next)
                            next_parent->left = next_right;
                        else
                            next_parent->right = next_right;
                        if(next_right != _snt)
                            next_right->parent = next_parent;

                        if(parent){
                            if(parent->left == node)
                                parent->left = next;
                            else
                                parent->right = next;
                        }
                        else
                            _root = next;
                        next->parent = parent;

                        next->left = left;
                        left->parent = next;

                        next->right = right;
                        right->parent = next;
                    }

                    delete node;
                    _lenght--;
                }

                void ereas(iterator first, iterator last)
                {
                    while (first != last)
                        erase(first++);
                }

                void swap(AVLTree <T, Comp, Duplicate> &o)
                {
                    std::swap(_root, o._root);
                    std::swap(_snt, o._snt);
                    std::swap(_lenght, o._lenght);
                }

                void clear(){
                    _rebalance(_root); // recleare
                    _snt->left = NULL;
                    _snt->right = NULL;
                    _snt->height = 0;
                    _root = _snt;
                    _lenght = 0;
                }

                iterator find(const key_type &key)
                {
                    _node *node = _root;
                    while (node != _snt)
                    {
                        if (_comp(key, node->e1))
                            node = node->left;
                        else if (_comp(node->e1, key))
                            node = node->right;
                        else
                            return iterator(node);
                    }
                    return end();
                }

                const_iterator find(const key_type &key) const
                {
                    _node *node = _root;
                    while (node != _snt)
                    {
                        if (_comp(key, node->e1))
                            node = node->left;
                        else if (_comp(node->e1, key))
                            node = node->right;
                        else
                            return const_iterator(node);
                    }
                    return end();
                }

                size_type count(const value_type &val) const
                {
                    size_type count = 0;
                    _node *node = _root;

                    while (node && node != _snt)
                    {
                        bool ret = _comp(node->e1, val);
                        if(!ret && !_comp(val, node->e1))
                        {
                            if(Duplicate)
                                count++;
                            else
                                return 1;
                            node = node->right;
                        }
                        else if(!ret)
                            node = node->left;
                        else
                            node = node->right;
                    }

                    return count;
                }

                
    };
};