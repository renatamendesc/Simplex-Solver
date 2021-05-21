#ifndef FORMA_PADRAO_H
#define FORMA_PADRAO_H

#include "modelo.h"
#include "funcaoObjetivo.h"
#include "restricoes.h"
#include "variaveisAdicionadas.h"
#include <iostream>
#include <vector>

using namespace std;

class FormaPadrao {

    public:
        FormaPadrao(Modelo);

        float getValorOtimo();
        int getIteracoes();
        void getSolucaoOtima(vector <float> &, vector <float> &, vector <int> &, vector <int> &);

        void setTableau();
        void setVariaveisBasicas(int, int);

        bool testeOtimalidade();
        void verificaSegundaFase();
        void defineNovaBase(int);
        void atualizaTableau(int, int);
        void analiseSensibilidade();

        bool comparaFloat(float a, float b);

        void printTableau();
        void printFuncaoObjetivo();
        void printRestricoes();

    private:
        FuncaoObjetivo funcaoObjetivo;
        vector <Restricoes> restricoes;

        vector <int> variaveisBasicas;
        vector <int> variaveisNaoBasicas;
        vector <VariaveisAdicionadas> outrasVariaveis; // Vector referente a variaveis de folga/artificias

        vector <vector <float>> tableau;

        bool duasFases = false; // Indica se será realizado o metodo das duas fases para solucionar o problema
        bool segundaFase = false; // Caso seja realizado o método das duas fases, indica se o tableau está na primeira ou segunda fase

        int numeroFolgas = 0;
        int numeroArtificiais = 0;

        int iteracoes = 0;
};

#endif