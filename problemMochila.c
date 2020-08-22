#include<stdio.h>

//Elementos no qual cada possui um valor (v) e um peso (w)
//Objetivo: Colocar os elementos na mochila
//A mochila tem uma capacidade maxima: W
//Exemplo:(peso, valor)
//  elemento 1: (2, 4)
//  elemento 2: (4, 8)
//  ...
//Conjunto S de n elementos
//Todo elemento tem um peso wi (w é o peso do elemento i) e valor/beneficio bi (b é o valor do elemento i)


int knapsack(int W, int wt[], int b[], int n){
    //tabela 
    int v[n + 1][W + 1];

    //Inicializando a primeira linha e coluna com zero
    for (int w = 1; w <= W; w++){
        v[0][w] = 0;
    }
    for (int i = 1; i <= n; i++){
        v[i][0] = 0;
    }
    for (int i = 1; i <= n; i++){
        for (int w = 1; w <= W; w++){
            //elemento pode fazer parte da solução
            if (wt[i -1] <= w){
                if ((b[i-1] + v[i -1][w -wt[i-1]]) > v[i -1][w]){
                    v[i][w] = b[i-1] + v[i -1][w -wt[i-1]];
                }
                else v[i][w] =v[i -1][w];
                
            }else v[i][w] = v[i -1][w];
            
        }
        
    }
    //retorna o valor maximo colocado na mochila
    return v[n][W];
    
    
}



int main(){

    //Capacidade maxima 
    int W = 20;

    //Numero de elementos
    int n = 5;

    //Vetor com os valores de cada elemento
    int b[] = {3, 5, 8, 4, 10};

    //vetor com os pesos de cada elemento
    int wt[] = {2,4,5,3,9};


    //O valor maximo que pode ser colocado na mochila
    int maxValor = knapsack(W, wt, b, n);

    printf("Valor maximo: %d\n", maxValor);

    return 0;
}