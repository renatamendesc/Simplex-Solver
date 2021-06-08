#include "modelo.h"

using namespace std;

FuncaoObjetivo Modelo::getFuncaoObjetivo(){
    return this->funcaoObjetivo;
}

vector <Restricoes> Modelo::getRestricoes(){
    return this->restricoes;
}

void Modelo::setFuncaoObjetivo(string tipo, vector <double> coeficientes){
    
    this->funcaoObjetivo.setTipo(tipo); // Estabelece o tipo da função como minimização ou maximização
    this->funcaoObjetivo.setVariaveis(coeficientes); // Estabelece as variáveis existentes na função objetivo

}

void Modelo::setRestricoes(string relacao, double segundoMembro, vector <double> coeficientes){

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

    // Percorre as restrições do modelo e verifica se em alguma o lado direito é negativo
    for(int i = 0; i < restricoes.size(); i++){

        if(restricoes[i].getSegundoMembro() < 0){

            // Percorre variáveis da restrição
            for(int j = 0; j < restricoes[i].getVariaveis().size(); j++){  
                restricoes[i].inverteCoeficiente(j); // Multiplica coeficientes por -1
            }

            restricoes[i].setRelacao("<="); // INverte a relação da restrição
            restricoes[i].setSegundoMembro(-(restricoes[i].getSegundoMembro())); // Multiplica lado direito por -1
        
        }
    }
}

void Modelo::printFuncaoObjetivo(){

    // Exibe a função objetivo em sua forma original
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

    // Exibe as restricoes na forma original do modelo
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

    cout << "\t";

    // Exibe restrições de não negatividade
    for(int i = 0; i < this->funcaoObjetivo.getVariaveis().size(); i++){
        if(i == this->funcaoObjetivo.getVariaveis().size()-1){
            cout << "x_" << i+1 << " >= 0";
        } else {
            cout << "x_" << i+1 << ", ";
        }
    }

    cout << endl;
}