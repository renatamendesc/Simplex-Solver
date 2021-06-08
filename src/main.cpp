#include "modelo.h"
#include "dual.h"
#include "formaPadrao.h"
#include <iostream>
#include <vector>

using namespace std;

void inicializacao(Modelo &modelo){

    // Inicializa função objetivo do modelo
    modelo.setFuncaoObjetivo("Min", {0.4, 0.5});

    // Inicializa restricoes do modelo
    modelo.setRestricoes("Menor ou igual", 2.7, {0.3, 0.1});
    modelo.setRestricoes("Igual", 6, {0.5, 0.5});
    modelo.setRestricoes("Maior ou igual", 6, {0.6, 0.4});
    
}

int main(void){
    vector <double> solucaoVariaveisBasicas, solucaoVariaveisNaoBasicas;
    vector <int> indicesVariaveisBasicas, indicesVariaveisNaoBasicas;
    bool verificacao = false;

    // Realiza a leitura do modelo:
    Modelo modelo;
    inicializacao(modelo);

    cout << "\n------------------------------------ RESOLVEDOR SIMPLEX ------------------------------------\n";

    // Exibe o modelo:
    modelo.printFuncaoObjetivo();
    modelo.printRestricoes();

    cout << "\n-------------------------------------------------------------------------------------------\n";

    // Transforma o modelo para sua forma padrão:
    FormaPadrao modeloPadrao = FormaPadrao(modelo);

    cout << "FORMA PADRÃO: ";

    // Exibe o modelo na forma padrão:
    modeloPadrao.printFuncaoObjetivo();
    modeloPadrao.printRestricoes();

    while(!verificacao){
        verificacao = modeloPadrao.testeOtimalidade();
    }

    cout << "\n-------------------------------------------------------------------------------------------\n";

    cout << "RESULTADO: " << endl;

    cout << "Número de iterações: " << modeloPadrao.getIteracoes() << endl;

    cout << "\nValor ótimo: " << modeloPadrao.getValorOtimo() << endl;
    modeloPadrao.getSolucaoOtima(solucaoVariaveisBasicas, solucaoVariaveisNaoBasicas, indicesVariaveisBasicas, indicesVariaveisNaoBasicas);

    cout << "Solução ótima: " << endl;
    for(int i = 0; i < solucaoVariaveisBasicas.size(); i++){
        cout << "\tx_" << indicesVariaveisBasicas[i] << ": " << solucaoVariaveisBasicas[i] << endl;
    }

    for(int i = 0; i < solucaoVariaveisNaoBasicas.size(); i++){
        cout << "\tx_" << indicesVariaveisNaoBasicas[i] << ": " << solucaoVariaveisNaoBasicas[i] << endl;
    }

    cout << "\n-------------------------------------------------------------------------------------------\n";

    Dual dual = Dual(modelo);

    cout << "MODELO DUAL: ";
    dual.printFuncaoObjetivo();
    dual.printRestricoes();

    cout << "\n-------------------------------------------------------------------------------------------\n";

    char selecao;
    cout << "Deseja fazer análise de sensibilidade? [S/N] " << endl;
    cin >> selecao;

    cout << "\n-------------------------------------------------------------------------------------------\n";

    if(selecao == 'S'){
        cout << "ANÁLISE DE SENSIBILIDADE: " << endl;;
        cout << "1) Tableau final do modelo original: " << endl;
        modeloPadrao.printTableau();

        cout << "2) Mudanças permitidas nos valores da mão direita:" << endl;;
        modeloPadrao.analiseSensibilidade();

         cout << "\n-------------------------------------------------------------------------------------------\n";
    }
}