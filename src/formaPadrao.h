#ifndef FORMA_PADRAO_H
#define FORMA_PADRAO_H

#include "funcaoObjetivo.h"
#include "restricoes.h"
#include "modelo.h"
#include <iostream>
#include <vector>

class FormaPadrao {

    public:
        double getValorOtimo();
        vector <double> getSolucaoOtima();

        void setTableau();
        void setVariaveisBasicas();

        void printTableau();
        void printFuncaoObjetivo();
        void printRestricoes();

        bool verificacaoSolucao();

        void defineNovaBase(int);
        void atualizaTableau(int, int);

        FormaPadrao(Modelo);

    private:
        FuncaoObjetivo funcaoObjetivo;
        vector <Restricoes> restricoes;

        vector <int> variaveisBasicas;
        vector <int> variaveisNaoBasicas;

        vector <vector<double>> tableau;

        int numeroFolgas = 0;
};

#endif