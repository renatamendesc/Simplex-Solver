# Simplex Solver
The Simplex method is an algorithm used to solve Linear Programming problems, searching for the optimal solution on each iteration.
In practice, Simplex covers vertices of a graphic that represents a feasible region of solutions to the problem, returning the best result that was found. Therefore, it's an exact method to solve **optimization problems**.

## Running the program
To run the program, it's necessary to indicate a Linear Programming model, indicating its objective function (whether if it's a maximization or minimization) and telling the constraints of the problem.

``` 
// Inicializa função objetivo do modelo
modelo.setFuncaoObjetivo((TIPO DE FUNÇÃO OBJETIVO), (COEFICIENTES));

// Inicializa restricoes do modelo
modelo.setRestricoes((TIPO DE RESTRIÇÃO), (LADO DIREITO), (COEFICIENTES));
```
**Initializing a model:**

As an example to solve the following model:

<!--
![image](https://cdn.discordapp.com/attachments/806262947160653834/854752706090631208/WhatsApp_Image_2021-06-08_at_13.03.04_1.jpg)
-->

We can express it on the code in the following way:

```
// Inicializa função objetivo do modelo
modelo.setFuncaoObjetivo("Max", {3, 5});

// Inicializa restricoes do modelo
modelo.setRestricoes("Menor ou igual", 4, {1, 0});
modelo.setRestricoes("Menor ou igual", 12, {0, 2});
modelo.setRestricoes("Igual", 18, {3, 2});
```

## Resuls
Finally, you should just run the program with the ```./main``` command and the solution will be shown. Also, the algorithm can do the **sensitivity analysis** of the maximum increase and decrease allowed to the resources used, without changing the solution (modifying only the objective function's result).
