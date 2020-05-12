/*
  Ficheiro: auxiliar.h
  Autor: Bruno Miguel da Silva Mendes ist195544/al95544
  Descricao: Ficheiro em que se funcoes auxiliares.
*/

/*IMPORTS*/
#include <stdio.h>
#include <strings.h>
#include "estruturas.h"

/*VARIAVEIS GLOBAIS*/

/*Vetor auxiliar*/
Pid aux[MAX_PROD];

/*DECLARACAO DE FUNCOES*/

int get_string(char*);
void merge_por_preco(Pid*, int, int, int, Produto*);
void ordena_por_preco(Pid*, int, int, Produto*);
void merge_por_nome(Pid*, int, int, int, Produto*);
void ordena_por_nome(Pid*, int, int, Produto*);
void troca(Pid*, Pid*);

/*DEFENICAO DE FUNCOES*/

/*
  get_string: char* -> int
  Le uma string da stdin ate encontrar o carater ':' ou exceder o 
  limite de carateres lidos STR_MAX; Retorna o numero de carateres lidos 
*/
int get_string(char* arg){
    char c;
    int i = 0;
  
    c = getchar();
    while(c != ':' && i < STR_MAX - 1){
        arg[i] = c;
        i++;
        c = getchar();
    }

    /*Limpa a stdin ate encomtrar ':'*/
    while(c != ':')
        c = getchar();

    /*Termina a string com null byte*/
    arg[i] = '\0';

    return i;
}

/*
  merge_por_preco: (Pid*, int, int, int, Produto*) -> ()
  Funcao auxiliar do algoritmo merge sort. Ordena o vetor copia segundo o preco do produto 
  para qual cada Pid de copia aponta.
*/
void merge_por_preco(Pid* copia, int baixo, int m, int cima, Produto* produto){
    int i,j,k;

    /*Constroi o vetor auxiliar*/
    for(i=m+1; i>baixo; i--)
        aux[i-1] = copia[i-1];
    
    for(j=m; j<cima; j++) /*Coloca j no limite superior do subvetor*/
        aux[cima+m-j] = copia[j+1];

    /*Escolhe os elemntos das pontas para ordenar o vetor copia*/
    for(k=baixo; k<=cima; k++){
        if(produto[aux[j].id].preco < produto[aux[i].id].preco)
            copia[k] = aux[j--];
        
        /*Caso de desempate: o menor id vem primeiro*/
        else if(produto[aux[j].id].preco == produto[aux[i].id].preco && aux[j].id < aux[i].id)
            copia[k] = aux[j--];

        else
            copia[k] = aux[i++];
    }
}

/*
  ordena_por_preco: (Pid*, int, int, Produto*) -> ()
  Ordena o vetor copia segundo o preco do produto para qual cada Pid de copia aponta segundo
  o procedimento de merge.
*/
void ordena_por_preco(Pid* copia, int baixo, int cima, Produto* produto){
    int m = (baixo+cima) / 2;

    if(cima <= baixo)
        return;

    /*Parte o vetor copia a meio recursivamente*/
    ordena_por_preco(copia, baixo, m, produto);
    ordena_por_preco(copia, m+1, cima, produto);

    /*Ordena o subvetor copia[baixo:cima]*/
    merge_por_preco(copia, baixo, m, cima, produto);
}

/*
  merge_por_nome: (Pid*, int, int, int, Produto*) -> ()
  Funcao auxiliar do algoritmo merge sort. Ordena o vetor copia segundo a descricao do produto 
  para qual cada Pid de copia aponta.
*/
void merge_por_nome(Pid* copia, int baixo, int m, int cima, Produto* produto){
    int i,j,k;

    /*Constroi o vetor auxiliar*/
    for(i=m+1; i>baixo; i--)
        aux[i-1] = copia[i-1];

    for(j=m; j<cima; j++)
        aux[cima+m-j] = copia[j+1];

    /*Escolhe os elemntos das pontas para ordenar o vetor copia*/
    for(k=baixo; k<=cima; k++){
        if(strcasecmp(produto[aux[j].id].desc, produto[aux[i].id].desc) < 0)
            copia[k] = aux[j--];

        else if(strcasecmp(produto[aux[j].id].desc, produto[aux[i].id].desc) == 0 && aux[j].id < aux[i].id)
            copia[k] = aux[j--];

        else
            copia[k] = aux[i++];
    }
}

/*
  ordena_por_nome: (Pid*, int, int, Produto*) -> ()
  Ordena o vetor copia segundo a descricao para qual cada Pid de copia aponta segundo
  o procedimento de merge.
*/
void ordena_por_nome(Pid* copia, int baixo, int cima, Produto* produto){
    int m = (baixo+cima) / 2;

    if(cima <= baixo)
        return;

    /*Parte o vetor copia a meio recursivamente*/
    ordena_por_nome(copia, baixo, m, produto);
    ordena_por_nome(copia, m+1, cima, produto);

    /*Ordena o subvetor copia[baixo:cima]*/
    merge_por_nome(copia, baixo, m, cima, produto);
}

/*
  troca: (Pid*, Pid*) -> ()
  Troca os 2 Pid's passados como argumento dentro de um array de Pid's.
*/
void troca(Pid* a, Pid* b){
    Pid t = *a;
    *a = *b;
    *b = t;
}

/*
  imprime_vetor: (Pid*, int, Produto*) -> ()
  Imprime a descricao, o preco e a quantidade de produtos referenciados por um vetor de Pid
*/
void imprime_vetor(Pid* pid, int size, Produto* produto){
    int i;

    for(i=0; i<size; i++){
        printf("* %s %d %d\n",produto[pid[i].id].desc,produto[pid[i].id].preco,pid[i].qtd);
    }
}