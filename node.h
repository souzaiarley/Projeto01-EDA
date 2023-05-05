#ifndef NODE_H
#define NODE_H
#include "pessoa.h"

template <typename T>
struct Node {
    // atributos
    Pessoa *pessoa;
    Node<T> *left;
    Node<T> *right;
    T dado;
    int height;

    // construtor
    Node (Pessoa *pessoa, Node<T> *left, Node<T> *right, T dado, int height = 1)
        : pessoa(pessoa), left(left), right(right), dado(dado), height(height)
    {}
};

#endif