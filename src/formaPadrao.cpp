#include "formaPadrao.h"
#include <iostream>
#include <cfloat>
#include <vector>

using namespace std;

FormaPadrao::FormaPadrao(Modelo formaOriginal){
    vector <double> coeficientes;
    Restricoes restricao;

    // Analisa variáveis da função objetivo do modelo original:
    for(int i = 0; i < formaOriginal.getFuncaoObjetivo().getVariaveis().size(); i++){
        coeficientes.push_back(formaOriginal.getFuncaoObjetivo().getVariaveis()[i].getCoeficiente());
    }

    // Analisa restrições do modelo original:
    for(int i = 0; i < formaOriginal.getRestricoes().size(); i++){
        // Conta quantas variáveis de folga serão adicionadas:
        if(formaOriginal.getRestricoes()[i].getRelacao() == "<="){
            coeficientes.push_back(0);
            this->numeroFolgas++;
        }
    }

    // Adiciona variaveis de folga na função objetivo(Forma padrão):
    this->funcaoObjetivo.setVariaveis(coeficientes);
    this->funcaoObjetivo.setTipo(formaOriginal.getFuncaoObjetivo().getTipo());

    coeficientes.clear();

    // Analisa restrições do modelo original:
    for(int i = 0; i < formaOriginal.getRestricoes().size(); i++){

        // Analisa coeficientes das variaveis das restrições:
        for(int j = 0; j < formaOriginal.getRestricoes()[i].getVariaveis().size(); j++){
            coeficientes.push_back(formaOriginal.getRestricoes()[i].getVariaveis()[j].getCoeficiente());
        }

        // Adiciona variáveis de folga:
        for(int j = 0; j < numeroFolgas; j++){
            if((formaOriginal.getRestricoes()[i].getRelacao() == "<=") && (j == i)){
                coeficientes.push_back(1);
            }else {
                coeficientes.push_back(0);
            }
        }

    // Adiciona variaveis de folga na função objetivo(Forma padrão):
    restricao.setVariaveis(coeficientes);
    restricao.setRelacao(formaOriginal.getRestricoes()[i].getRelacao());
    restricao.setSegundoMembro(formaOriginal.getRestricoes()[i].getSegundoMembro());

    this->restricoes.push_back(restricao);
    coeficientes.clear();

    }
}

void FormaPadrao::setTableau(){
    vector <double> linha;

    // Adiciona primeira linha (Referente a função objetivo):
    for(int i = 0; i <= this->funcaoObjetivo.getVariaveis().size(); i++){
        if(i == this->funcaoObjetivo.getVariaveis().size()){
            linha.push_back(0);

        }else if(funcaoObjetivo.getVariaveis()[i].getCoeficiente() != 0){
            linha.push_back(-(funcaoObjetivo.getVariaveis()[i].getCoeficiente()));

        }else {
            linha.push_back(funcaoObjetivo.getVariaveis()[i].getCoeficiente()); 

        }
    }

    // Adiciona linha ao tableau:
    this->tableau.push_back(linha);
    linha.clear();

    // Adiciona linhas referentes as restrições:
    for(int i = 0; i < this->restricoes.size(); i++){
        for(int j = 0; j <= this->restricoes[i].getVariaveis().size(); j++){
            if(j == this->restricoes[i].getVariaveis().size()){
                linha.push_back(this->restricoes[i].getSegundoMembro());
            } else {
                linha.push_back(this->restricoes[i].getVariaveis()[j].getCoeficiente());
            }
        }

        // Adiciona linha ao tableau:
        this->tableau.push_back(linha);
        linha.clear();
    }
}

void FormaPadrao::setVariaveisBasicas(){
    bool basica = true;

    // Analisa quais são variaveis básicas e não básicas:
    for(int j = 0; j < this->restricoes.size(); j++){
        for(int i = 0; i < this->tableau.size(); i++){

            if(this->tableau[i][j] != 0 || this->tableau[i][j] != 1){
                basica = false;
            }

            if(basica){
                this->variaveisBasicas.push_back(j+1);
            }else{
                this->variaveisNaoBasicas.push_back(j+1);
            }
        }
    }
}

bool FormaPadrao::verificacaoSolucao(){

    while(true){
        //this->printTableau();

        double menor = DBL_MAX;
        int colunaPivo;

        // Verifica qual o menor elemento:
        for(int i = 0; i < tableau[0].size(); i++){
            if(tableau[0][i] < menor){
                menor = tableau[0][i];
                colunaPivo = i;
            }
        }

        // Verifica se o menor elemento é negativo:
        if(menor < 0){
            this->defineNovaBase(colunaPivo);
            continue;
        } else {
            return true;
        }
    }
}

void FormaPadrao::defineNovaBase(int colunaPivo){
    double menor = DBL_MAX, resultado = DBL_MAX;
    int linhaPivo;

    // Verifica a linha pivô:
    for(int i = 1; i < this->tableau.size(); i++){
        if(this->tableau[i][colunaPivo] != 0){
            resultado = this->tableau[i][tableau[i].size()-1] / this->tableau[i][colunaPivo];
        }

        if(resultado < menor){
            menor = resultado;
            linhaPivo = i;
        }
    }

    atualizaTableau(colunaPivo, linhaPivo);
}

void FormaPadrao::atualizaTableau(int colunaPivo, int linhaPivo){
    int elementoPivo = this->tableau[linhaPivo][colunaPivo];

    // Atualiza nova linha pivô:
    for(int i = 0; i < this->tableau[linhaPivo].size(); i++){
        this->tableau[linhaPivo][i] = this->tableau[linhaPivo][i] / elementoPivo;
    }

    // Atualiza as demais linhas:
    for(int i = 0; i < this->tableau.size(); i++){
        if(i != linhaPivo){
            double multiplicador = -(this->tableau[i][colunaPivo]);

            for(int j = 0; j < this->tableau[i].size(); j++){
                this->tableau[i][j] = (multiplicador * (this->tableau[linhaPivo][j])) + this->tableau[i][j];
            }
        }
    }
}

void FormaPadrao::printTableau(){

    // Exibe tableau:
    for(int i = 0; i < this->tableau.size(); i++){
        for(int j = 0; j < this->tableau[i].size(); j++){
            cout << tableau[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
}

void FormaPadrao::printFuncaoObjetivo(){

    // Exibe função objetivo:
    cout << "\nFunção Objetivo: " << funcaoObjetivo.getTipo() << " Z = ";
    
    for(int i = 0; i < this->funcaoObjetivo.getVariaveis().size(); i++){
        cout << this->funcaoObjetivo.getVariaveis()[i].getCoeficiente() << "x_" << funcaoObjetivo.getVariaveis()[i].getIndice();

        if(i < this->funcaoObjetivo.getVariaveis().size()-1){
            cout << " + ";
        }
    }

    cout << endl;
}

void FormaPadrao::printRestricoes(){

    cout << "\nSujeito a:\n";

    // Analisa restrições:
    for(int i = 0; i < this->restricoes.size(); i++){
        cout << "\t";

        // Analisa variáveis das restrições:
        for(int j = 0; j < this->restricoes[i].getVariaveis().size(); j++){
            cout << this->restricoes[i].getVariaveis()[j].getCoeficiente() << "x_" << this->restricoes[i].getVariaveis()[j].getIndice();

            if(j < this->restricoes[i].getVariaveis().size()-1){
                cout << " + ";
            }
        }

        cout << " " << this->restricoes[i].getRelacao() << " " << this->restricoes[i].getSegundoMembro() << endl;   
    }

    cout << endl;
}

double FormaPadrao::getValorOtimo(){

    return this->tableau[0][tableau[0].size()-1];
}

vector <double> FormaPadrao::getSolucaoOtima(){
    vector <double> solucao;

    for(int i = 0; i < this->funcaoObjetivo.getVariaveis().size(); i++){
        for(int j = 0; j < variaveisNaoBasicas.size(); j++){
            cout << "oi1" << endl;
            if(this->funcaoObjetivo.getVariaveis()[i].getIndice() == variaveisNaoBasicas[j]){
                solucao.insert(solucao.begin()+(this->funcaoObjetivo.getVariaveis()[i].getIndice()-1), 0);
            }
        }
    }

    for(int i = 0; i < this->funcaoObjetivo.getVariaveis().size(); i++){
        for(int j = 0; j < variaveisBasicas.size(); j++){
            cout << "oi2" << endl;
            if(this->funcaoObjetivo.getVariaveis()[i].getIndice() == variaveisBasicas[j]){
                solucao.insert(solucao.begin()+(this->funcaoObjetivo.getVariaveis()[i].getIndice()-1), this->tableau[j][tableau[j].size()-1]);
            }
        }
    }

   return solucao;
}
