#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define true 1
#define false 0
#define BRANCO 0
#define AMARELO 1
#define VERMELHO 3

typedef int bool;
typedef int TipoPeso;


typedef struct adjacencia{
    //Vertice final, peso e o proximo da lista ligada
    int vertices;
    TipoPeso peso;
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
ADJACENCIA *criaAdj(int v, int peso){//Vai receber o vertice final da aresta e o peso
    //Aloca espaço para um nó final na lista
    ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
    //Assoocia a ele o vértice final da aresta e o peso
    temp ->vertices = v; 
    temp ->peso = peso;
    temp -> prox = NULL;//O proximo campo é null e retorna
    return(temp);
}
//Uma aresta só é criada qndo add uma adjacencia a lista de um vertice
//Aresta tem o grafo que vai de vi ate vf e o peso,
bool criaAresta(GRAFO *gr, int vi, int vf, TipoPeso p){

    if (!gr) return false;//Se o grafo for null retorna falso
    if ((vf < 0 ) || vf >= gr ->vertices) return false;//um vertice final invalido retorna false
    if ((vi < 0 ) || (vi >= gr -> vertices)) return false;//um vertice inicial invalido retorna false
    //Cria adjacencia na memoria
    ADJACENCIA *novo = criaAdj(vf,p);//Adj recebe o vertice final e o peso
    //Insere a adj no inicio da lista de adj
    novo -> prox = gr -> adj[vi].cab; //O novo elemento recebe a cabeça da lista
    gr -> adj[vi].cab = novo;
    gr -> arestas++;//Inclui a aresta
    return(true);//Retorna 1;
    
}

void profundidade(GRAFO *g){
    int i;
    int cor[g->vertices];
    //Inicializando todos os vertices como branco
    for(i = 0; i < g->vertices; i++){
        cor[i] = BRANCO;
    }
    for(i = 0; i < g->vertices; i++){
        if (cor[i] ==BRANCO){
            visitaP(g, i, cor);
        }
    } 
}
void visitaP( GRAFO *g, int i, int *cor){
    //AO visitar o no ele é marcado de amarelo
    cor[i] = AMARELO;
    //Então é visitado suas adjacencias recursivamente
    ADJACENCIA *v = g->adj[i].cab;
    //Mas só visita vertices ainda não visitados
    while (v){//Usa recurssividade para visitar as arestas
        if (cor[v->vertices]==BRANCO){
            visitaP(g, v->vertices,cor);
        }
        v = v->prox;
    }
    cor[i] = VERMELHO;
    
}
//Inicializando o grafo
//Arranjo de distancia, predecessor e ponto inicial
void inicializaD(GRAFO *g, int *d, int *p, int s){
    //
    for (int v = 0; v < g->vertices; v++){
        //Pega o maior valor e divide por 2 para não dar negativo
        d[v] = INT_MAX/2;
        //O predecessor de todos é -1
        p[v] = -1;

    }
    //A distancia de todos é 0
    d[s] = 0;
    
}
void relaxa(GRAFO *g, int *d, int *p, int u, int v){
    ADJACENCIA *ad = g->adj[u].cab;
    while (ad && ad->vertices != v){
        ad = ad->prox;
    }

    if (ad){
        if (d[v] > d[u] + ad->peso){
            d[v] = d[u] + ad->peso;
            p[v] = u;
        }
    }    
}
int dijkstra (GRAFO *g, int s){
    
    int *d = (int *) malloc(g->vertices*sizeof(int));
    int p[g->vertices];

    bool aberto[g->vertices];
    inicializaD(g,d,p,s);

    int i;
    for (i = 0; i < g->vertices; i++){
        aberto[i] = true;
    }

    while (existeAberto(g,aberto)){
        int u = menorDist(g,aberto,d);
        aberto[u] = false;
        ADJACENCIA *ad = g->adj[u].cab;
    
        while (ad){
            relaxa(g,d,p,u,ad->vertices);
            ad = ad -> peso;
        }
    }
    return(d);  
}

bool existeaberto(GRAFO *g, int *aberto){

    for (int i = 0; i < g->vertices; i++){
        if (aberto[i]) return true;
    return false;
        
    }
    
}

int menorDist(GRAFO *g, int *aberto, int *d){
    int i;
    for (i = 0; i < g->vertices; i++)
        if (aberto[i]) break;
        
    if (i == g) return -1;
    
    int menor = i;

    for ( i = 0; i < g->vertices; i++)
        if(aberto[i] && (d[menor]>d[i])) 
            menor = i; 
    return(menor);
    
    
}

void imprime (GRAFO *gr){
 
    //Total de arestas e vertices
    printf("Vertice: %d. Arestas: %d\n", gr->vertices, gr->arestas);

    //Para cada vertice fo grafo
    for (int i = 0; i < gr->vertices; i++){
        printf("\n Lista de Adjacencias do vertice %d\n cabeça ", i);//Imprime o numero do vertice
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

    GRAFO *gr = criaGrafo(6);

    
    criaAresta(gr,0,1,3);
    criaAresta(gr,1,3,1);
    criaAresta(gr,1,2,0);
    criaAresta(gr,2,4,2);
    criaAresta(gr,3,5,6);
    criaAresta(gr,3,4,4);
    criaAresta(gr,4,1,4);
    criaAresta(gr, 5,5,0);

    int *r = dijkstra(gr,0);

    for (int i = 0; i < gr->vertices; i++){
        printf("D(v0 -> v%d) = %d\n", i, r[i]);
    }
    
    imprime(gr);

    return 0;
}