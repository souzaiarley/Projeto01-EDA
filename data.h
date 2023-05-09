#ifndef DATA_H
#define DATA_H
#include <iomanip>

struct Data {
    // atributos
    int mes, dia, ano;
    
    // construtor
    Data(int mes, int dia, int ano)
        : mes(mes), dia(dia), ano(ano)
    {}
    // construtor padrão
    Data(){}

    // sobrecarga de operadores '<' , '==' , '>', '>=' , '<<'
    bool operator<(Data data){
        if (ano < data.ano){return true;}
        else if (ano > data.ano){return false;}

        if (mes < data.mes){return true;}
        else if (mes > data.mes){return false;}

        if (dia < data.dia){return true;}

        return false;
    }

    bool operator==(Data data){
        if (ano == data.ano && mes == data.mes && dia == data.dia){
            return true;
        }
        return  false;
    }

    bool operator>(Data data){
        if (ano > data.ano){return true;}
        else if (ano < data.ano){return false;}

        if (mes > data.mes){return true;}
        else if (mes < data.mes){return false;}

        if (dia > data.dia){return true;}

        return false;
    }

    bool operator>=(Data data){
        return (operator>(data)|| operator==(data));
    }

    bool operator<=(Data data){
        return (operator<(data)|| operator==(data));
    }

    friend std::ostream& operator<<(std::ostream& os, const Data& data){
        os << std::setfill('0') << std::setw(2) << data.mes << "/"
        << std::setw(2) << data.dia << "/" << std::setw(4) << data.ano;
        return os;
    }
};

#endif