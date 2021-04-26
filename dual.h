#ifndef DUAL_H
#define DUAL_H

#include "funcaoObjetivo.h"
#include "funcaoObjetivo.cpp"
#include "restricoes.h"
#include "restricoes.cpp"
#include <iostream>
#include <vector>

using namespace std;

class Dual {
    
    public:
        void setFuncaoObjetivo(string, vector <float>);
        void setRestricoes(string, float, vector <float>);

        FuncaoObjetivo getFuncaoObjetivo();
        vector <Restricoes> getRestricoes();

        void printFuncaoObjetivo();
        void printRestricoes();

        Dual();

    private:
        FuncaoObjetivo funcaoObjetivo;
        vector <Restricoes> restricoes;   

};

#endif