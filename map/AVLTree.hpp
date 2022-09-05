#pragma once

namespace ft
{
    template <class T>
    struct Node
    {
        T val;
        Node *left;
        Node *right;
        Node *parent;
        int height;
        int balanceFactor;

        Node(): parent(nullptr), left(nullptr), right(nullptr) {}
        Node(const T& val): val(val) {}
        Node(const T& val, const int height) : val(val), parent(nullptr), left(nullptr), right(nullptr), height(height), balanceFactor(0) {}
    };

    template <class T, class Compare, class Alloc>
    class AVLTree
    {
    public:
        typedef T value_type;
        typedef Compare key_compare;
        typedef Node<T>* node_pointer;
        typedef typename Alloc::template rebind<Node<T>>::other allocator_type;
        typedef typename allocator_type::size_type size_type;

    private:
        node_pointer _root;
        node_pointer _end;
        allocator_type _alloc;
        key_compare _cmp;
        size_type _size;

    public:
        AVLTree(const allocator_type &alloc = allocator_type(), const key_compare &cmp = key_compare()) : _root(nullptr), _end(nullptr), _alloc(alloc), _comp(cmp), _size(0) {
            _end = _alloc.allocate(1);
            _alloc.construct(_end);
        }

        ~AVLTree() {
            clear();
            _alloc.deallocate(_end, 1);
            _end = nullptr;
        }

        size_type size() const {
            return _size;
        }

        size_type max_size() const {
            return _alloc.max_size();
        }

        allocator_type get_allocator() const {
            return this->_alloc;
        }

        node_pointer get_End() const {
            return this->_end;
        }

        node_pointer get_Min(node_pointer node = nullptr) const {
            if (node == nullptr)
                node = _root;
            while (node->left != nullptr)
                node = node->left;
            return node;
        }

        node_pointer get_Max(node_pointer node = nullptr) const {
            if (node == nullptr)
                node = _root;
            while (node->right != nullptr)
                node = node->right;
            return node;
        }

        node_pointer LowerBnd(const value_type &val){
            node_pointer node = get_Min();
            while(node != _end){
                if(!_cmp(node->val.first, val.first))
                    return node;
                node = successort(node);
            }
            return _end;
        }

        node_pointer upperBnd(const value_type &val){
            node_pointer node = get_Min();
            while(node != _end){
                if(_cmp(val.first, node->val.first))
                    return node;
                node = successort(node);
            }
            return _end;
        }

        void swap(AVLTree &tree){
            node_pointer root = _root;
            node_pointer end = _end;
            size_type size = _size;
            allocator_type alloc = _alloc;
            key_compare cmp = _cmp;

            _root = tree._root;
            _end = tree._end;
            _size = tree._size;
            _alloc = tree._alloc;
            _cmp = tree._cmp;

            tree._root = root;
            tree._end = end;
            tree._size = size;
            tree._alloc = alloc;
            tree._cmp = cmp;
        }

        void clear(){
            if (_root == nullptr)
                return;
            clear(_root);
            _root = nullptr;
            _size = 0;
        }

        node_pointer find(const value_type &val){
            return find(val, _root);
        }

        void insert(const value_type &val){
            insert(val, _root, _end);
            _end->left = _root;
            _root->parent = _end;
        }

        void erase(const value_type &val){
            erase(_root, val);
            _end->left = _root;
            if(_root)
                _root->parent = _end;
        }

        private:
            void eraseHelp(node_pointer &node, node_pointer &parent){
                node_pointer tmp ;
                if(node->right)
                    tmp = node->right;
                else
                    tmp = node->left;
                if(tmp)
                    tmp->parent = parent;
                _alloc.deallocate(node, 1);
                node = tmp;
                _size--;
            }

            void erase(node_pointer &node, const value_type &val){
                if(!node)
                    return;
                if(node->val.first == val.first)
                {
                    if(!node->left || !node->right){
                        eraseHelp(node, node->parent);
                        return;
                    }
                    else
                    {
                        if(node->left->height > node->right->height)
                        {
                            value_type value(get_Max(node->left)->val);
                            _alloc.construct(node, value);
                            erase(node->left, value);
                        }
                        else
                        {
                            value_type value(get_Min(node->right)->val);
                            _alloc.construct(node, value);
                            erase(node->right, value);
                        }
                    }
                }

                else if(_cmp(val.first, node->val.first))
                    erase(node->left, val);
                else
                    erase(node->right, val);

                update(node);
                balance(node);
            }

            void insert(const value_type &val, node_pointer &node, node_pointer &parent){
                if(!node)
                {
                    node = _alloc.allocate(1);
                    _alloc.construct(node, val, 0);
                    node->parent = parent;
                    _size++;
                    return;
                }
                if(_cmp(val.first, node->val.first))
                    insert(val, node->left, node);
                else
                    insert(val, node->right, node);
                update(node);
                balance(node);
            }


                //find
            node_pointer find(const value_type &val, node_pointer node){
                if(!node)
                    return _end;
                if(node->val.first == val.first)
                    return node;
                if(_cmp(val.first, node->val.first))
                    return find(val, node->left);
                else
                    return find(val, node->right);
            }
    };
};