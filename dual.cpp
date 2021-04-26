#include "dual.h"
#include <iostream>

using namespace std;

FuncaoObjetivo Dual::getFuncaoObjetivo(){
    return this->funcaoObjetivo;
}

vector <Restricoes> Dual::getRestricoes(){
    return this->restricoes;
}

void Dual::setFuncaoObjetivo(string tipo, vector <float> coeficientes){
    
    this->funcaoObjetivo.setTipo(tipo);
    this->funcaoObjetivo.setVariaveis(coeficientes);

}

void Dual::setRestricoes(string relacao, float segundoMembro, vector <float> coeficientes){

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

void Dual::printFuncaoObjetivo(){

    cout << "\nFunção Objetivo: " << this->funcaoObjetivo.getTipo() << " Z = ";
    
    for(int i = 0; i < this->funcaoObjetivo.getVariaveis().size(); i++){
        cout << this->funcaoObjetivo.getVariaveis()[i].getCoeficiente() << "x_" << this->funcaoObjetivo.getVariaveis()[i].getIndice();

        if(i < this->funcaoObjetivo.getVariaveis().size()-1){
            cout << " + ";
        }
    }

    cout << endl;
}

void Dual::printRestricoes(){

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