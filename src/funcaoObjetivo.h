#ifndef FUNCAO_OBJETIVO_H
#define FUNCAO_OBJETIVO_H

#include "variaveis.h"
#include "variaveis.cpp"
#include <iostream>
#include <vector>

using namespace std;

// Classe referente à função objetivo do modelo
class FuncaoObjetivo {

    public:
        void setTipo(string);
        void setVariaveis(vector <float>);
        void setSegundoMembro(float);

        string getTipo();
        vector <Variaveis> getVariaveis();
        float getSegundoMembro();

    private:
        string tipo; // Indica se a função é de minimização ou maximização
        vector <Variaveis> variaveis; // Vector com as variaveis da função
        float segundoMembro = 0; //Inicializa lado direito da função como zerp    

};

#endif