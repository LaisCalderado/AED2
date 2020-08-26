#include<stdio.h>
#include<stdlib.h>

int* BubbleInvertido(int *vetor, int tamanho){

    //Ordenando em ordem decrescente o vetor
    for (int i = 0; i < tamanho; i++){
        for (int j = 0; j < tamanho - 1; j++){            
            if (vetor[j] < vetor[j+ 1]){
                vetor[j] = vetor[j] + vetor[j + 1];
                vetor[j + 1] = vetor[j] - vetor[j + 1];
                vetor[j] = vetor[j] - vetor[j + 1];
            } 
        }
    }
    return vetor;
}

void Divisor(int *vetor, int tamanhoPen, int n){

    int contador = 0;
    int Valores[n];

    //Dando valor de 64G para as unidades do vetor
    for (int i = 0; i < n; i++){
        Valores[i] = tamanhoPen;
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (Valores[j] - vetor[i] >= 0){
                Valores[j] -= vetor[i];
                break;
            }
            
        }
    }
    //Contando o numero de pendrives necessários
    for (int i = 0; i < n; i++){
        if (Valores[i] != tamanhoPen){
            contador++;
        } 
    }  
    printf("Necessario %d pendrive(s) \n", contador);
}

int main(int argc, char **argv){

    //Quantidade de arquivos
    int quantidade;
    printf("Digite a quantidade de arquivos: \n");
    scanf("%d", &quantidade);

    //Iniciando o vetor como tanho dos arquivos
    int vetor[quantidade];

    //Recebendo os arquivos
    printf("Digite o tamanhos dos %d arquivos: \n", quantidade);
    for (int i = 0; i < quantidade; i++){
        scanf("%d", &vetor[i]);
    }
    printf("\n");

    //Imprimindo o vetor desordenado
    printf("Arquivos atual:\n");
    for (int i = 0; i < quantidade; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
    
    //Pendrive possui um tamanho de 64G
    int tamanhoPen = 64;

    // uma ponteiro recebera o vetor ordenado
    int *ordenado = BubbleInvertido(vetor, quantidade);

    //Imprimendo o vetor ordenando de forma decrescente
    printf("Vetor em ordem decrescente:\n");
    for (int i = 0; i < quantidade; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");

    //Utilizando o modelo de FFD 
    Divisor(ordenado, tamanhoPen, quantidade);

    return 0;

}  