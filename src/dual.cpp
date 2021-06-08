#include "dual.h"

using namespace std;

// Construtor que transforma primal no dual
Dual::Dual(Modelo primal){
    int numeroVariaveis, numeroRestricoes;
    double coeficiente, coeficienteRestricao, segundoMembro;
    vector <double> coeficientes, coeficientesRestricoes;
    string tipo, relacao;

    // Define tipo do dual
    if(primal.getFuncaoObjetivo().getTipo() == "Max"){
        tipo = "Min";
    } else if(primal.getFuncaoObjetivo().getTipo() == "Min"){
        tipo = "Max";
    }

    // Define coeficientes das variaveis decisão
    for(int i = 0; i < primal.getRestricoes().size(); i++){

        coeficiente = primal.getRestricoes()[i].getSegundoMembro();
        coeficientes.push_back(coeficiente);

    }

    // Establece funcao objetivo do modelo dual
    this->setFuncaoObjetivo(tipo, coeficientes);

    for(int i = 0; i < primal.getFuncaoObjetivo().getVariaveis().size(); i++){
      
        // Define relação das restrições
        if(primal.getFuncaoObjetivo().getTipo() == "Max"){
            relacao = ">=";
            
        }else if(primal.getFuncaoObjetivo().getTipo() == "Min"){
            relacao = "<=";

        }

        // Estabelece lado direito da restrição em questão
        segundoMembro = primal.getFuncaoObjetivo().getVariaveis()[i].getCoeficiente();

        // Percorre variaveis das restrições do primal
        for(int j = 0; j < primal.getRestricoes().size(); j++){

            // Adiciona coeficientes das restrições do dual
            coeficienteRestricao = primal.getRestricoes()[j].getVariaveis()[i].getCoeficiente();
            coeficientesRestricoes.push_back(coeficienteRestricao);
        }

        // Define restrição do modelo dual
        this->setRestricoes(relacao, segundoMembro, coeficientesRestricoes);
        coeficientesRestricoes.clear();
    }

    // Verifica se variáveis do dual terão restrições de negatividade ou não negatividade
    for(int i = 0; i < primal.getRestricoes().size(); i++){

        if(primal.getFuncaoObjetivo().getTipo() == "Max"){

            if(primal.getRestricoes()[i].getRelacao() == ">="){
                this->restricoesVariaveis.push_back("<=");
            }else if(primal.getRestricoes()[i].getRelacao() == "="){
                this->restricoesVariaveis.push_back("livre");
            }else if(primal.getRestricoes()[i].getRelacao() == "<="){
                this->restricoesVariaveis.push_back(">=");
            }

        }else if(primal.getFuncaoObjetivo().getTipo() == "Min"){

            if(primal.getRestricoes()[i].getRelacao() == ">="){
                this->restricoesVariaveis.push_back(">=");
            }else if(primal.getRestricoes()[i].getRelacao() == "="){
                this->restricoesVariaveis.push_back("livre");
            }else if(primal.getRestricoes()[i].getRelacao() == "<="){
                this->restricoesVariaveis.push_back("<=");
            }
        }
    }
}

void Dual::setFuncaoObjetivo(string tipo, vector <double> coeficientes){
    
    this->funcaoObjetivo.setTipo(tipo);
    this->funcaoObjetivo.setVariaveis(coeficientes);

}

void Dual::setRestricoes(string relacao, double segundoMembro, vector <double> coeficientes){

    Restricoes restricao;

    restricao.setVariaveis(coeficientes);
    restricao.setSegundoMembro(segundoMembro);
    restricao.setRelacao(relacao);

    this->restricoes.push_back(restricao);
}

void Dual::printFuncaoObjetivo(){

    // Exibe a função objetivo do modelo dual
    cout << "\nFunção Objetivo: " << this->funcaoObjetivo.getTipo() << " W = ";
    
    for(int i = 0; i < this->funcaoObjetivo.getVariaveis().size(); i++){
        cout << this->funcaoObjetivo.getVariaveis()[i].getCoeficiente() << "y_" << this->funcaoObjetivo.getVariaveis()[i].getIndice();

        if(i < this->funcaoObjetivo.getVariaveis().size()-1){
            cout << " + ";
        }
    }

    cout << endl;
}

void Dual::printRestricoes(){

    cout << "\nSujeito a:\n";

    // Exibe as restricoes na forma original do modelo
    for(int i = 0; i < this->restricoes.size(); i++){

        cout << "\t";

        for(int j = 0; j < this->restricoes[i].getVariaveis().size(); j++){

            if(this->restricoes[i].getVariaveis()[j].getCoeficiente() != 0){
                cout << this->restricoes[i].getVariaveis()[j].getCoeficiente() << "y_" << this->restricoes[i].getVariaveis()[j].getIndice();

                if(j < this->restricoes[i].getVariaveis().size()-1 && this->restricoes[i].getVariaveis()[j+1].getCoeficiente() != 0){
                    cout << " + ";
                }
            }
        }

        cout << " " << this->restricoes[i].getRelacao() << " " << this->restricoes[i].getSegundoMembro() << endl;
        
    }

    cout << "\t";

    // Exibe restrições de não negatividade
    for(int i = 0; i < this->restricoesVariaveis.size(); i++){

        if(this->restricoesVariaveis[i] == ">="){
            cout << "x_" << i+1 << " >= 0";
        }else if(this->restricoesVariaveis[i] == "<="){
            cout << "x_" << i+1 << " <= 0";
        }else if(this->restricoesVariaveis[i] == "livre"){
            cout << "x_" << i+1 << " livre";
        }

        if(i != this->restricoesVariaveis.size()-1){
            cout << ", ";
        }
        
    }

    cout << endl;
}