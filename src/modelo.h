#ifndef MODELO_H
#define MODELO_H

#include "funcaoObjetivo.h"
#include "funcaoObjetivo.cpp"
#include "restricoes.h"
#include "restricoes.cpp"
#include <iostream>
#include <vector>

using namespace std;

class Modelo {
    
    public:
        void setFuncaoObjetivo(string, vector <float>);
        void setRestricoes(string, float, vector <float>);

        void verificaNegatividade();

        FuncaoObjetivo getFuncaoObjetivo();
        vector <Restricoes> getRestricoes();

        void printFuncaoObjetivo();
        void printRestricoes();

    private:
        FuncaoObjetivo funcaoObjetivo;
        vector <Restricoes> restricoes;   

};

#endif