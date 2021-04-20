#ifndef RESTRICOES_H
#define RESTRICOES_H

#include "variaveis.h"
#include <iostream>
#include <vector>

using namespace std;

class Restricoes {

    public:
        void setRelacao(string);
        void setVariaveis(vector <double>);
        void setSegundoMembro(double);

        string getRelacao();
        vector <Variaveis> getVariaveis();
        double getSegundoMembro();
    
    private:
        string relacao;
        double segundoMembro;
        vector <Variaveis> variaveis;

};

#endif