#ifndef VARIAVEIS_ADICIONADAS_H
#define VARIAVEIS_ADICIONADAS_H

#include <iostream>

// Classe referente às variáveis que forem adicionadas na forma padrão (artificiais/folga)
class VariaveisAdicionadas {

    private:
        std::string tipo; // Indica se a variável é folga ou artificial
        int restricao; // Indica para qual restrição essa variável será adicionada
        int indice;
        double coeficiente;

    public:
        void setIndice(int);
        void setCoeficiente(double);
        void setRestricao(int);
        void setTipo(std::string);
        
        int getIndice();
        double getCoeficiente();
        int getRestricao();
        std::string getTipo();

};

#endif