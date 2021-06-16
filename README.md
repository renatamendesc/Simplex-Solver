# Resolvedor Simplex
O método Simplex é um algoritmo utilizado para solucionar problemas de Programação Linear, buscando a solução ótima, seja ela de maximização ou de minimização, a cada iteração realizada. Na prática, o Simplex percorre vértices de um gráfico que representa a região de soluções viáveis do problema indicado, retornando o melhor resultado encontrado. Sendo assim, se trata de um método exato para resolução de **problemas de otimização**.

## Funcionamento
Para utilizar o programa, é necessário indicar um modelo de Programação Linear válido, determinando sua função objetivo (indicando se é um problema de maximização ou minimização) e informando as restrições do problema a serem respeitadas.

``` 
// Inicializa função objetivo do modelo
modelo.setFuncaoObjetivo((TIPO DE FUNÇÃO OBJETIVO), (COEFICIENTES));

// Inicializa restricoes do modelo
modelo.setRestricoes((TIPO DE RESTRIÇÃO), (LADO DIREITO), (COEFICIENTES));
```
**Exemplo de inicialização de um modelo**

Como exemplo, para resolver o seguinte modelo:

<!---

-->

![image](https://cdn.discordapp.com/attachments/806262947160653834/854752706090631208/WhatsApp_Image_2021-06-08_at_13.03.04_1.jpg)

Podemos expressá-lo no código da maneira abaixo:

```
// Inicializa função objetivo do modelo
modelo.setFuncaoObjetivo("Max", {3, 5});

// Inicializa restricoes do modelo
modelo.setRestricoes("Menor ou igual", 4, {1, 0});
modelo.setRestricoes("Menor ou igual", 12, {0, 2});
modelo.setRestricoes("Igual", 18, {3, 2});
```

## Resultados
Feito isso, basta rodar o programa com o com o comando ```./main```, e a solução do modelo será exibida. É importante deixar claro que por padrão, o programa só resolve problemas onde suas variáveis possuem restrições de não negatividade.

Além disso, o programa também é capaz de realizar a **análise de sensibilidade** com relação ao aumento máximo e redução máxima para os recursos utilizados, sem que a solução seja alterada (modificando apenas o resultado da função objetivo).

