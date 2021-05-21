#ifndef MODELO_H
#define MODELO_H

#include "funcaoObjetivo.h"
#include "restricoes.h"
#include <iostream>
#include <vector>

using namespace std;

// Classe referente ao modelo em questão (na sua forma original)
class Modelo {
    
    public:
        void setFuncaoObjetivo(string, vector <float>);
        void setRestricoes(string, float, vector <float>);

        FuncaoObjetivo getFuncaoObjetivo();
        vector <Restricoes> getRestricoes();

        void verificaNegatividade();

        void printFuncaoObjetivo();
        void printRestricoes();

    private:
        FuncaoObjetivo funcaoObjetivo;
        vector <Restricoes> restricoes;

};

#endif