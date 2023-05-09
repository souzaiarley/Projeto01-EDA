#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "avl.h"

using namespace std;

string formatCpf(string cpf){
    if (cpf.size() >= 9){
        cpf.erase(std::remove(cpf.begin(), cpf.end(), '.'), cpf.end());
        cpf.erase(std::remove(cpf.begin(), cpf.end(), '-'), cpf.end());
        
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

void func1 (avl_tree<string> *tree){
    string cpf;

    cout << "Insert CPF: ";
    getline(cin, cpf);    
    cpf = formatCpf(cpf);
    if (isAlphanumeric(cpf) || cpf.length() < 14 || cpf.length() > 14){
        cout << cpf;
        cout << "error: Invalid CPF" << endl;
        return;
    }
    
    system("clear || cls");
    tree->cpfData(cpf);
}

void func2 (avl_tree<string> *tree){
    string str;

    cout << "Search for: ";
    getline(cin, str);

    system("clear || cls");
    tree->prefixo(str, toUpper(str));

}

void func3 (avl_tree<Data> *tree){
    Data date1, date2;
    int month, day, year;
    string str;
    stringstream ss;
    char ch;

    cout << "Insert first date (MM/DD/YYYY): ";
    getline(cin, str);
    ss << str;

    ss >> month >> ch >> day >> ch >> year;

    date1 = Data(month, day, year);

    str.clear();
    ss.clear();

    cout << "\nInsert second date (MM/DD/YYYY): ";
    getline(cin, str);
    ss << str;

    ss >> month >> ch >> day >> ch >> year;

    date2 = Data(month, day, year);
    system("clear || cls");
    tree->inRange(date1, date2);
}