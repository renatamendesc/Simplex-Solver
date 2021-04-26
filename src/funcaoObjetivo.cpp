#include "funcaoObjetivo.h"
#include <iostream>

using namespace std;

void FuncaoObjetivo::setTipo(string tipo){
    this->tipo = tipo;
}

void FuncaoObjetivo::setVariaveis(vector <float> coeficientes){
    Variaveis variavel;

    for(int i = 0; i < coeficientes.size(); i++){
        variavel.setIndice(i+1);
        variavel.setCoeficiente(coeficientes[i]);

        this->variaveis.push_back(variavel);
    }
    
}

void FuncaoObjetivo::setSegundoMembro(float segundoMembro){
    this->segundoMembro = segundoMembro;
}

float FuncaoObjetivo::getSegundoMembro(){
    return this->segundoMembro;
}

string FuncaoObjetivo::getTipo(){
    return this->tipo;
}

vector <Variaveis> FuncaoObjetivo::getVariaveis(){
    return this->variaveis;
}

