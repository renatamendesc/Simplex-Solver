#include "modelo.h"
#include <iostream>

using namespace std;

FuncaoObjetivo Modelo::getFuncaoObjetivo(){
    return this->funcaoObjetivo;
}

vector <Restricoes> Modelo::getRestricoes(){
    return this->restricoes;
}

void Modelo::setFuncaoObjetivo(string tipo, vector <float> coeficientes){
    
    this->funcaoObjetivo.setTipo(tipo);
    this->funcaoObjetivo.setVariaveis(coeficientes);

}

void Modelo::setRestricoes(string relacao, float segundoMembro, vector <float> coeficientes){

    Restricoes restricao;

    restricao.setVariaveis(coeficientes);
    restricao.setSegundoMembro(segundoMembro);

    if(relacao == "Menor ou igual"){
        restricao.setRelacao("<=");
    }else if(relacao == "Maior ou igual"){
        restricao.setRelacao(">=");
    }else if(relacao == "Igual"){
        restricao.setRelacao("=");
    }

    this->restricoes.push_back(restricao);
}

void Modelo::verificaNegatividade(){

    for(int i = 0; i < restricoes.size(); i++){

        // Multiplica restrição que o lado direito for negativo:
        if(restricoes[i].getSegundoMembro() < 0){

            // Percorre variáveis da restrição:
            for(int j = 0; j < restricoes[i].getVariaveis().size(); j++){
                
                restricoes[i].inverteCoeficiente(j);
                
            }

            restricoes[i].setRelacao("<=");
            restricoes[i].setSegundoMembro(-(restricoes[i].getSegundoMembro()));
        
        }
    }
}

void Modelo::printFuncaoObjetivo(){

    cout << "\nFunção Objetivo: " << this->funcaoObjetivo.getTipo() << " Z = ";
    
    for(int i = 0; i < this->funcaoObjetivo.getVariaveis().size(); i++){
        cout << this->funcaoObjetivo.getVariaveis()[i].getCoeficiente() << "x_" << this->funcaoObjetivo.getVariaveis()[i].getIndice();

        if(i < this->funcaoObjetivo.getVariaveis().size()-1){
            cout << " + ";
        }
    }

    cout << endl;
}

void Modelo::printRestricoes(){

    cout << "\nSujeito a:\n";

    for(int i = 0; i < this->restricoes.size(); i++){

        cout << "\t";

        for(int j = 0; j < this->restricoes[i].getVariaveis().size(); j++){

            if(this->restricoes[i].getVariaveis()[j].getCoeficiente() != 0){
                cout << this->restricoes[i].getVariaveis()[j].getCoeficiente() << "x_" << this->restricoes[i].getVariaveis()[j].getIndice();

                if(j < this->restricoes[i].getVariaveis().size()-1 && this->restricoes[i].getVariaveis()[j+1].getCoeficiente() != 0){
                    cout << " + ";
                }
            }
        }

        cout << " " << this->restricoes[i].getRelacao() << " " << this->restricoes[i].getSegundoMembro() << endl;
        
    }

    cout << endl;
}