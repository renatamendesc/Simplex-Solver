#ifndef RESTRICOES_H
#define RESTRICOES_H

#include "variaveis.h"
#include <iostream>
#include <vector>

using namespace std;

class Restricoes {

    public:
        void setRelacao(string);
        void setVariaveis(vector <float>);
        void setVariaveisFolgas(int, int, int);
        void setVariaveisArtificiais(int, int, int);
        void setSegundoMembro(float);

        void inverteCoeficiente(int);

        string getRelacao();
        vector <Variaveis> getVariaveis();
        Variaveis getVariaveisFolgas();
        Variaveis getVariaveisArtificiais();
        float getSegundoMembro();
    
    private:
        string relacao;
        float segundoMembro;
        vector <Variaveis> variaveis;
        Variaveis variaveisFolgas;
        Variaveis variaveisArtificiais;

};

#endif