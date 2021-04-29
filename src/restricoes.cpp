#include "restricoes.h"

void Restricoes::setRelacao(string relacao){
    this->relacao = relacao;
}

void Restricoes::setVariaveis(vector <float> coeficientes){
    Variaveis variavel;

    variaveis.clear();
    for(int i = 0; i < coeficientes.size(); i++){
        variavel.setIndice(i+1);
        variavel.setCoeficiente(coeficientes[i]);

        this->variaveis.push_back(variavel);
    }
}

void Restricoes::inverteCoeficiente(int indice){
    this->variaveis[indice].setCoeficiente(-(this->variaveis[indice].getCoeficiente()));
}

void Restricoes::setSegundoMembro(float segundoMembro){
    this->segundoMembro = segundoMembro;
}

vector <Variaveis> Restricoes::getVariaveis(){
    return this->variaveis;
}

string Restricoes::getRelacao(){
    return this->relacao;
}

float Restricoes::getSegundoMembro(){
    return this->segundoMembro;
}