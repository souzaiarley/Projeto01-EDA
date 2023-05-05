#ifndef AVL_H
#define AVL_H
#include <iostream>
#include "node.h"
using namespace std;

template <typename T>
class avl_tree {
public:
    avl_tree() = default;
    avl_tree(const avl_tree& t) = delete;
    avl_tree& operator=(const avl_tree& t) = delete;
    
    void add(T dado, Pessoa *pessoa){
        root = add(root, dado, pessoa);
    }

    void bshow() const{
        bshow(root, "");
    }

    void clear(){
        root = clear(root);
    }

    bool search(T dado){
        return search(root, dado); 
    }

    ~avl_tree(){
        clear();
    }

private:
    Node<T> *root {nullptr};

    int height(Node<T> *node){
        if (node == nullptr) return 0;
        else return node->height;
    }

    int balance(Node<T> *node){
        return height(node->right) - height(node->left);
    }

    Node<T>* rightRotation(Node<T> *p){
        Node<T> *u = p->left;
        p->left = u->right;
        u->right = p;
        // recalcular as alturas de p e de u
        p->height = 1 + max(height(p->left), height(p->right));
        u->height = 1 + max(height(u->left), height(u->right));
        return u;
    }

    Node<T>* leftRotation(Node<T> *p){
        Node<T> *u = p->right;
        p->right = u->left;
        u->left = p;
        // recalcular as alturas de p e de u
        p->height = 1 + max(height(p->left), height(p->right));
        u->height = 1 + max(height(u->left), height(u->right));
        return u;
    }

    Node<T>* add(Node<T> *node, T dado, Pessoa *pessoa){
        if (node == nullptr){
            return new Node<T>(pessoa, nullptr, nullptr, dado);
        }
        if (dado < node->dado){
            node->left = add(node->left, dado, pessoa);
        }
        else {
            node->right = add(node->right, dado, pessoa);
        }

        node = fixup_node(node, dado);
        
        return node;
    }

    Node<T>* fixup_node(Node<T> *p, T key){
        // recalcula a altura de p
        p->height = 1 + max(height(p->left), height(p->right));

        // calcula o balanco de p
        int bal = balance(p);

        if (bal < -1 && key < p->left->dado){
            return rightRotation(p);
        }
        else if (bal < -1 && key >= p->left->dado){
            p->left = leftRotation(p->left);
            return rightRotation(p);
        }
        else if (bal > 1 && key >= p->right->dado){
            return leftRotation(p);
        }
        else if (bal > 1 && key < p->right->dado){
            p->right = rightRotation(p->right);
            return leftRotation(p);
        }

        return p;
    }

    void bshow(Node<T> *node, std::string heranca) const{
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->right , heranca + "r");
        for(int i = 0; i < (int) heranca.size() - 1; i++)
            std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
        if(heranca != "")
            std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
        if(node == nullptr){
            std::cout << "#" << std::endl;
            return;
        }
        std::cout << node->dado << std::endl;
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->left, heranca + "l");
    }

    Node<T>* clear(Node<T> *node){
        if(node != nullptr) {
            node->left = clear(node->left);
            node->right = clear(node->right);
            delete node;
        }
        return nullptr;
    }

    bool search(Node<T> *node, T dado){
        if (node == nullptr){
            return false;
        }
        if (node->dado == dado){
            return true;
        }
        if (dado < node->dado){
            return search(node->left, dado); 
        }
        return search(node->right, dado);
    }
};

#endif