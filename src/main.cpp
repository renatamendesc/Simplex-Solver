#include "modelo.h"
#include "modelo.cpp"
#include "formaPadrao.h"
#include "formaPadrao.cpp"
#include <iostream>
#include <vector>

using namespace std;

void leitura(Modelo &modelo){
    int numeroVariaveis, numeroRestricoes;
    double coeficiente, coeficienteRestricao, segundoMembro;
    vector <double> coeficientes, coeficientesRestricoes;
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

    modeloPadrao.setTableau();

    while(!verificacao){
        verificacao = modeloPadrao.verificacaoSolucao();
    }

    modeloPadrao.setVariaveisBasicas();

    cout << "Valor ótimo: " << modeloPadrao.getValorOtimo() << endl;
    vector <double> solucaoOtima = modeloPadrao.getSolucaoOtima();

    /*
    for(int i = 0; i < solucaoOtima.size(); i++){
        cout << solucaoOtima[i] << " " << endl;
        cout << "oi";
    }
    */

    cout << endl;

}