#ifndef VARIAVEIS_ADICIONADAS_H
#define VARIAVEIS_ADICIONADAS_H

#include <iostream>

using namespace std;

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
        string tipo;
        int restricao;
        int indice;
        float coeficiente;

};

#endif