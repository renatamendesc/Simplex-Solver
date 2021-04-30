#include "formaPadrao.h"
#include <cfloat>

// Construtor que transforma modelo original na sua forma padrao
FormaPadrao::FormaPadrao(Modelo formaOriginal){
    vector <float> coeficientes;
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

            this->duasFases = true; // Caso haja variável artificial, haverá método das duas fases

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

            this->duasFases = true; // Caso haja variável artificial, haverá método das duas fases
        }
    }

    // Percorre variaveis da função objetivo
    for(int i = 0; i < formaOriginal.getFuncaoObjetivo().getVariaveis().size() + numeroArtificiais + numeroFolgas; i++){
        // Percorre variaveis da função objetivo na forma original
        if(i < formaOriginal.getFuncaoObjetivo().getVariaveis().size()){
            coeficientes.push_back(formaOriginal.getFuncaoObjetivo().getVariaveis()[i].getCoeficiente());
            this->variaveisNaoBasicas.push_back(i+1); // Define variaveis de decisão como não básicas
        } else {
            coeficientes.push_back(0);
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
        }

    } else {

        // Analisa variaveis que foram adicionadas
        for(int i = 0; i < this->outrasVariaveis.size(); i++){
            // Se a variavel for artificial, define como básica
            if(this->outrasVariaveis[i].getTipo() == "Artificial"){
                this->variaveisBasicas.push_back(this->outrasVariaveis[i].getIndice());
            } else if(this->outrasVariaveis[i].getTipo() == "Folga" && this->outrasVariaveis[i].getCoeficiente() == 1){
                this->variaveisBasicas.push_back(this->outrasVariaveis[i].getIndice());
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
    vector <float> linha;
    vector <Restricoes> restricaoSoma;
    vector <float> coeficientesSoma;
    Restricoes resultante;


    // Adiciona primeira linha (Referente a função objetivo)
    for(int i = 0; i <= this->funcaoObjetivo.getVariaveis().size(); i++){
        if(i == this->funcaoObjetivo.getVariaveis().size()){
            linha.push_back(0);

        }else if(funcaoObjetivo.getTipo() == "Max" && funcaoObjetivo.getVariaveis()[i].getCoeficiente() != 0){
            linha.push_back(-(funcaoObjetivo.getVariaveis()[i].getCoeficiente()));

        }else if(funcaoObjetivo.getTipo() == "Min" || funcaoObjetivo.getVariaveis()[i].getCoeficiente() == 0){
            linha.push_back(funcaoObjetivo.getVariaveis()[i].getCoeficiente()); 
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

    // Verifica se será usado o método das duas fases
    if(this->duasFases){

        // Verifica restrições com variáveis artificiais
        for(int i = 0; i < this->restricoes.size(); i++){
            if(this->restricoes[i].getRelacao() == "=" || this->restricoes[i].getRelacao() == ">="){
                restricaoSoma.push_back(this->restricoes[i]);
            }
        }

        // Percorre variaveis de restrições com variaveis artificiais
        for(int i = 0; i <= restricaoSoma[0].getVariaveis().size(); i++){
            float elemento = 0;

            // Calcula "função objetivo" da primeira fase
            for(int j = 0; j < restricaoSoma.size(); j++){ 

                if(i == restricaoSoma[0].getVariaveis().size()){
                    elemento += restricaoSoma[j].getSegundoMembro();
                }else{
                    elemento += restricaoSoma[j].getVariaveis()[i].getCoeficiente();
                }
                
            }

            if(elemento == 0){
                coeficientesSoma.push_back(elemento);
            }else{
                coeficientesSoma.push_back(-elemento);
            }
            
        }

        for(int i = 0; i < restricaoSoma.size(); i++){
            for(int j = 0; j < restricaoSoma[i].getVariaveis().size(); j++){
                for(int k = 0; k < variaveisBasicas.size(); k++){
                    if(restricaoSoma[i].getVariaveis()[j].getIndice() == variaveisBasicas[k]){
                        coeficientesSoma[j] = 0;
                    }
                }
            }
        }

        for(int i = 0; i < coeficientesSoma.size(); i++){
            linha.push_back(coeficientesSoma[i]);
        }

        // Adiciona linha ao tableau:
        this->tableau.insert(tableau.begin(), linha);
        coeficientesSoma.clear();
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
        if(duasFases && !segundaFase){
            if(this->variaveisBasicas[linhaPivo-2] == this->funcaoObjetivo.getVariaveis()[i].getIndice()){
                saiBase = this->variaveisBasicas[linhaPivo-2] ;
            }
        } else {
            if(this->variaveisBasicas[linhaPivo-1] == this->funcaoObjetivo.getVariaveis()[i].getIndice()){
                saiBase = this->variaveisBasicas[linhaPivo-1] ;
            }
        }
    }

    // Determina indice da variavel que sai na base
    for(int i = 0; i < this->variaveisNaoBasicas.size(); i++){
        if(this->variaveisNaoBasicas[i] == entraBase){
            indiceSai = i;
        }
    }

    // Verifica se está na primeira ou segunda fase do método das duas fases
    if(duasFases && !segundaFase){
        this->variaveisBasicas[linhaPivo-2] = entraBase;
    } else {
        this->variaveisBasicas[linhaPivo-1] = entraBase;
    }
    
    // Atualiza vectores de variaveis basicas e não básicas
    this->variaveisNaoBasicas.push_back(saiBase);
    this->variaveisNaoBasicas.erase(variaveisNaoBasicas.begin() + indiceSai);

}

bool FormaPadrao::testeOtimalidade(){

    while(true){
        iteracoes++;

        float menor = DBL_MAX;
        int colunaPivo;

        // Verifica qual o menor elemento:
        for(int i = 0; i < tableau[0].size()-1; i++){
            if(tableau[0][i] < menor && !comparaFloat(tableau[0][i], menor)){
                menor = tableau[0][i];
                colunaPivo = i;
            }
        }

        // Caso esteja sendo realizado o metodo das duas fases
        if(duasFases && !segundaFase){
            this->verificaSegundaFase(); // verifica se variaveis artificiais são básicas ou não
            if(segundaFase){
                continue;
            }
        }

        // Verifica se o menor elemento é negativo
        if(menor < 0){
            this->defineNovaBase(colunaPivo); // Se o menor elemento for negativo, continua simplex
        } else {
            return true; // Se o menor elemento for positivo, solução otima foi encontrada
        }
    }
}

void FormaPadrao::verificaSegundaFase(){
    int contadorBase = 0;

    // Verifica se ainda há bariáveis artificiais na base (não zeradas)
    for(int i = 0; i < this->outrasVariaveis.size(); i++){
        if(this->outrasVariaveis[i].getTipo() == "Artificial"){

            for(int j = 0; j < this->variaveisBasicas.size(); j++){
                if(this->outrasVariaveis[i].getIndice() == this->variaveisBasicas[j]){
                    contadorBase++;
                }
            }
        }
    }

    // Verifica fase do metodo das duas fases
    if(contadorBase == 0){
        segundaFase = true;
    }

    // Caso o simplex esteja na segunda fase
    if(segundaFase){
        // Apaga "função objetivo" da primeira fase
        this->tableau.erase(this->tableau.begin());

        // Percorre variaveis de folga e artificiais
        for(int i = 0; i < this->outrasVariaveis.size(); i++){

            // Caso a variavel seja artificial
            if(this->outrasVariaveis[i].getTipo() == "Artificial"){

                // Procura coluna referente a variavel artifical
                for(int j = 0; j < this->tableau[0].size(); j++){

                    // Aloca 0 na coluna da variavel
                    if(this->outrasVariaveis[i].getIndice() == j+1){
                        for(int k = 0; k < this->tableau.size(); k++){
                            this->tableau[k][j] = 0;
                        }
                    } 
                }
            }
        }
    }
}

void FormaPadrao::defineNovaBase(int colunaPivo){
    float menor = DBL_MAX, resultado = DBL_MAX;
    int linhaPivo;

    // Verifica a linha pivô
    for(int i = 1; i < this->tableau.size(); i++){

        if(duasFases && !segundaFase){
            if(this->tableau[i][colunaPivo] != 0 && i != 1){
                resultado = this->tableau[i][tableau[i].size()-1] / this->tableau[i][colunaPivo];
            }
        }else {
            if(this->tableau[i][colunaPivo] != 0){
                resultado = this->tableau[i][tableau[i].size()-1] / this->tableau[i][colunaPivo];
            }
        }

        if(menor == DBL_MAX){
            menor = resultado;
            linhaPivo = i;
        } else if(resultado < menor && resultado >= 0){
            menor = resultado;
            linhaPivo = i;
        }

    }

    this->atualizaTableau(colunaPivo, linhaPivo); // Chama função apara atualizar tableau com nova linha e coluna pivo
    this->setVariaveisBasicas(colunaPivo, linhaPivo); // Atualiza variaveis básicas e não básicas do modelo

}

void FormaPadrao::atualizaTableau(int colunaPivo, int linhaPivo){
    float elementoPivo = this->tableau[linhaPivo][colunaPivo];

    // Atualiza nova linha pivô
    for(int i = 0; i < this->tableau[linhaPivo].size(); i++){
        this->tableau[linhaPivo][i] = this->tableau[linhaPivo][i] / elementoPivo;
    }  

    // Atualiza as demais linhas
    for(int i = 0; i < this->tableau.size(); i++){
        if(i != linhaPivo){
            float multiplicador = -(this->tableau[i][colunaPivo]);

            for(int j = 0; j < this->tableau[i].size(); j++){
                float somador = this->tableau[i][j];

                this->tableau[i][j] = (multiplicador * (this->tableau[linhaPivo][j])) + somador;
            }
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

float FormaPadrao::getValorOtimo(){

    if(funcaoObjetivo.getTipo() == "Max"){
        return this->tableau[0][tableau[0].size()-1];
    }else if(funcaoObjetivo.getTipo() == "Min"){
        return -(this->tableau[0][tableau[0].size()-1]);
    }
    
}

void FormaPadrao::getSolucaoOtima(vector <float> &solucaoVariaveisBasicas, vector <float> &solucaoVariaveisNaoBasicas, vector <int> &indicesVariaveisBasicas, vector <int> &indicesVariaveisNaoBasicas){

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
    return this->iteracoes;
}

void FormaPadrao::analiseSensibilidade(){
    vector <vector <float>> matrizFolga;
    vector <float> linhas, maoDireita;

    // Percorre linhas do tableau:
    for(int i = 1; i < this->tableau.size(); i++){
        // Percorre elementos da linha (colunas):
        for(int j = 0; j < this->tableau[i].size(); j++){
            for(int k = 0; k < this->outrasVariaveis.size(); k++){
                // Verifica se a coluna em questão é referente a uma variável de folga:
                if(this->outrasVariaveis[k].getTipo() == "Folga" && j+1 == this->outrasVariaveis[k].getIndice()){
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

    vector <float> limiteMenor(matrizFolga.size()), limiteMaior(matrizFolga.size());
    float limite;

    // Percorre todas restrições:
    for(int i = 0; i < matrizFolga.size(); i++){
        int contadorPositivo = 0, contadorNegativo = 0;
        float maiorNegativo = 0, menorPositivo = 0;

        for(int j = 0; j < matrizFolga.size(); j++){
            
            if(matrizFolga[j][i] != 0){
                limite = -(maoDireita[j])/matrizFolga[j][i];

                if(limite < 0 && contadorNegativo == 0){
                    maiorNegativo = limite;
                    contadorNegativo++;

                }else if(limite < 0 && limite > maiorNegativo){
                    maiorNegativo = limite;

                }

                if(limite > 0 && contadorPositivo == 0){
                    menorPositivo = limite;
                    contadorPositivo++;

                }else if(limite > 0 && limite < menorPositivo){
                    menorPositivo = limite;

                } 
            }
        }

        limiteMaior[i] = menorPositivo;
        limiteMenor[i] = maiorNegativo;

    }

    // Exibe os aumentos e reduções máximos para as variáveis de folga:
    for(int i = 0; i < matrizFolga.size(); i++){
        for(int j = 0; j < this->outrasVariaveis.size(); j++){
            if(this->outrasVariaveis[j].getTipo() == "Folga"){

                if(limiteMaior[i] ==  0){
                    cout << "Aumento máximo para x_" << this->outrasVariaveis[j].getIndice() + i << ": Infinito " << endl;
                }else{
                    cout << "Aumento máximo para x_" << this->outrasVariaveis[j].getIndice() + i << ": " << limiteMaior[i] << endl;
                }

                if(limiteMenor[i] ==  0){
                    cout << "Redução máxima para x_" << this->outrasVariaveis[j].getIndice() + i << ": Infinito " << endl;
                }else{
                    cout << "Redução máxima para x_" << this->outrasVariaveis[j].getIndice() + i << ": " << -limiteMenor[i] << endl;
                }

                break;
            }
        }  
    }   
}

bool FormaPadrao::comparaFloat(float a, float b){

    float epsilon = 0.001;
    return abs(a - b) < epsilon;

}