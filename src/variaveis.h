#ifndef VARIAVEIS_H
#define VARIAVEIS_H

#include <iostream>

// Classe refente às variaveis existentes
class Variaveis {

    private:
        int indice;
        double coeficiente;

    public:
        void setIndice(int);
        void setCoeficiente(double);
        
        int getIndice();
        double getCoeficiente();

};

#endif