/*
  Ficheiro: estruturas.h
  Autor: Bruno Miguel da Silva Mendes ist195544/al95544
  Descricao: Ficheiro em que se definem todas as estruturas e constantes
*/

/*DEFENICAO DE CONSTANTES*/
#define STR_MAX 64
#define MAX_PROD 10000
#define MAX_ENC 500
#define MAX_PESO 200

/*ESTRUTURAS*/

/*
  Produto: int, char*, int, int, int
  Representa um produto constituida por id, descricao, preco, peso e quantidade.
*/
typedef struct {
    int id;
    char desc[STR_MAX];
    int preco;
    int peso;
    int qtd;
} Produto;

/*
  Pid: int, int
  Representa um pseudo apontador para um produto em que guarda a quantidade
  do produto cujo id esta guardado na variavel id.
*/
typedef struct {
    int id;
    int qtd;
} Pid;

/*
  Encomenda: int, int, Pid*
  Representa uma encomenda constituida por peso, quantidade de produtos na encomenda e um
  vetor de pseudo apontadores para produtos que constituem esta encomenda.
*/
typedef struct {
    int peso;
    int size;
    Pid pid[MAX_PROD];
} Encomenda;
