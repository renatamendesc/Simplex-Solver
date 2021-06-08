#ifndef RESTRICOES_H
#define RESTRICOES_H

#include "variaveis.h"
#include <iostream>
#include <vector>

// Classe para as restrições existentes no modelo:
class Restricoes {

    private:
        std::vector <Variaveis> variaveis;
        std::string relacao;
        double segundoMembro;

    public:
        void setVariaveis(std::vector <double>);
        void setRelacao(std::string);
        void setSegundoMembro(double);

        std::vector <Variaveis> getVariaveis();
        std::string getRelacao();
        double getSegundoMembro();

        void inverteCoeficiente(int);

};

#endif