// Esse arquivo e suas funções foram criadas para permitir as interações necessárias do usuário com
// o programa, dependendo das escolhas tomadas no menu interativo. Este arquivo é responsável por
// interligar as decisões do usuário com as implementações da classe 'avl_tree'.
// Além disso, ele trata as entradas e encerra a execução caso alguma entrada for inválida.

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "avl.h"

using namespace std;

// Essa função recebe uma string e a coloca em formato de cpf.
string formatCpf(string cpf){
    if (cpf.size() >= 9){
        // Se a string já está formatada, os caracteres '-' e '.' são removidos
        cpf.erase(std::remove(cpf.begin(), cpf.end(), '.'), cpf.end());
        cpf.erase(std::remove(cpf.begin(), cpf.end(), '-'), cpf.end());
        
        // Os caracteres '-' e '.' são inseridos na string em seus respectivos campos.
        cpf.insert(9, "-");
        cpf.insert(6, ".");
        cpf.insert(3, ".");
    }
    return cpf;
}

// Faz com que uma string fique inteiramente maiuscula
std::string toUpper(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return std::toupper(c);
    });
    return str;
}

// verifica se uma string é alfanumerica
bool isAlphanumeric(string str) {
    for (char c : str) {
        if (!isalnum(c)) {
            return false;
        }
    }
    return true;
}

// Esta função vai receber um ano e irá verificar se o ano é bissexto
bool isLeap(int year) {
  if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
    return true;
  } else {
    return false;
  }
}

// Função auxiliar que "interligará" as ações do usuário com as funções da árvore passada como parâmetro
void func1 (avl_tree<string> *tree){
    string cpf;

    cout << "Insert CPF: ";
    getline(cin, cpf);
    // Faz o tratamento do cpf
    cpf = formatCpf(cpf);

    // Verifica se a entrada para CPF é uma entrada válida.
    // A entrada para um cpf deve conter exatamente 14 caracteres e não deve conter letras.
    if (isAlphanumeric(cpf) || cpf.length() != 14){
        cout << "error: Invalid CPF" << endl;
        return;
    }
    
    system("clear || cls");
    // Chama a funcão da árvore passada como parâmetro para fazer a busca or CPF
    tree->cpfData(cpf);
}

// Função auxiliar que "interligará" as ações do usuário com as funções da árvore passada como parâmetro
void func2 (avl_tree<string> *tree){
    string str;

    cout << "Search for: ";
    getline(cin, str);

    system("clear || cls");
    // Chama a função 'prefixo()' para imprimir as informações dos nós cujas chaves começam com 'str'
    tree->prefixo(str, toUpper(str));
}

// Função auxiliar que "interligará" as ações do usuário com as funções da árvore passada como parâmetro
void func3 (avl_tree<Data> *tree){
    Data date1, date2;
    int month, day, year;
    string str;
    stringstream ss;
    char ch;
    int meses[12] = {31,0, 31,30,31,30,31,31,30,31,30,31}; // vetor com os dias de todos os meses do ano, exceto fervereiro
    
    cout << "Insert first date (MM/DD/YYYY): ";
    getline(cin, str);
    ss << str;

    ss >> month >> ch >> day >> ch >> year;
    // tratamento de data
    if (year > 2023 || year < 1900 || month < 1 || month > 12){
        cout << "error: invalid date" << endl;
        return;
    }
    if (month != 2){
        if (day > meses[month-1] || day < 1){
            cout << "error: invalid date" << endl;
            return;
        }
    }
    if (month == 2) {
        if (isLeap(year) && (day > 29 || day < 1)){
            cout << "error: invalid date" << endl;
            return;
        }
        if (!isLeap(year) && (day > 28 || day < 1)){
            cout << "error: invalid date" << endl;
            return;
        }
    }

    date1 = Data(month, day, year);

    str.clear();
    ss.clear();

    cout << "\nInsert second date (MM/DD/YYYY): ";
    getline(cin, str);
    ss << str;

    ss >> month >> ch >> day >> ch >> year;
    // tratamento de data
    if (year > 2023 || year < 1900 || month < 1 || month > 12){
        cout << "error: invalid date" << endl;
        return;
    }
    if (month != 2){
        if (day > meses[month-1] || day < 1){
            cout << "error: invalid date" << endl;
            return;
        }
    }
    if (month == 2) {
        if (isLeap(year) && (day > 29 || day < 1)){
            cout << "error: invalid date" << endl;
            return;
        }
        if (!isLeap(year) && (day > 28 || day < 1)){
            cout << "error: invalid date" << endl;
            return;
        }
    }

    date2 = Data(month, day, year);
    system("clear || cls");
    // Chama a função que imprimirá todos os nós cujas chaves se encontram no intervalo determinado
    tree->inRange(date1, date2);
}