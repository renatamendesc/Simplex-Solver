#ifndef VARIAVEIS_H
#define VARIAVEIS_H

#include <iostream>

using namespace std;

// Classe refente às variaveis existentes
class Variaveis {

    public:
        void setIndice(int);
        void setCoeficiente(float);
        
        int getIndice();
        float getCoeficiente();

    private:
        int indice;
        float coeficiente;

};

#endif