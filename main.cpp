#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "avl.h"
using namespace std;

// função que retorna um vector de ponteiros para 
// objetos Pessoa do arquivo .csv passado como parâmetro
vector<Pessoa*> fill_vector(string nome_arquivo);

int main (){
    system("chcp 65001 > nul");
    
    vector<Pessoa*> pessoas = fill_vector("data.csv");
    avl_tree<string> *cpfTree = new avl_tree<string>;
    avl_tree<string> *nameTree = new avl_tree<string>;
    avl_tree<Data> *bornTree = new avl_tree<Data>;

    for (int i = 0; i < pessoas.size(); i++){
        if (!cpfTree->search(pessoas[i]->cpf)){     // primeiro verifica se o cpf já está na árvore de cpfs
            cpfTree->add(pessoas[i]->cpf, pessoas[i]);  // se nao estiver, adiciona na arvore 
        }
        nameTree->add(pessoas[i]->nome + pessoas[i]->sobrenome, pessoas[i]); // add nome
        bornTree->add(pessoas[i]->nascimento, pessoas[i]);  // add data de nascimento
    }
}

vector<Pessoa*> fill_vector(string nome_arquivo){
    vector<Pessoa*> pessoas;
    ifstream file;
    string line = "";
    file.open(nome_arquivo);

    getline(file, line);
    line = "";

    while (getline(file, line)){
        string cpf;
        string nome;
        string sobrenome;
        string cidade;
        Pessoa *pessoa;
        int dia, mes, ano;

        string tempString;
        stringstream ss(line);

        getline(ss, cpf, ',');
        getline(ss, nome, ',');
        getline(ss, sobrenome, ',');

        getline(ss, tempString, '/');
        mes = atoi(tempString.c_str());
        tempString = "";

        getline(ss, tempString, '/');
        dia = atoi(tempString.c_str());
        tempString = "";

        getline(ss, tempString, ',');
        ano = atoi(tempString.c_str());
        tempString = "";

        Data born = Data(mes, dia, ano);

        getline(ss, cidade, ',');
        tempString = "";

        pessoa = new Pessoa(cpf, nome, sobrenome, born, cidade);

        pessoas.push_back(pessoa);

        line = "";
    }

    return pessoas;
}