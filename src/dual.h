#ifndef DUAL_H
#define DUAL_H

#include "modelo.h"
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

        Dual(Modelo);

    private:
        FuncaoObjetivo funcaoObjetivo;
        vector <Restricoes> restricoes;   

};

#endif