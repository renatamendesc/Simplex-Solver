#ifndef FORMA_PADRAO_H
#define FORMA_PADRAO_H

#include "modelo.h"
#include "variaveisAdicionadas.h"
#include <iostream>
#include <vector>

class FormaPadrao {

    private:
        FuncaoObjetivo funcaoObjetivo;
        std::vector <Restricoes> restricoes;

        std::vector <int> variaveisBasicas;
        std::vector <int> variaveisNaoBasicas;
        std::vector <VariaveisAdicionadas> outrasVariaveis; // Vector referente a variaveis de folga/artificias

        std::vector <std::vector <double>> tableau;
        std::vector <int> colunasMatrizIdentidade;

        bool bigM = false;

        int numeroFolgas = 0;
        int numeroArtificiais = 0;

        int iter = 0;

    public:
        FormaPadrao(Modelo);

        double getValorOtimo();
        int getIteracoes();
        void getSolucaoOtima(std::vector <double> &, std::vector <double> &, std::vector <int> &, std::vector <int> &);

        void setTableau();
        void setVariaveisBasicas(int, int);

        bool testeOtimalidade();
        void defineNovaBase(int);
        void atualizaTableau(int, int);
        void analiseSensibilidade();

        bool comparaDouble(double a, double b);

        void printTableau();
        void printFuncaoObjetivo();
        void printRestricoes();

};

#endif