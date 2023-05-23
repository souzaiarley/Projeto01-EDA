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

void menu(){
    cout << "╔═════════╦═══════════════════╦═════════╗\n";
    cout << "╠═════════╣    DATA SEARCH    ╠═════════╣\n";
    cout << "╠═════════╩═══════════════════╩═════════╣\n";
    cout << "║                                       ║\n";
    cout << "║           [1] Search CPF              ║\n";
    cout << "║                                       ║\n";
    cout << "║           [2] Search names            ║\n";
    cout << "║                                       ║\n";
    cout << "║           [3] Filter by date          ║\n";
    cout << "║                                       ║\n";
    cout << "║           [4] Add person              ║\n";
    cout << "║                                       ║\n";
    cout << "║           [5] Exit                    ║\n";
    cout << "║                                       ║\n";
    cout << "╚═══════════════════════════════════════╝\n";
    cout << "Input: ";
}

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

// verifica se uma string é somente numerica
bool isNumeric(string str) {
    for (char c : str) {
        if (!isdigit(c)) {
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

    cout << "▸ Insert CPF: ";
    getline(cin, cpf);

    // Verifica se a entrada para CPF é uma entrada válida.
    // A entrada para um cpf deve conter exatamente 14 caracteres e não deve conter letras.
    if (!isNumeric(cpf) || cpf.length() != 11){
        cout << "error: Invalid CPF" << endl;
        return;
    }
    // Faz o tratamento do cpf
    cpf = formatCpf(cpf);

    
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
    
    cout << "▸ Insert first date (MM/DD/YYYY): ";
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

    cout << "\n▸ Insert second date (MM/DD/YYYY): ";
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

void func4 (avl_tree<string> *cpfs, avl_tree<string> *nome, avl_tree<Data> *data){
    string cpf, name, surname, city, str;
    stringstream ss;
    Data date;
    char ch;
    int month, day, year;
    int meses[12] = {31,0, 31,30,31,30,31,31,30,31,30,31};

    cout << "Please, insert the following data: " << endl;
    cout << "\n▸ CPF: ";
    getline(cin, cpf);

    // Verifica se a entrada para CPF é uma entrada válida.
    // A entrada para um cpf deve conter exatamente 14 caracteres e não deve conter letras.
    if (!isNumeric(cpf) || cpf.length() != 11){
        cout << "error: Invalid CPF" << endl;
        return;
    }

    // Faz o tratamento do cpf
    cpf = formatCpf(cpf);

    if (cpfs->search(cpf)){
        cout << "error: cpf already exists" << endl;
        return;
    }
    cout << "▸ First name: ";
    cin >> name;
    cout << "▸ Surname: ";
    cin >> surname;
    cout << "▸ Hometown: ";
    cin.ignore();
    getline(cin, city);

    cout << "▸ Birthday (MM/DD/YYYY): ";
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

    date = Data(month, day, year);
    // Criação objeto pessoa
    Pessoa *pessoa = new Pessoa(cpf, name, surname, date, city);
    cpfs->add(cpf, pessoa);
    nome->add(toUpper(name + " " + surname), pessoa);
    data->add(date, pessoa);
    cout << "+---------------------+\n";
    cout << "| Succesfully added ✓ |\n";
    cout << "+---------------------+\n";
}