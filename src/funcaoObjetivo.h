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
        void setVariaveis(vector <float>);
        void setSegundoMembro(float);

        string getTipo();
        vector <Variaveis> getVariaveis();
        float getSegundoMembro();


    private:
        string tipo;
        float segundoMembro = 0;
        vector <Variaveis> variaveis; 
        

};

#endif