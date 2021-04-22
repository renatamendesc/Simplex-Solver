#include "formaPadrao.h"
#include <iostream>
#include <cfloat>
#include <cmath>
#include <vector>

using namespace std;

FormaPadrao::FormaPadrao(Modelo formaOriginal){
    vector <double> coeficientes;
    vector <VariaveisAdicionadas> outrasVariaveis;
    VariaveisAdicionadas novaVariavel;
    Restricoes restricao;

    // Verifica se há alguma restrição com segundo membro negativo:
    formaOriginal.verificaNegatividade();
    
    // Analisa restrições:
    for(int i = 0; i < formaOriginal.getRestricoes().size(); i++){
        int somador = 0;

        if(formaOriginal.getRestricoes()[i].getRelacao() == "<="){
            novaVariavel.setIndice(i + formaOriginal.getFuncaoObjetivo().getVariaveis().size() + somador + 1);
            novaVariavel.setCoeficiente(1);
            novaVariavel.setTipo("Folga");
            novaVariavel.setRestricao(i+1);

            this->numeroFolgas++;

            outrasVariaveis.push_back(novaVariavel);

        }else if(formaOriginal.getRestricoes()[i].getRelacao() == "="){
            novaVariavel.setIndice(i + formaOriginal.getFuncaoObjetivo().getVariaveis().size() + somador + 1);
            novaVariavel.setCoeficiente(1);
            novaVariavel.setTipo("Artificial");
            novaVariavel.setRestricao(i+1);

            this->numeroArtificiais++;

            outrasVariaveis.push_back(novaVariavel);

        }else if(formaOriginal.getRestricoes()[i].getRelacao() == ">="){
            novaVariavel.setIndice(i + formaOriginal.getFuncaoObjetivo().getVariaveis().size() + somador + 1);
            novaVariavel.setCoeficiente(-1);
            novaVariavel.setTipo("Folga");
            novaVariavel.setRestricao(i+1);

            this->numeroFolgas++;

            outrasVariaveis.push_back(novaVariavel);

            somador++;
            novaVariavel.setIndice(i + formaOriginal.getFuncaoObjetivo().getVariaveis().size() + somador + 1);
            novaVariavel.setCoeficiente(-1);
            novaVariavel.setTipo("Artificial");
            novaVariavel.setRestricao(i+1);

            this->numeroArtificiais++;

            outrasVariaveis.push_back(novaVariavel);
        }
    }

    for(int i = 0; formaOriginal.getFuncaoObjetivo().getVariaveis().size() + numeroArtificiais + numeroFolgas; i++){
        if(i < formaOriginal.getFuncaoObjetivo().getVariaveis().size()){
            coeficientes.push_back(formaOriginal.getFuncaoObjetivo().getVariaveis()[i].getCoeficiente());
            this->variaveisNaoBasicas.push_back(i+1);

        }else {
            coeficientes.push_back(formaOriginal.getFuncaoObjetivo().getVariaveis()[i].getCoeficiente());
        }
    }

    this->funcaoObjetivo.setTipo(formaOriginal.getFuncaoObjetivo().getTipo());
    this->funcaoObjetivo.setSegundoMembro(formaOriginal.getFuncaoObjetivo().getSegundoMembro());
    this->funcaoObjetivo.setVariaveis(coeficientes);

    coeficientes.clear();

    if(this->numeroArtificiais == 0){
        for(int i = 0; i < this->numeroFolgas; i++){
            this->variaveisBasicas.push_back(outrasVariaveis[i].getIndice());
        }

    } else {
        for(int i = 0; i < outrasVariaveis.size(); i++){
            if(outrasVariaveis[i].getTipo() == "Folga"){
               this->variaveisNaoBasicas.push_back(outrasVariaveis[i].getIndice()); 
            }else if(outrasVariaveis[i].getTipo() == "Artificial"){
                this->variaveisBasicas.push_back(outrasVariaveis[i].getIndice()); 
            }
        }
    }

    for(int i = 0; i < formaOriginal.getRestricoes().size(); i++){

        for(int j = 0; j < formaOriginal.getRestricoes()[i].getVariaveis().size(); j++){
            coeficientes.push_back(formaOriginal.getRestricoes()[i].getVariaveis()[j].getCoeficiente());
        }

        for(int j = 0; j < outrasVariaveis.size(); j++){
            if(i == outrasVariaveis[j].getRestricao()){
                coeficientes.push_back(outrasVariaveis[j].getIndice());
            }else{
                coeficientes.push_back(0);
            }
        }

        restricao.setRelacao(formaOriginal.getRestricoes()[i].getRelacao());
        restricao.setSegundoMembro(formaOriginal.getRestricoes()[i].getSegundoMembro());
        restricao.setVariaveis(coeficientes);

        this->restricoes.push_back(restricao);

        coeficientes.clear();
    }
    
    this->setTableau();
}

void FormaPadrao::setTableau(){
    vector <double> linha;

    // Adiciona primeira linha (Referente a função objetivo):
    for(int i = 0; i <= this->funcaoObjetivo.getVariaveis().size(); i++){
        if(i == this->funcaoObjetivo.getVariaveis().size()){
            linha.push_back(0);

        }else if(funcaoObjetivo.getTipo() == "Max" && funcaoObjetivo.getVariaveis()[i].getCoeficiente() != 0){
            linha.push_back(-(funcaoObjetivo.getVariaveis()[i].getCoeficiente()));

        }else if(funcaoObjetivo.getTipo() == "Min" || funcaoObjetivo.getVariaveis()[i].getCoeficiente() == 0){
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

void FormaPadrao::setVariaveisBasicas(int colunaPivo, int linhaPivo){
    int entraBase, saiBase, indiceSai;

    // Determina variavel que entra na base:
    for(int i = 0; i < this->funcaoObjetivo.getVariaveis().size(); i++){
        if(colunaPivo + 1 == this->funcaoObjetivo.getVariaveis()[i].getIndice()){
            entraBase = colunaPivo + 1;
        }
    }

    //cout << "Entra: " << entraBase << endl;

    // Determina variavel que sai na base:
    for(int i = 0; i < this->funcaoObjetivo.getVariaveis().size(); i++){
        if(this->variaveisBasicas[linhaPivo-1] == this->funcaoObjetivo.getVariaveis()[i].getIndice()){
            saiBase = this->variaveisBasicas[linhaPivo-1] ;
        }
    }

    for(int i = 0; i < this->variaveisNaoBasicas.size(); i++){
        if(this->variaveisNaoBasicas[i] == entraBase){
            indiceSai = i;
        }
    }

    //cout << "Sai: " << saiBase << endl;

    this->variaveisBasicas[linhaPivo-1] = entraBase;
    this->variaveisNaoBasicas.push_back(saiBase);

    this->variaveisNaoBasicas.erase(variaveisNaoBasicas.begin() + indiceSai);

    /*
    for(int i = 0; i < this->variaveisBasicas.size(); i++){
        cout << "variavel básica: x_" << this->variaveisBasicas[i] << endl;
    }

    for(int i = 0; i < this->variaveisNaoBasicas.size(); i++){
        cout << "variavel não básica: x_" << this->variaveisNaoBasicas[i] << endl;
    }
    */

}

bool FormaPadrao::verificacaoSolucao(){
    int contador = 0;

    while(true){
        contador++;

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

        if(menor == DBL_MAX){
            menor = resultado;
            linhaPivo = i;
        } else if(resultado < menor && resultado > 0){
            menor = resultado;
            linhaPivo = i;
        }
    }

    this->atualizaTableau(colunaPivo, linhaPivo);
    this->setVariaveisBasicas(colunaPivo, linhaPivo);
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

        cout << " = " << this->restricoes[i].getSegundoMembro() << endl;   
    }

    cout << endl;
}

double FormaPadrao::getValorOtimo(){

    if(funcaoObjetivo.getTipo() == "Max"){
        return this->tableau[0][tableau[0].size()-1];
    }else if(funcaoObjetivo.getTipo() == "Min"){
        return -(this->tableau[0][tableau[0].size()-1]);
    }
    
}

void FormaPadrao::getSolucaoOtima(vector <double> &solucaoVariaveisBasicas, vector <double> &solucaoVariaveisNaoBasicas, vector <int> &indicesVariaveisBasicas, vector <int> &indicesVariaveisNaoBasicas){

    for(int i = 0; i < this->variaveisNaoBasicas.size(); i++){
        for(int j = 0; j < this->funcaoObjetivo.getVariaveis().size(); j++){
            if(this->variaveisNaoBasicas[i] == this->funcaoObjetivo.getVariaveis()[j].getIndice()){
                solucaoVariaveisNaoBasicas.push_back(0);
                indicesVariaveisNaoBasicas.push_back(this->variaveisNaoBasicas[i]);
            }
        }
    }

    for(int i = 0; i < this->variaveisBasicas.size(); i++){
        for(int j = 0; j < this->funcaoObjetivo.getVariaveis().size(); j++){
            if(this->variaveisBasicas[i] == this->funcaoObjetivo.getVariaveis()[j].getIndice()){
                solucaoVariaveisBasicas.push_back(this->tableau[i+1][tableau[i+1].size()-1]);
                indicesVariaveisBasicas.push_back(this->variaveisBasicas[i]);
            }
        }
    }
}
