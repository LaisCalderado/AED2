#include<stdio.h>
#include<stdlib.h>
#define true 1
#define false 0
#define Inicial 0
#define TemCaminho 1
#define SemCaminho 2

typedef int boll;
typedef int TipoPeso;

typedef struct adjacencia{
    //Vertice final, peso e o proximo da lista ligada
    int vertices;
    //TipoPeso peso;
    struct adjacencia *prox;
        
}ADJACENCIA;

typedef struct vertice{
    //Dados armazenados vão aqui
    //Estrutura que guarda a cabeça da lista ligada
    ADJACENCIA *cab;
}VERTICE;

//Grafo 
typedef struct grafo{
    //Numero de vertices e arestas
    int vertices;
    int arestas;
    //Arranjo de vertices
    VERTICE *adj;
}GRAFO;

//Criar um grafo sem aresta 
GRAFO *criaGrafo(int v){//Recebe o numero de vertices do grafo
    //Aloca memorica para o grafo
    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
    //Atualiza o numero de vertice e não coloca aresta
    g -> vertices = v;
    g -> arestas = 0;
    //Aloca o arranjo na memoria para o v 
    g -> adj = (VERTICE*)(malloc)(v * sizeof(VERTICE));
    for (int i = 0; i < v; i++){//Coloca null em todas as adjacencias
        g -> adj[i].cab = NULL;//Coloca Null em todas as adjacencias pq não tem arestas
    }return(g);//Cria o grafo
    
}
//Criando a adjacencia (aresta)
ADJACENCIA *criaAdj(int v){//Vai receber o vertice final da aresta e o peso
    //Aloca espaço para um nó final na lista
    ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
    //Assoocia a ele o vértice final da aresta e o peso
    temp ->vertices = v; 
    //temp ->peso = peso;
    temp -> prox = NULL;//O proximo campo é null e retorna
    return(temp);
}
//Uma aresta só é criada qndo add uma adjacencia a lista de um vertice
//Aresta tem o grafo que vai de vi ate vf e o peso,
boll criaAresta(GRAFO *gr, int vi, int vf){

    if (!gr) return false;//Se o grafo for null retorna falso
    if ((vf < 0 ) || vf >= gr ->vertices) return false;//um vertice final invalido retorna false
    if ((vi < 0 ) || (vi >= gr -> vertices)) return false;//um vertice inicial invalido retorna false
    //Cria adjacencia na memoria
    ADJACENCIA *novo = criaAdj(vf);//Adj recebe o vertice final e o peso
    //Insere a adj no inicio da lista de adj
    novo -> prox = gr -> adj[vi].cab; //O novo elemento recebe a cabeça da lista
    gr -> adj[vi].cab = novo;
    gr -> arestas++;//Inclui a aresta
    return(true);//Retorna 1;
    
}
void imprime (GRAFO *gr){
    //Total de arestas e vertices
    printf("Vertice: %d. Arestas: %d\n", gr->vertices, gr->arestas);

    //Para cada vertice fo grafo
    for (int i = 0; i < gr->vertices; i++){
        printf("V%d:", i);//Imprime o numero do vertice
        ADJACENCIA *ad = gr ->adj[i].cab;//ad recebe a cabeça da lista de adjacencia
        
        while (ad){//Enquando ad não for null
            //Imprime o valor da lista de adjacencia e o peso
            printf("-> v%d ", ad->vertices);
            //Passa para o proximo até o final
            ad = ad -> prox;
        }//Quando acabar passa para o proximo elemento e repete
        printf("\n");
    }
}


int main(){

    int vertices, arestas, vi, vf;

    GRAFO *gr = criaGrafo(6);
    

    criaAresta(gr,0,1);
    criaAresta(gr,0,2);
    criaAresta(gr,1,0);
    criaAresta(gr,1,3);
    criaAresta(gr,1,4);
    criaAresta(gr,2,4);
    criaAresta(gr,3,1);
    criaAresta(gr,4,5);
    //criaAresta(gr,5,6);
    //criaAresta(gr,6,5);


    /*Vertice: 5. Arestas: 6
        V0:-> v2 -> v1 
        V1:-> v4 -> v3 -> v0 
        V2:-> v4 
        V3:-> v1 
        V4:-> v2
    */

    imprime(gr);
}