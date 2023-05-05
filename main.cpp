#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "avl.h"
using namespace std;

// função que retorna um vector de ponteiros para 
// objetos Pessoa do arquivo .csv passado como parâmetro
vector<Pessoa*> fill_vector(string arquivo);

int main (){
    system("chcp 65001 > nul");
    
    vector<Pessoa*> pessoas = fill_vector("data.csv");
}

vector<Pessoa*> fill_vector(string arquivo){
    vector<Pessoa*> pessoas;
    ifstream file;
    string line = "";
    file.open(arquivo);

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