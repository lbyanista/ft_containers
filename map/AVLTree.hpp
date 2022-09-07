#pragma once

#include <iostream>
#include <memory>
#include "../utility/pair.hpp"
#include "../utility/make_pair.hpp"
#include "../iterator/reverse_iterator.hpp"
#include <cmath>

namespace ft
{
    template <class value_type, class Compare = std::less<typename value_type::first_type>, class Alloc = std::allocator<value_type>>
    class AVLTree{
        public:
        typedef size_t  size_type;
        typedef typename value_type::first_type key;
        typedef typename value_type::sec T;

        typedef struct node
        {
            value_type      *value;
            size_type       height;
            struct node     *parent; // using in find and insert ...
            struct node     *left;
            struct node     *right;
            int             balance;
        }                   Node;

        Node                                            *_node;
        Node                                            *_end_node;
        Compare                                         _ob_comp;
        typename Alloc::template rebind<Node>::other    _alloc_node;
        Alloc                                           _alloc_pair;

        AVLtree(){
            this->_node = NULL;
            this->_end_node = _alloc_node.allocate(1);
            this->_end_node->height = 19;
        }

        ~AVLtree(){
            _alloc_node.deallocate(_end_node, 1);
        }

        Node *getHead(Node *node){
            Node *node_parent = node;
            while(true){
                if(!node_parent || !node_parent->parent)
                    return (node_parent);
                node_parent = node_parent->parent;
            }
            return node_parent;
        }

        Node *new_node(const value_type &val, Node *parent){
            Node *node = this->_alloc_node.allocate(1);
            node->value = this->_alloc_pair.allocate(1);
            this->_alloc_pair.construct(node->value, val);
            node->left = NULL;
            node->right = NULL;
            node->parent = parent;
            node->height = 1;
            return (node);
        }

        int max(int i, int j){
            return a > b? a : b;
        }

        int node_hieght(Node *node){
            if(node == NULL)
                return 0;
            return node->height;
        }

        int balance(Node *node){
            if(node == NULL)
                return 0;
            return (node->height(node->left) - node->height(node->right))
        }

        /*
                      A                                      B 
                     / \                                   /   \
                    B   1                                 C     A
                   / \          - - - - - - - - ->      /  \   /  \ 
                  C   2                                4    3 2    1
                 / \
                4   3
			*/


        Node *rotate_right(Node *r){
            Node *y = r->left;
			Node *T = y->right;
			y->right = z;
			r->left = T;
			
			y->parent = r->parent;
			r->parent = y;
			if (T)
				T->parent = r;
			r->height = this->max(this->node_height(r->left), this->node_height(r->right)) + 1;
			y->height = this->max(this->node_height(y->left), this->node_height(y->right)) + 1;
			return (y);
        }

        /*
          A                                B
         /  \                            /   \ 
        1    B                          A      C
            /  \   - - - - - - - ->    / \    / \
           2    C                     1   2  3   4
               / \
              3   4
		*/

        Node *rotate_left(Node *l){
            Node	*y = l->right;
			Node	*T = y->left;

			y->left = l;
			l->right = T;

			y->parent = l->parent;
			l->parent = y;
			if (T)
				T->parent = l;
			l->height = this->max(this->node_height(l->left), this->node_height(l->right)) + 1;
			y->height = this->max(this->node_height(y->left), this->node_height(y->right)) + 1;
			return (y)
        }

        Node *insert(Node * &node, key k, T value, Node *parent = NULL){
            Node *tmp;
            if(!node){
                node = this->new_node(ft::make_pair<key, T>(key, value), parent);
                tmp = node;
                this->_node = getHead(node);
                return tmp;
            }

            if(this->_ob_comp(k, node->value->first))
                tmp = insert(node->left, k, value, node);
            
            else if(this->_ob_comp(node->value->first, k))
                tmp = insert(node->right, k, value, node);
            
            else
            {
                this->_node = getHead(node);
                return node;
            }

            node->height = 1 + max(node_height(node->left), node_height(node->right));
            int balance = balanced(node);

            if(balance > 1 && this->_ob_comp(k, node->left->value->first))
                node = rotate_right(node);
            if(balance < -1 && this->_ob_comp(node->right->value->first, k))
                node = rotate_left(node);

            if(balance > 1 && this->_ob_comp(node->left->value->first, k)){
                node->left = rotate_left(node->left);
                node = rotate_right(node);
            }
            if(balance < -1 && this->_ob_comp(k, node->right-value->first)){
                node->right = rotate_right(node->right);
                node = rotate_left(node);
            }
            this->node = getHead(node);
            return tmp;
        }

        Node *min_node(const Node *node)const {
            Node *tmp = (Node*)node;

            while (tmp->left)
                tmp = tmp->left;
            return (tmp);
        }

        

        
    };

    // template <class T, class Compare, class Alloc>
    // class AVLTree
    // {
    // public:
    //     typedef T value_type;
    //     typedef Compare key_compare;
    //     typedef Node<T>* node_pointer;
    //     typedef typename Alloc::template rebind<Node<T>>::other allocator_type;
    //     typedef typename allocator_type::size_type size_type;

    // private:
    //     node_pointer _root;
    //     node_pointer _end;
    //     allocator_type _alloc;
    //     key_compare _cmp;
    //     size_type _size;

    // public:
    //     AVLTree(const allocator_type &alloc = allocator_type(), const key_compare &cmp = key_compare()) : _root(nullptr), _end(nullptr), _alloc(alloc), _comp(cmp), _size(0) {
    //         _end = _alloc.allocate(1);
    //         _alloc.construct(_end);
    //     }

    //     ~AVLTree() {
    //         clear();
    //         _alloc.deallocate(_end, 1);
    //         _end = nullptr;
    //     }

    //     size_type size() const {
    //         return _size;
    //     }

    //     size_type max_size() const {
    //         return _alloc.max_size();
    //     }

    //     allocator_type get_allocator() const {
    //         return this->_alloc;
    //     }

    //     node_pointer get_End() const {
    //         return this->_end;
    //     }

    //     node_pointer get_Min(node_pointer node = nullptr) const {
    //         if (node == nullptr)
    //             node = _root;
    //         while (node->left != nullptr)
    //             node = node->left;
    //         return node;
    //     }

    //     node_pointer get_Max(node_pointer node = nullptr) const {
    //         if (node == nullptr)
    //             node = _root;
    //         while (node->right != nullptr)
    //             node = node->right;
    //         return node;
    //     }

    //     node_pointer LowerBnd(const value_type &val){
    //         node_pointer node = get_Min();
    //         while(node != _end){
    //             if(!_cmp(node->val.first, val.first))
    //                 return node;
    //             node = successort(node);
    //         }
    //         return _end;
    //     }

    //     node_pointer upperBnd(const value_type &val){
    //         node_pointer node = get_Min();
    //         while(node != _end){
    //             if(_cmp(val.first, node->val.first))
    //                 return node;
    //             node = successort(node);
    //         }
    //         return _end;
    //     }

    //     void swap(AVLTree &tree){
    //         node_pointer root = _root;
    //         node_pointer end = _end;
    //         size_type size = _size;
    //         allocator_type alloc = _alloc;
    //         key_compare cmp = _cmp;

    //         _root = tree._root;
    //         _end = tree._end;
    //         _size = tree._size;
    //         _alloc = tree._alloc;
    //         _cmp = tree._cmp;

    //         tree._root = root;
    //         tree._end = end;
    //         tree._size = size;
    //         tree._alloc = alloc;
    //         tree._cmp = cmp;
    //     }

    //     void clear(){
    //         if (_root == nullptr)
    //             return;
    //         clear(_root);
    //         _root = nullptr;
    //         _size = 0;
    //     }

    //     node_pointer find(const value_type &val){
    //         return find(val, _root);
    //     }

    //     void insert(const value_type &val){
    //         insert(val, _root, _end);
    //         _end->left = _root;
    //         _root->parent = _end;
    //     }

    //     void erase(const value_type &val){
    //         erase(_root, val);
    //         _end->left = _root;
    //         if(_root)
    //             _root->parent = _end;
    //     }

    //     private:
    //         void eraseHelp(node_pointer &node, node_pointer &parent){
    //             node_pointer tmp ;
    //             if(node->right)
    //                 tmp = node->right;
    //             else
    //                 tmp = node->left;
    //             if(tmp)
    //                 tmp->parent = parent;
    //             _alloc.deallocate(node, 1);
    //             node = tmp;
    //             _size--;
    //         }

    //         void erase(node_pointer &node, const value_type &val){
    //             if(!node)
    //                 return;
    //             if(node->val.first == val.first)
    //             {
    //                 if(!node->left || !node->right){
    //                     eraseHelp(node, node->parent);
    //                     return;
    //                 }
    //                 else
    //                 {
    //                     if(node->left->height > node->right->height)
    //                     {
    //                         value_type value(get_Max(node->left)->val);
    //                         _alloc.construct(node, value);
    //                         erase(node->left, value);
    //                     }
    //                     else
    //                     {
    //                         value_type value(get_Min(node->right)->val);
    //                         _alloc.construct(node, value);
    //                         erase(node->right, value);
    //                     }
    //                 }
    //             }

    //             else if(_cmp(val.first, node->val.first))
    //                 erase(node->left, val);
    //             else
    //                 erase(node->right, val);

    //             update(node);
    //             balance(node);
    //         }

    //         void insert(const value_type &val, node_pointer &node, node_pointer &parent){
    //             if(!node)
    //             {
    //                 node = _alloc.allocate(1);
    //                 _alloc.construct(node, val, 0);
    //                 node->parent = parent;
    //                 _size++;
    //                 return;
    //             }
    //             if(_cmp(val.first, node->val.first))
    //                 insert(val, node->left, node);
    //             else
    //                 insert(val, node->right, node);
    //             update(node);
    //             balance(node);
    //         }


    //             //find
    //         node_pointer find(const value_type &val, node_pointer node){
    //             if(!node)
    //                 return _end;
    //             if(node->val.first == val.first)
    //                 return node;
    //             if(_cmp(val.first, node->val.first))
    //                 return find(val, node->left);
    //             else
    //                 return find(val, node->right);
    //         }
    // };
};