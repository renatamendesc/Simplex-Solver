#include "modelo.h"
#include "modelo.cpp"
#include "dual.h"
#include "dual.cpp"
#include "formaPadrao.h"
#include "formaPadrao.cpp"
#include <iostream>
#include <vector>

using namespace std;

void leitura(Modelo &modelo){
    int numeroVariaveis, numeroRestricoes;
    float coeficiente, coeficienteRestricao, segundoMembro;
    vector <float> coeficientes, coeficientesRestricoes;
    string tipo, relacao;

    cout << "\n-------------------------------------RESOLVEDOR SIMPLEX-------------------------------------\n\n";

    cout << "Informe o tipo da função objetivo [Max/Min]: ";
    getline(cin, tipo);

    cout << "Informe a quantidade de variáveis de decisão: ";
    cin >> numeroVariaveis;

    cout << "Informe os coeficientes das variáveis de decisão:\n";

    for(int i = 0; i < numeroVariaveis; i++){

        cout << "\t" << i+1 << ".Coeficiente de x_" << i+1 << ": ";
        cin >> coeficiente;

        coeficientes.push_back(coeficiente);
    }

    modelo.setFuncaoObjetivo(tipo, coeficientes);

    cout << "\nInforme a quantidade de restrições: ";
    cin >> numeroRestricoes;

    for(int i = 0; i < numeroRestricoes; i++){
        cout << "\nInforme a relação da " << i+1 << "ª restrição [Menor ou igual / Igual / Maior ou igual]: ";

        getchar();
        getline(cin, relacao);

        cout << "Informe o termo do lado direito da " << i+1 << "ª restrição: ";
        cin >> segundoMembro;

        for(int j = 0; j < numeroVariaveis; j++){
            cout << "\t" << j+1 << ".Coeficiente de x_" << j+1 << " na " << i+1 <<"ª restrição: ";
            cin >> coeficienteRestricao;

            coeficientesRestricoes.push_back(coeficienteRestricao);
        }

        modelo.setRestricoes(relacao, segundoMembro, coeficientesRestricoes);
        coeficientesRestricoes.clear();
    }

    cout << "\n-------------------------------------------------------------------------------------------\n";

}

int main(void){
    vector <float> solucaoVariaveisBasicas, solucaoVariaveisNaoBasicas;
    vector <int> indicesVariaveisBasicas, indicesVariaveisNaoBasicas;
    bool verificacao = false;

    Modelo modelo;

    // Realiza a leitura do modelo:
    leitura(modelo);

    // Exibe o modelo:
    modelo.printFuncaoObjetivo();
    modelo.printRestricoes();

    // Transforma o modelo para sua forma padrão:
    FormaPadrao modeloPadrao = FormaPadrao(modelo);

    // Exibe o modelo na forma padrão:
    modeloPadrao.printFuncaoObjetivo();
    modeloPadrao.printRestricoes();

    while(!verificacao){
        verificacao = modeloPadrao.verificacaoSolucao();
    }

    modeloPadrao.printTableau();

    cout << "Valor ótimo: " << modeloPadrao.getValorOtimo() << endl;
    modeloPadrao.getSolucaoOtima(solucaoVariaveisBasicas, solucaoVariaveisNaoBasicas, indicesVariaveisBasicas, indicesVariaveisNaoBasicas);

    cout << "Solução ótima: " << endl;
    for(int i = 0; i < solucaoVariaveisBasicas.size(); i++){
        cout << "\tx_" << indicesVariaveisBasicas[i] << ": " << solucaoVariaveisBasicas[i] << endl;
    }

    for(int i = 0; i < solucaoVariaveisNaoBasicas.size(); i++){
        cout << "\tx_" << indicesVariaveisNaoBasicas[i] << ": " << solucaoVariaveisNaoBasicas[i] << endl;
    }

    cout << endl;

    Dual dual = Dual(modelo);
    cout << "Dual: ";
    dual.printFuncaoObjetivo();
    dual.printRestricoes();

    char selecao;
    cout << "Deseja fazer análise de sensibilidade? [S/N] ";
    cin >> selecao;

    if(selecao == 'S'){
        modeloPadrao.analiseSensibilidade();
    }

}