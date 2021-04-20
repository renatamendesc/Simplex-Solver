#ifndef VARIAVEIS_H
#define VARIAVEIS_H

class Variaveis {

    public:
        void setIndice(int);
        void setCoeficiente(double);

        int getIndice();
        double getCoeficiente();

    private:
        int indice;
        double coeficiente;

};

#endif