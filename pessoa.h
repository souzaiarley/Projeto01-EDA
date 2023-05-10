#ifndef PESSOA_H
#define PESSOA_H
#include "data.h"
#include <string>

class Pessoa {
    public:
    // atributos
    std::string cpf;
    std::string nome;
    std::string sobrenome;
    Data nascimento;
    std::string cidade;

    // construtor
    Pessoa (std::string cpf, std::string nome, std::string sobrenome, Data nascimento, std::string cidade)
        : cpf(cpf), nome(nome), sobrenome(sobrenome), nascimento(nascimento), cidade(cidade) 
    {}
    // construtor padrão
    Pessoa (){}

    // Método para imprimir todos os atributos
    void print(){
        std::cout << "=========================" << std::endl;
        std::cout << "Name: " << nome << " " << sobrenome << std::endl;
        std::cout << "CPF: " << cpf << std::endl;
        std::cout << "Born: " << nascimento << std::endl;
        std::cout << "Born in: " << cidade << std::endl;
    }
};

#endif