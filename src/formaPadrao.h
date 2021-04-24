#ifndef FORMA_PADRAO_H
#define FORMA_PADRAO_H

#include "funcaoObjetivo.h"
#include "variaveisAdicionadas.h"
#include "variaveisAdicionadas.cpp"
#include "restricoes.h"
#include "modelo.h"
#include <iostream>
#include <vector>

class FormaPadrao {

    public:
        double getValorOtimo();
        void getSolucaoOtima(vector <double> &, vector <double> &, vector <int> &, vector <int> &);

        void setTableau();
        void setVariaveisBasicas(int, int);

        void printTableau();
        void printFuncaoObjetivo();
        void printRestricoes();

        bool verificacaoSolucao();
        void verificaSegundaFase();

        void defineNovaBase(int);
        void atualizaTableau(int, int);

        bool comparaDouble(double a, double b);

        FormaPadrao(Modelo);

    private:
        FuncaoObjetivo funcaoObjetivo;
        vector <Restricoes> restricoes;

        vector <int> variaveisBasicas;
        vector <int> variaveisNaoBasicas;
        vector <VariaveisAdicionadas> outrasVariaveis;

        vector <vector<double>> tableau;

        bool duasFases = false;
        bool segundaFase = false;

        int numeroFolgas = 0;
        int numeroArtificiais = 0;
};

#endif