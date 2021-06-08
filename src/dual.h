#ifndef DUAL_H
#define DUAL_H

#include "modelo.h"
#include <iostream>
#include <vector>

class Dual {

    private:
        FuncaoObjetivo funcaoObjetivo;
        std::vector <Restricoes> restricoes;
        std::vector <std::string> restricoesVariaveis;  
    
    public:
        Dual(Modelo);

        void setFuncaoObjetivo(std::string, std::vector <double>);
        void setRestricoes(std::string, double, std::vector <double>);

        FuncaoObjetivo getFuncaoObjetivo();
        std::vector <Restricoes> getRestricoes();

        void printFuncaoObjetivo();
        void printRestricoes();

};

#endif