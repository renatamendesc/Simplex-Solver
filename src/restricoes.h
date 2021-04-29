#ifndef RESTRICOES_H
#define RESTRICOES_H

#include "variaveis.h"
#include <iostream>
#include <vector>

using namespace std;

// Classe para as restrições existentes no modelo:
class Restricoes {

    public:
        void setRelacao(string);
        void setVariaveis(vector <float>);
        void setSegundoMembro(float);

        string getRelacao();
        vector <Variaveis> getVariaveis();
        float getSegundoMembro();

        void inverteCoeficiente(int);
    
    private:
        string relacao;
        float segundoMembro;
        vector <Variaveis> variaveis;

};

#endif