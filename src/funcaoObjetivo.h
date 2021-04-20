#ifndef FUNCAO_OBJETIVO_H
#define FUNCAO_OBJETIVO_H

#include "variaveis.h"
#include "variaveis.cpp"
#include <iostream>
#include <vector>

using namespace std;

class FuncaoObjetivo {

    public:
        void setTipo(string);
        void setVariaveis(vector <double>);
        void setSegundoMembro(double);

        string getTipo();
        vector <Variaveis> getVariaveis();
        double getSegundoMembro();


    private:
        string tipo;
        double segundoMembro = 0;
        vector <Variaveis> variaveis; 
        

};

#endif