#ifndef VARIAVEIS_H
#define VARIAVEIS_H

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