#include "dual.h"
#include <iostream>

using namespace std;


Dual::Dual(Modelo primal){
    int numeroVariaveis, numeroRestricoes;
    float coeficiente, coeficienteRestricao, segundoMembro;
    vector <float> coeficientes, coeficientesRestricoes;
    string tipo, relacao;

    // Define tipo do dual:
    if(primal.getFuncaoObjetivo().getTipo() == "Max"){
        tipo = "Min";
    } else if(primal.getFuncaoObjetivo().getTipo() == "Min"){
        tipo = "Max";
    }

    // Define coeficientes das variaveis decisão:
    for(int i = 0; i < primal.getRestricoes().size(); i++){

        coeficiente = primal.getRestricoes()[i].getSegundoMembro();
        coeficientes.push_back(coeficiente);

    }

    this->setFuncaoObjetivo(tipo, coeficientes);

    for(int i = 0; i < primal.getFuncaoObjetivo().getVariaveis().size(); i++){
      
        // Define relação das restrições:
        if(primal.getFuncaoObjetivo().getTipo() == "Max"){
            relacao = ">=";
            
        }else if(primal.getFuncaoObjetivo().getTipo() == "Min"){
            relacao = "<=";

        }

        segundoMembro = primal.getFuncaoObjetivo().getVariaveis()[i].getCoeficiente();

        for(int j = 0; j < primal.getRestricoes().size(); j++){

            coeficienteRestricao = primal.getRestricoes()[j].getVariaveis()[i].getCoeficiente();

            coeficientesRestricoes.push_back(coeficienteRestricao);
        }

        this->setRestricoes(relacao, segundoMembro, coeficientesRestricoes);
        coeficientesRestricoes.clear();
    }

}

void Dual::setFuncaoObjetivo(string tipo, vector <float> coeficientes){
    
    this->funcaoObjetivo.setTipo(tipo);
    this->funcaoObjetivo.setVariaveis(coeficientes);

}

void Dual::setRestricoes(string relacao, float segundoMembro, vector <float> coeficientes){

    Restricoes restricao;

    restricao.setVariaveis(coeficientes);
    restricao.setSegundoMembro(segundoMembro);
    restricao.setRelacao(relacao);

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