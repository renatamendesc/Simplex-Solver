#include "variaveis.h"
#include <iostream>

void Variaveis::setIndice(int i){
    this->indice = i;
}

void Variaveis::setCoeficiente(double c){
    this->coeficiente = c;
}

int Variaveis::getIndice(){
    return this->indice;
}

double Variaveis::getCoeficiente(){
    return this->coeficiente;
}