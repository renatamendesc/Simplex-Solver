#ifndef MODELO_H
#define MODELO_H

#include "funcaoObjetivo.h"
#include "restricoes.h"
#include <iostream>
#include <vector>

// Classe referente ao modelo em questão (na sua forma original)
class Modelo {

    private:
        FuncaoObjetivo funcaoObjetivo;
        std::vector <Restricoes> restricoes;
    
    public:
        void setFuncaoObjetivo(std::string, std::vector <double>);
        void setRestricoes(std::string, double, std::vector <double>);

        FuncaoObjetivo getFuncaoObjetivo();
        std::vector <Restricoes> getRestricoes();

        void verificaNegatividade();

        void printFuncaoObjetivo();
        void printRestricoes();

};

#endif