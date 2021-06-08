#ifndef FUNCAO_OBJETIVO_H
#define FUNCAO_OBJETIVO_H

#include "variaveis.h"
#include <iostream>
#include <vector>

// Classe referente à função objetivo do modelo
class FuncaoObjetivo {

    private:
        std::string tipo; // Indica se a função é de minimização ou maximização
        std::vector <Variaveis> variaveis; // Vector com as variaveis da função
        double segundoMembro = 0; //Inicializa lado direito da função como zero   

    public:
        void setTipo(std::string);
        void setVariaveis(std::vector <double>);
        void setSegundoMembro(double);

        std::string getTipo();
        std::vector <Variaveis> getVariaveis();
        double getSegundoMembro(); 

};

#endif