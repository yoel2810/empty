#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;
namespace ariel
{
    template<typename T>
    struct Node {
            T data;
            Node* right;
            Node* left;
            Node(T& value): data(value), right(nullptr), left(nullptr){}
        };


    template<typename T>
    class BinaryTree
    {
        
    public:
        Node<T>* root;
        
        BinaryTree():root(nullptr){
            
        }
        BinaryTree(const BinaryTree<T>& node)
        {
            if(node.root!=nullptr)
            {
                root=new Node<T>(node.root->data);
                deep_copy(*node.root,*root);
            }
        }
        BinaryTree(BinaryTree<T> && node) noexcept
        {
            root=node.root;
            node.root=nullptr;
        }
        void deep_copy(const Node<T> &start, Node<T> &end)
        {
            if (start.left != nullptr)
            {
                end.left=new Node<T>(start.left->data);
                deep_copy(*start.left,*end.left);
            }
            if (start.right != nullptr)
            {
                end.right=new Node<T>(start.right->data);
                deep_copy(*start.right,*end.right);
            }
        }
        ~BinaryTree(){}
        Node<T>* find(Node<T>* node,T& value){
            if(node==nullptr)
            {
                return nullptr;
            }
            if(node->data==value)
            {
                return node;
            }
            Node<T>* right=find(node->right, value);
            if(right)
            {
                return right;
            }
            Node<T>* left=find(node->left, value);
            return left;
        }
        
        
        BinaryTree<T>& add_right(T parent, T child)
        {
            if(!find(root, parent))
            {
                throw invalid_argument("no right");
            }
            if(!find(root, parent)->right)
            {
                find(root, parent)->right=new Node<T>(child);
            }
            find(root, parent)->right->data=child;
            return *this;
        }

        BinaryTree<T>& add_left(T parent, T child)
        {
            if(!find(root, parent))
            {
                throw invalid_argument("no left");
            }
            if(!find(root, parent)->left)
            {
                find(root, parent)->left=new Node<T>(child);
            }
            find(root, parent)->left->data = child;
            return *this;
        }


        BinaryTree<T>& add_root(T root_node)
        {
            if(root==nullptr)
            {
                root=new Node<T>(root_node);
            }
            root->data=root_node;
            return *this;
        }


        class Iterator
        {
        public:
            void _inorder(Node<T>* node)
            {
                if(node==nullptr)
                {
                    return;
                }
                _inorder(node->left);
                nodes.push_back(node);
                _inorder(node->right);
            }

            void _preorder(Node<T>* node)
            {
                if(node==nullptr)
                {
                    return;
                }
                nodes.push_back(node);
                _preorder(node->left);
                _preorder(node->right);
            }

            void _postorder(Node<T>* node)
            {
                if(node==nullptr)
                {
                    return;
                }
                _postorder(node->left);
                _postorder(node->right);
                nodes.push_back(node);
            }
            vector <Node<T>*> nodes;
            Node<T>* current_node;
            Iterator(Node<T>* node, int num) noexcept
            {
                if(node != nullptr)
                {
                    if(num == 2)
                    {
                        _postorder(node);
                        current_node=nodes[0];
                    }
                    else if(num == 3)
                    {
                        _preorder(node);
                        current_node=nodes[0];
                    }
                    else
                    {
                        _inorder(node);
                        current_node=nodes[0];
                    }
                }
                else
                {
                    current_node = nullptr;
                }
            }
            Iterator():current_node(nullptr){

            }
            Iterator(Node<T>* n):current_node(n){

            }
            Iterator& operator++()
            {
                if(nodes.size()!=1)
                {
                    nodes.erase(nodes.begin());
                    current_node=nodes[0];
                }
                else
                {
                    current_node=nullptr;
                }
                return *this;
            }
            Iterator operator++(int)
            {
                Iterator ans(nodes[0]);
                ++*this;
                return ans;
            }
            bool operator!= (Iterator node)
            {
                return current_node!=nullptr;
            }
            bool operator== (Iterator node)
            {
                return current_node==node.current_node;
            }
            T& operator*()
            {
                return current_node->data;
            }
            T* operator->()
            {
                return &current_node->data;
            }
        };
        Iterator begin()
        {
            return Iterator{root, 1};
        }
        Iterator end(){
            return Iterator();
        }
        Iterator begin_inorder()
        {
            return begin();
        }
        Iterator end_inorder()
        {
            return Iterator();
        }
        Iterator begin_postorder()
        {
            return Iterator{root, 2};
        }
        Iterator end_postorder()
        {
            return Iterator();
        }
        Iterator begin_preorder()
        {
            return Iterator{root, 3};
        }
        Iterator end_preorder()
        {
            return Iterator();
        }
        BinaryTree& operator=(BinaryTree node)
        {
            if(this == &node)
            {
                return *this;
            }
            if(root!=nullptr)
            {
                delete root;
            }
            root=new Node<T>(node.root->data);
            deep_copy(*node.root,*root);
            return *this;
        }
        BinaryTree& operator=(BinaryTree&& node) noexcept
        {
            *root=node.root;
        }
        friend ostream& operator<< (ostream& os,BinaryTree<T> const& b)
        {
            return os;
        }
    };
}



