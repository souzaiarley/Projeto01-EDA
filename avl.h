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
        if (search(root, dado) != nullptr){
            return true;
        } 
        return false;
    }

    // Função que verifica se existe algum nó na árvore cuja chave tenha como prefixo 'prefix'
    void prefixo (string prefix, string upperPrefix){
        // ponteiro para Node que ira receber o nó retornado em 'searchPrefix'
        Node<T>* node = searchPrefix(root, upperPrefix);
        // Se node for nulo, então não existe um nó na árvore cuja chave tenha como prefixo 'prefix'.
        // A função deve ser encerrada.
        if (node == nullptr){
            cout << "No results for: '" << prefix << "'" << endl;
            return;
        }
        // Caso contrário, todos os nós que atenderem ao prefixo terão seus dados impressos por meio de 'prefixo'
        cout << "Showing results for '" << prefix << "'" << endl;
        prefixo(node, upperPrefix);
    }

    // Função que verifica se existe algum nó na árvore cuja chave seja igual a 'cpf'
    void cpfData(string cpf){
        // ponteiro para Node que ira receber o nó retornado em 'search'
        Node<T> *node = search(root, cpf);
        // node é nulo, então não existe um nó de chave 'cpf' na árvore
        if (node == nullptr){
            cout << "Error: cpf not found" << endl;
        }
        // node é diferente de nulo, então existe um nó de chave 'cpf' na árvore
        else {
            cout << "Data for '" << cpf << "'" << endl;
            node->pessoa->print();
            // imprime todas as informações do node.
        }
        return;
    }

    // Função pública que verifica se existe algum nó cuja chave esteja no intervalo 'dado1' - 'dado2' 
    void inRange(T dado1, T dado2){
        // Primeiro verifica se dado1 é maior ou igual a dado2.
        // Se sim, a função é interrompida
        if (dado1 > dado2){
            cout << "Error: minimum is greater than maximum" << endl;
            return;
        }
        if (dado1 == dado2){
            cout << "Error: minimum equals to maximum" << endl;
            return;
        }
        // Ponteiro para Node que recebe o nó retornado sem 'searchBetween' 
        Node<T> *node = searchBetween(root, dado1, dado2);

        // Se node for nulo, então não existe nenhum nó na árvore cuja chave esteja no intervalo 'dado1' - 'dado2'
        // A função é interrompida caso isso ocorra.
        // Caso contrário todas os dados dos nós que estejam no intervalo são impressos, por meio da função 'inRange'.
        if (node == nullptr){
            cout << "No results found between '" << dado1 << "' and '" << dado2 << "'" << endl;
            return;
        }
        cout << "Showing results between '" << dado1 << "' and '" << dado2 << "':" << endl;
        inRange(node, dado1, dado2);
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

    // Função search padrão que verifica se um nó de chave 'dado' se encontra na árvore
    Node<T>* search(Node<T> *node, T dado){
        if (node == nullptr){
            return node;
        }
        if (node->dado == dado){
            return node;
        }
        if (dado < node->dado){
            return search(node->left, dado); 
        }
        return search(node->right, dado);
    }


    // Função que retorna o primeiro nó da árvore cuja chave esteja entre 'dado1' e 'dado2'.
    Node<T>* searchBetween(Node<T> *node, T dado1, T dado2){
        if (node == nullptr){   // árvore vazia
            return node;
        }
        if (node->dado < dado1){    // o nó se encontra abaixo do valor mínimo
            return searchBetween(node->right, dado1, dado2);
        }
        if (node->dado > dado2){    // o nó se encontra acima do valor máximo
            return searchBetween(node->left, dado1, dado2);
        }
        return node;                // o nó se encontra dentro do intervalo
    }

    // Função auxiliar de busca que retorna o primeiro nó cuja chave possua 'prefix' como prefixo
    Node <T>* searchPrefix(Node<string> *node, string prefix){
        if (node == nullptr){
            return node;
        }
        // Seja n o comprimento da string 'prefix'

        // Se a substring composta pelos primeiros n caracteres da chave de node
        // for menor que 'prefix', fazemos a busca recursiva para a subárvore direita de node.
        if (node->dado.substr(0, prefix.length()) < prefix) {
            return searchPrefix(node->right, prefix);
        }
        // Se a substring composta pelos primeiros n caracteres da chave de node
        // for maior que 'prefix', fazemos a busca recursiva para a subárvore esquerda de node.
        if (node->dado.substr(0, prefix.length()) > prefix) {
            return searchPrefix(node->left, prefix);
        }
        // Caso contrário, identificamos que os primeiros n caracteres da chave de node
        // são iguais a 'prefix'. Portanto, 'prefix' é prefixo da chave de node. Devemos retorna-lo
        return node;
    }

    // Função que imprime todas as informações do objeto pessoa cujo o nó esteja interligado,
    // desde que sua chave esteja entre 'dado1' e 'dado2'.
    void inRange(Node<T> *node, T dado1, T dado2){
        // Caso base: node é nulo, devemos retornar
        if (node == nullptr){
            return;
        }
        // Se a chave do node for menor que o mínimo 'dado1', devemos fazer a busca em sua subárvore direita,
        // tendo em vista que os nós nessa subárvore são maiores ou iguais a ele, a fim de encontrarmos
        // nós dentro do intervalo 'dado1' - 'dado2'.
        if (node->dado < dado1){
            return inRange(node->right, dado1, dado2);
        }
        // Simetricamente a condição anterior, se a chave do node for maior que o máximo 'dado2', fazemos
        // a busca na subárvore esquerda, a fim de encontrarmos nós no intervalo 'dado1' - 'dado2'.
        if (node->dado > dado2){
            return inRange(node->left, dado1, dado2);
        }
        // Caso contrário, indentificamos que a chave de node se encontra dentro do intervalo estabelecido.
        // Nesse caso devemos imprimi-lo e fazer a busca em suas duas subárvores, pois podem haver nós
        // que também estejam no intervalo.
        inRange(node->left, dado1, dado2);
        node->pessoa->print();
        inRange(node->right, dado1, dado2);
        // Ordem simétrica
        return;
    }

    // Função que imprime todas informações do objeto pessoa cujo o nó esteja interligado,
    // desde que 'prefix' seja prefixo de sua chave.
    void prefixo(Node<string> *node, string prefix){
        // caso base, node é nulo, devemos retornar
        if (node == nullptr){
            return;
        }
        // Seja n o comprimento da string 'prefix'

        // Se a substring composta pelos primeiros n caracteres da chave de node
        // for menor que 'prefix', fazemos a busca recursiva para a subárvore direita de node.
        if (node->dado.substr(0, prefix.length()) < prefix) {
            return prefixo(node->right, prefix);
        }
        // Se a substring composta pelos primeiros n caracteres da chave de node
        // for maior que 'prefix', fazemos a busca recursiva para a subárvore esquerda de node.
        if (node->dado.substr(0, prefix.length()) > prefix) {
            return prefixo(node->left, prefix);
        }
        // Caso contrário, indentificamos que 'prefix' é prefixo da chave de node.
        // Devemos imprimi-lo e fazer a busca recursiva para a esquerda e direita, pois pode haver outros
        // nós que também possuam 'prefix' como prefixo para suas chaves.
        prefixo(node->left, prefix);
        node->pessoa->print();
        prefixo(node->right, prefix);
        // Ordem simétrica
    }
};

#endif