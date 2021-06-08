#include "formaPadrao.h"
#include <cfloat>

using namespace std;

#define BIG_M 99999

// Construtor que transforma modelo original na sua forma padrao
FormaPadrao::FormaPadrao(Modelo formaOriginal){
    vector <double> coeficientes;
    VariaveisAdicionadas novaVariavel;
    Restricoes restricao;
    int somador = 0;

    // Verifica se há alguma restrição com segundo membro negativo
    formaOriginal.verificaNegatividade();
    
    // Analisa restrições e conta quantas e quais variaveis de folga/artificiais serão adicionadas
    for(int i = 0; i < formaOriginal.getRestricoes().size(); i++){

        if(formaOriginal.getRestricoes()[i].getRelacao() == "<="){
            novaVariavel.setIndice(i + formaOriginal.getFuncaoObjetivo().getVariaveis().size() + somador + 1);
            novaVariavel.setCoeficiente(1);
            novaVariavel.setTipo("Folga");
            novaVariavel.setRestricao(i+1);

            this->numeroFolgas++;

            this->outrasVariaveis.push_back(novaVariavel);

        }else if(formaOriginal.getRestricoes()[i].getRelacao() == "="){
            novaVariavel.setIndice(i + formaOriginal.getFuncaoObjetivo().getVariaveis().size() + somador + 1);
            novaVariavel.setCoeficiente(1);
            novaVariavel.setTipo("Artificial");
            novaVariavel.setRestricao(i+1);

            this->numeroArtificiais++;

            this->outrasVariaveis.push_back(novaVariavel);

            this->bigM = true;

        }else if(formaOriginal.getRestricoes()[i].getRelacao() == ">="){
            novaVariavel.setIndice(i + formaOriginal.getFuncaoObjetivo().getVariaveis().size() + somador + 1);
            novaVariavel.setCoeficiente(-1);
            novaVariavel.setTipo("Folga");
            novaVariavel.setRestricao(i+1);

            this->numeroFolgas++;

            this->outrasVariaveis.push_back(novaVariavel);
            somador++;

            novaVariavel.setIndice(i + formaOriginal.getFuncaoObjetivo().getVariaveis().size() + somador + 1);
            novaVariavel.setCoeficiente(1);
            novaVariavel.setTipo("Artificial");
            novaVariavel.setRestricao(i+1);

            this->numeroArtificiais++;

            this->outrasVariaveis.push_back(novaVariavel);

            this->bigM = true;
        }
    }

    // Percorre variaveis da função objetivo
    for(int i = 0; i < formaOriginal.getFuncaoObjetivo().getVariaveis().size() + numeroArtificiais + numeroFolgas; i++){
        
        // Percorre variaveis da função objetivo na forma original
        if(i < formaOriginal.getFuncaoObjetivo().getVariaveis().size()){
            coeficientes.push_back(formaOriginal.getFuncaoObjetivo().getVariaveis()[i].getCoeficiente());
            this->variaveisNaoBasicas.push_back(i+1); // Define variaveis de decisão como não básicas

        }else if(this->outrasVariaveis[i-formaOriginal.getFuncaoObjetivo().getVariaveis().size()].getTipo() == "Folga"){
            coeficientes.push_back(0);

        }else if(this->outrasVariaveis[i-formaOriginal.getFuncaoObjetivo().getVariaveis().size()].getTipo() == "Artificial"){
            
            // Verifica de coeficiente M será positivo ou negativo
            if(formaOriginal.getFuncaoObjetivo().getTipo() == "Max"){
                coeficientes.push_back(-BIG_M);
            }else if(formaOriginal.getFuncaoObjetivo().getTipo() == "Min"){
                coeficientes.push_back(BIG_M);
            }
        }
    }

    // Coloca função objetivo na forma padrão
    this->funcaoObjetivo.setTipo(formaOriginal.getFuncaoObjetivo().getTipo());
    this->funcaoObjetivo.setSegundoMembro(formaOriginal.getFuncaoObjetivo().getSegundoMembro());
    this->funcaoObjetivo.setVariaveis(coeficientes);

    coeficientes.clear();

    // Verifica se há ou não variáveis artificiais
    if(this->numeroArtificiais == 0){

        // Caso não haja variaveis artificiais, define folgas como básicas
        for(int i = 0; i < this->numeroFolgas; i++){
            this->variaveisBasicas.push_back(this->outrasVariaveis[i].getIndice());
            this->colunasMatrizIdentidade.push_back(this->outrasVariaveis[i].getIndice()-1);
        }

    } else {

        // Analisa variaveis que foram adicionadas
        for(int i = 0; i < this->outrasVariaveis.size(); i++){

            // Se a variavel for artificial, define como básica
            if(this->outrasVariaveis[i].getTipo() == "Artificial"){
                this->variaveisBasicas.push_back(this->outrasVariaveis[i].getIndice());
                this->colunasMatrizIdentidade.push_back(this->outrasVariaveis[i].getIndice()-1);

            } else if(this->outrasVariaveis[i].getTipo() == "Folga" && this->outrasVariaveis[i].getCoeficiente() == 1){
                this->variaveisBasicas.push_back(this->outrasVariaveis[i].getIndice());
                this->colunasMatrizIdentidade.push_back(this->outrasVariaveis[i].getIndice()-1);

            } else if(this->outrasVariaveis[i].getTipo() == "Folga" && this->outrasVariaveis[i].getCoeficiente() == -1){
                this->variaveisNaoBasicas.push_back(this->outrasVariaveis[i].getIndice());

            }
        }
    }

    // Percorre restrições do modelo em sua forma original
    for(int i = 0; i < formaOriginal.getRestricoes().size(); i++){

        // Percorre variáveis já existentes na restriçõe
        for(int j = 0; j < formaOriginal.getRestricoes()[i].getVariaveis().size(); j++){
            coeficientes.push_back(formaOriginal.getRestricoes()[i].getVariaveis()[j].getCoeficiente());
        }

        // Percorre variáveis a serem adicionadas
        for(int j = 0; j < this->outrasVariaveis.size(); j++){
            if(i == this->outrasVariaveis[j].getRestricao()-1){
                coeficientes.push_back(this->outrasVariaveis[j].getCoeficiente());
            }else{
                coeficientes.push_back(0);
            }
        }

        // Coloca restrição em questão na forma padrão
        restricao.setRelacao(formaOriginal.getRestricoes()[i].getRelacao());
        restricao.setSegundoMembro(formaOriginal.getRestricoes()[i].getSegundoMembro());
        restricao.setVariaveis(coeficientes);

        this->restricoes.push_back(restricao);

        coeficientes.clear();
    }

    // Chama metodo para setar o tableau com a solução básica incial
    this->setTableau();
}

void FormaPadrao::setTableau(){
    vector <double> linha, coeficientesSoma;
    vector <Restricoes> restricaoSoma;
    Restricoes resultante;

    for(int i = 0; i <= this->funcaoObjetivo.getVariaveis().size(); i++){

        if(i == this->funcaoObjetivo.getVariaveis().size()){
            linha.push_back(0);

        }else if(funcaoObjetivo.getTipo() == "Max" && funcaoObjetivo.getVariaveis()[i].getCoeficiente() != 0){
            linha.push_back(-funcaoObjetivo.getVariaveis()[i].getCoeficiente());

        }else if(funcaoObjetivo.getTipo() == "Min" || funcaoObjetivo.getVariaveis()[i].getCoeficiente() == 0){
            linha.push_back(funcaoObjetivo.getVariaveis()[i].getCoeficiente()); 
        }

    }

    // Adiciona primeira linha (Referente a função objetivo)
    if(this->bigM){
        // Verifica linha de variável artificial
        for(int i = 0; i < this->variaveisBasicas.size(); i++){
            for(int j = 0; j < this->outrasVariaveis.size(); j++){
                if(this->variaveisBasicas[i] == this->outrasVariaveis[j].getIndice() && this->outrasVariaveis[j].getTipo() == "Artificial"){ 
                    for(int k = 0; k < linha.size(); k++){
                        if(k == linha.size()-1){
                            linha[k] = linha[k] - (this->restricoes[i].getSegundoMembro() * BIG_M);
                        }else{
                            linha[k] = linha[k] - (this->restricoes[i].getVariaveis()[k].getCoeficiente() * BIG_M);
                        }
                    }
                }
            }
        }
    }

    // Adiciona linha ao tableau
    this->tableau.push_back(linha);
    linha.clear();

    // Adiciona linhas referentes as restrições
    for(int i = 0; i < this->restricoes.size(); i++){
        for(int j = 0; j <= this->restricoes[i].getVariaveis().size(); j++){
            if(j == this->restricoes[i].getVariaveis().size()){
                linha.push_back(this->restricoes[i].getSegundoMembro());
            } else {
                linha.push_back(this->restricoes[i].getVariaveis()[j].getCoeficiente());
            }
        }

        // Adiciona linha ao tableau
        this->tableau.push_back(linha);
        linha.clear();
    }
}

void FormaPadrao::setVariaveisBasicas(int colunaPivo, int linhaPivo){
    int entraBase, saiBase, indiceSai;

    // Determina variavel que entra na base
    for(int i = 0; i < this->funcaoObjetivo.getVariaveis().size(); i++){
        if(colunaPivo + 1 == this->funcaoObjetivo.getVariaveis()[i].getIndice()){
            entraBase = colunaPivo + 1;
        }
    }

    // Determina variavel que sai na base
    for(int i = 0; i < this->funcaoObjetivo.getVariaveis().size(); i++){
        if(this->variaveisBasicas[linhaPivo-1] == this->funcaoObjetivo.getVariaveis()[i].getIndice()){
            saiBase = this->variaveisBasicas[linhaPivo-1] ;
        }
        
    }

    // Determina indice da variavel que sai na base
    for(int i = 0; i < this->variaveisNaoBasicas.size(); i++){
        if(this->variaveisNaoBasicas[i] == entraBase){
            indiceSai = i;
        }
    }

    // Verifica se está na primeira ou segunda fase do método das duas fases
    this->variaveisBasicas[linhaPivo-1] = entraBase;
    
    
    // Atualiza vectores de variaveis basicas e não básicas
    this->variaveisNaoBasicas.push_back(saiBase);
    this->variaveisNaoBasicas.erase(variaveisNaoBasicas.begin() + indiceSai);

}

bool FormaPadrao::testeOtimalidade(){

    while(true){
        double menor = DBL_MAX;
        int colunaPivo;

        // Verifica qual o menor elemento:
        for(int i = 0; i < tableau[0].size()-1; i++){
            if(tableau[0][i] < menor && !comparaDouble(tableau[0][i], menor)){
                menor = tableau[0][i];
                colunaPivo = i;
            }
        }

        // Verifica se o menor elemento é negativo
        if(menor < 0){
            this->defineNovaBase(colunaPivo); // Se o menor elemento for negativo, continua simplex
            this->iter++;

        } else {
            return true; // Se o menor elemento for positivo, solução otima foi encontrada

        }
    }
}

void FormaPadrao::defineNovaBase(int colunaPivo){
    double menor = DBL_MAX, resultado = DBL_MAX;
    int linhaPivo;

    // Verifica a linha pivô
    for(int i = 1; i < this->tableau.size(); i++){

        if(this->tableau[i][colunaPivo] != 0){
            resultado = this->tableau[i][tableau[i].size()-1] / this->tableau[i][colunaPivo];
        }        

        if(menor == DBL_MAX){
            menor = resultado;
            linhaPivo = i;

        } else if((resultado < menor && !comparaDouble(resultado, menor)) && resultado >= 0 ){
            menor = resultado;
            linhaPivo = i;

        }

    }

    this->atualizaTableau(colunaPivo, linhaPivo); // Chama função apara atualizar tableau com nova linha e coluna pivo
    this->setVariaveisBasicas(colunaPivo, linhaPivo); // Atualiza variaveis básicas e não básicas do modelo

}

void FormaPadrao::atualizaTableau(int colunaPivo, int linhaPivo){
    double elementoPivo = this->tableau[linhaPivo][colunaPivo];

    // Atualiza nova linha pivô
    for(int i = 0; i < this->tableau[linhaPivo].size(); i++){
        this->tableau[linhaPivo][i] = this->tableau[linhaPivo][i] / elementoPivo;
    }

    // Atualiza as demais linhas
    for(int i = 0; i < this->tableau.size(); i++){
        if(i != linhaPivo){
            double elemento = -this->tableau[i][colunaPivo];

            for(int j = 0; j < this->tableau[i].size(); j++){
                this->tableau[i][j] = (elemento * this->tableau[linhaPivo][j]) + this->tableau[i][j];
            }
        }
    }
}

void FormaPadrao::analiseSensibilidade(){
    vector <vector <double>> matrizFolga;
    vector <double> linhas, maoDireita;

    // Percorre linhas do tableau:
    for(int i = 1; i < this->tableau.size(); i++){
        // Percorre elementos da linha (colunas):
        for(int j = 0; j < this->tableau[i].size(); j++){
            for(int k = 0; k < this->colunasMatrizIdentidade.size(); k++){

                // Verifica se a coluna em questão é referente a matriz identidade inicial
                if(j == this->colunasMatrizIdentidade[k]){
                    linhas.push_back(this->tableau[i][j]);
                }
            }
        }

        // Adiciona na matriz referente às variaveis de folga
        matrizFolga.push_back(linhas);
        linhas.clear();
    }

    // Adiciona valores no vetor da mão direita:
    for(int i = 1; i < tableau.size(); i++){
        for(int j = 0; j < tableau[i].size(); j++){
            if(j == this->tableau[i].size()-1){
                maoDireita.push_back(this->tableau[i][j]);
            }
        }
    }

    vector <double> rangeMenor(matrizFolga.size()), rangeMaior(matrizFolga.size());
    double range = 0, finalRangePositivo = 0, finalRangeNegativo = 0;
    int matrizFolgaLinhas = matrizFolga.size(), matrizFolgaColunas = matrizFolga[0].size();

    // Percorre todas restrições:
    for(int i = 0; i < matrizFolgaColunas; i++){
        finalRangeNegativo = 0;
        finalRangePositivo = 0;

        for(int j = 0; j < matrizFolgaLinhas; j++){
            bool validacao = true;
            
            if(matrizFolga[j][i] != 0){
                range = -(maoDireita[j]) / matrizFolga[j][i];

                // Verifica se o valor é valido para todas expressões
                for(int k = 0; k < matrizFolga.size(); k++){
                    if(matrizFolga[k][i] * range + maoDireita[k] < 0){
                        validacao = false;
                        break;
                    }
                }

            }else{
                validacao = false;
            }

            if(validacao){
                if(range < 0 && range < finalRangeNegativo){
                    finalRangeNegativo = range;

                }else if(range > 0 && range > finalRangePositivo){
                    finalRangePositivo = range;
                }
            }
        }

        rangeMenor[i] = finalRangeNegativo;
        rangeMaior[i] = finalRangePositivo;
    }

    for(int i = 0; i < maoDireita.size(); i++){
        if(rangeMaior[i] == 0){
            cout << "Aumento máximo para recurso " << i+1 << ": Infinito" << endl;
        } else {
            cout << "Aumento máximo para recurso " << i+1 << ": " << rangeMaior[i] << endl;
        }

        if(rangeMenor[i] == 0){
            cout << "Redução máxima para recurso " << i+1 << ": Infinito" << endl;
        } else {
            cout << "Redução máxima para recurso " << i+1 << ": " << -rangeMenor[i] << endl;
        }   
    }
}

void FormaPadrao::printTableau(){

    // Exibe tableau:
    for(int i = 0; i < this->tableau.size(); i++){
        for(int j = 0; j < this->tableau[i].size(); j++){
            cout << tableau[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
}

void FormaPadrao::printFuncaoObjetivo(){

    // Exibe função objetivo
    cout << "\nFunção Objetivo: " << funcaoObjetivo.getTipo() << " Z = ";
    
    for(int i = 0; i < this->funcaoObjetivo.getVariaveis().size(); i++){
        cout << this->funcaoObjetivo.getVariaveis()[i].getCoeficiente() << "x_" << funcaoObjetivo.getVariaveis()[i].getIndice();

        if(i < this->funcaoObjetivo.getVariaveis().size()-1){
            cout << " + ";
        }
    }

    cout << endl;
}

void FormaPadrao::printRestricoes(){

    cout << "\nSujeito a:\n";

    // Exibe as restricoes na forma padrao do modelo
    for(int i = 0; i < this->restricoes.size(); i++){
        cout << "\t";

        for(int j = 0; j < this->restricoes[i].getVariaveis().size(); j++){
            cout << this->restricoes[i].getVariaveis()[j].getCoeficiente() << "x_" << this->restricoes[i].getVariaveis()[j].getIndice();

            if(j < this->restricoes[i].getVariaveis().size()-1){
                cout << " + ";
            }
        }

        cout << " = " << this->restricoes[i].getSegundoMembro() << endl;   
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

double FormaPadrao::getValorOtimo(){

    if(funcaoObjetivo.getTipo() == "Max"){
        return this->tableau[0][tableau[0].size()-1];
    }else if(funcaoObjetivo.getTipo() == "Min"){
        return -(this->tableau[0][tableau[0].size()-1]);
    }
    
}

void FormaPadrao::getSolucaoOtima(vector <double> &solucaoVariaveisBasicas, vector <double> &solucaoVariaveisNaoBasicas, vector <int> &indicesVariaveisBasicas, vector <int> &indicesVariaveisNaoBasicas){

    for(int i = 0; i < this->variaveisNaoBasicas.size(); i++){
        for(int j = 0; j < this->funcaoObjetivo.getVariaveis().size(); j++){
            if(this->variaveisNaoBasicas[i] == this->funcaoObjetivo.getVariaveis()[j].getIndice()){
                solucaoVariaveisNaoBasicas.push_back(0);
                indicesVariaveisNaoBasicas.push_back(this->variaveisNaoBasicas[i]);
            }
        }
    }

    for(int i = 0; i < this->variaveisBasicas.size(); i++){
        for(int j = 0; j < this->funcaoObjetivo.getVariaveis().size(); j++){
            if(this->variaveisBasicas[i] == this->funcaoObjetivo.getVariaveis()[j].getIndice()){
                solucaoVariaveisBasicas.push_back(this->tableau[i+1][tableau[i+1].size()-1]);
                indicesVariaveisBasicas.push_back(this->variaveisBasicas[i]);
            }
        }
    }
}

int FormaPadrao::getIteracoes(){
    return this->iter;
}

bool FormaPadrao::comparaDouble(double a, double b){

    double epsilon = 0.001;
    return abs(a - b) < epsilon;

}