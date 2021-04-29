#include "variaveisAdicionadas.h"

void VariaveisAdicionadas::setIndice(int i){
    this->indice = i;
}

void VariaveisAdicionadas::setCoeficiente(float c){
    this->coeficiente = c;
}

void VariaveisAdicionadas::setTipo(string t){
    this->tipo = t;
}

void VariaveisAdicionadas::setRestricao(int indiceRestricao){
    this->restricao = indiceRestricao;
}

string VariaveisAdicionadas::getTipo(){
    return this->tipo;
}

int VariaveisAdicionadas::getIndice(){
    return this->indice;
}

float VariaveisAdicionadas::getCoeficiente(){
    return this->coeficiente;
}

int VariaveisAdicionadas::getRestricao(){
    return this->restricao;
}