/*
  Ficheiro: projeto.h
  Autor: Bruno Miguel da Silva Mendes ist195544/al95544
  Descricao: Ponto de entrada para o projeto de IAED19/20
*/

/*IMPORTS*/
#include "funcoes.h"

/*FUNCAO MAIN*/

/*
  main: () -> int
  Primeira funcao a ser executada, trata de reconhecer o comando presente na input
*/
int main(){
    /*Variavel que contem o comando a ser executado*/
    char op;

    /*Le carateres da stdin ate encontrar o caso terminal
      ou um comando a executar*/
    while((op = getchar()) != 'x'){
        switch(op){
            case('a'):
                novo_produto();
                break;

            case('q'):
                adiciona_qtd();
                break;

            case('N'):
                nova_encomenda();
                break;

            case('A'):
                adiciona_encomenda();
                break;

            case('r'):
                remove_qtd();
                break;

            case('R'):
                remove_prod_encomenda();
                break;

            case('C'):
                calcula_custo();
                break;

            case('p'):
                altera_preco();
                break;

            case('E'):
                lista_desc_qtd();
                break;
            
            case('m'): 
                lista_maximo();
                break;

            case('l'):
                lista_por_preco();
                break;

            case('L'):
                lista_encomenda_nome();
                break;
        }
    }
    return 0;
}
