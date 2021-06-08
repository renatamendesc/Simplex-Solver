#include "variaveisAdicionadas.h"

using namespace std;

void VariaveisAdicionadas::setIndice(int i){
    this->indice = i;
}

void VariaveisAdicionadas::setCoeficiente(double c){
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

double VariaveisAdicionadas::getCoeficiente(){
    return this->coeficiente;
}

int VariaveisAdicionadas::getRestricao(){
    return this->restricao;
}