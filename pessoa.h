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

    void print(){
        std::cout << "Nome: " << nome << " " << sobrenome << std::endl;
        std::cout << "CPF: " << cpf << std::endl;
        std::cout << "Data de Nascimento: " << nascimento << std::endl;
        std::cout << "Natural de: " << cidade << std::endl;
    }
};

#endif