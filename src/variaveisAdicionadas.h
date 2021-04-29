#ifndef VARIAVEIS_ADICIONADAS_H
#define VARIAVEIS_ADICIONADAS_H

#include <iostream>

using namespace std;

// Classe referente às variáveis que forem adicionadas na forma padrão (artificiais/folga)
class VariaveisAdicionadas {

    public:
        void setIndice(int);
        void setCoeficiente(float);
        void setTipo(string);
        void setRestricao(int);
        
        int getIndice();
        float getCoeficiente();
        string getTipo();
        int getRestricao();

    private:
        string tipo; // Indica se a variável é folga ou artificial
        int restricao; // Indica para qual restrição essa variável será adicionada
        int indice;
        float coeficiente;

};

#endif