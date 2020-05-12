/*
  Ficheiro: funcoes.h
  Autor: Bruno Miguel da Silva Mendes ist195544/al95544
  Descricao: Ficheiro em que se declara todas as estruturas e se define as funcoes usadas.
*/

/*IMPORTS*/
#include "auxiliar.h"

/*VARIAVEIS GLOBAIS*/

/*Array que guarda todos os prudutos existentes; nao sofre ordenação*/
Produto produto[MAX_PROD];

/*Array que guarda todas as encomendas*/
Encomenda encomenda[MAX_ENC];

/*Array que guarda todos os ids dos produtos e a sua quantidade disponivel*/
Pid pid[MAX_PROD];

/*Variaveis que registam quantas encomendas e produtos existem*/
int size_p = 0;
int size_e = 0;

/*DECLARACAO DE FUNCOES*/

void novo_produto();
void adiciona_qtd();
void nova_encomenda();
void adiciona_encomenda();
void remove_qtd();
void remove_prod_encomenda();
void calcula_custo();
void altera_preco();
void atualiza_preco();
void lista_por_preco();
void lista_desc_qtd();
void lista_encomenda_nome();
void lista_maximo();

/*DEFENICAO DE FUNCOES*/

/*
  novo_produto: () -> ()
  Cria um novo produto e atualiza o indice de Pid's pid.
*/
void novo_produto(){
    /*Define o id do produto segundo ordem de insercao*/
    produto[size_p].id = size_p;
    
    getchar();
    get_string(produto[size_p].desc);
    scanf("%d:%d:%d",&produto[size_p].preco,&produto[size_p].peso,&produto[size_p].qtd);

    /*Atualiza o indice de produtos pid*/
    pid[size_p].id = size_p;
    pid[size_p].qtd = produto[size_p].qtd;

    printf("Novo produto %d.\n",size_p);

    /*Incrementa a variavel que resgista quantos produtos existem*/
    size_p++;
}

/*
  adiciona_qtd: () -> ()
  Adiciona quantidade de produto a um produto ja existente.
*/
void adiciona_qtd(){
    int tmp, id;
    
    scanf("%d:%d",&id,&tmp);

    /*Verifica se e possivel realizar a operacao*/
    if(id >= size_p){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",id);
        return;
    }

    /*Adiciona a quantidade inserida ao stock global e ao stock disponivel*/
    produto[id].qtd += tmp;
    pid[id].qtd += tmp;
}

/*
  nova_encomenda: () -> ()
  Cria uma nova encomenda.
*/
void nova_encomenda(){    
    /*Inicializa quantidade de produtos e peso da encomenda a zero*/
    encomenda[size_e].size = 0;
    encomenda[size_e].peso = 0;
    
    printf("Nova encomenda %d.\n",size_e);

    /*Incrementa a variavel que regista quantas encomendas existem*/
    size_e++;
}

/*
  adiciona_encomenda: () -> ()
  Adiciona um produto existente a uma encomenda existente, adicionando a quantidade
  passada no comando se o produto se econtrar na encomenda.
*/
void adiciona_encomenda(){
    int id_enc, id_prod, qtd, i, found;

    scanf("%d:%d:%d",&id_enc,&id_prod,&qtd);

    /*Verifica se a encomenda e o produto existem*/
    if(id_enc >= size_e){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",id_prod,id_enc);
        return;
    }

    else if(id_prod >= size_p){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",id_prod,id_enc);
        return;
    }

    /*Verifica se existe quantidade disponivel suficiente e se a encomenda nao excede o peso maximo*/
    if(qtd > pid[id_prod].qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",id_prod,id_enc);
        return;
    }

    else if(encomenda[id_enc].peso + (produto[id_prod].peso * qtd) > MAX_PESO){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",id_prod,id_enc);
        return;
    }

    pid[id_prod].qtd -= qtd;
    
    /*Procura o produto na encomenda*/
    found = 0;
    for(i=0; i<encomenda[id_enc].size; i++){
        if(encomenda[id_enc].pid[i].id == id_prod){
            /*Adiciona a quantidade ao produto ja existente e atualiza o peso*/
            encomenda[id_enc].pid[i].qtd += qtd;
            encomenda[id_enc].peso += (qtd * produto[id_prod].peso);

            found = 1;
            break;
        }
    }   

    /*Cria o produto na encomenda caso nao exista*/
    if(found == 0){
        encomenda[id_enc].pid[encomenda[id_enc].size].id = id_prod;
        encomenda[id_enc].pid[encomenda[id_enc].size].qtd = qtd;

        /*Atualiza o peso da encomenda*/
        encomenda[id_enc].peso += (qtd * produto[id_prod].peso);

        /*Incrementa a variavel que regista quantos produtos existem na encomenda*/
        encomenda[id_enc].size++;
    }
}

/*
  remove_qtd: () -> ()
  Adiciona um produto existente a uma encomenda existente, adicionando a quantidade
  passada no comando se o produto se econtrar na encomenda.
*/
void remove_qtd(){
    int id_prod, qtd;
    
    scanf("%d:%d",&id_prod,&qtd);

    /*Verifica se o produto existe e se existe quantidade suficiente de produto disponivel*/
    if(id_prod >= size_p){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",id_prod);
        return;
    }

    if(qtd > pid[id_prod].qtd){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,id_prod);
        return;
    }

    /*Retira a quantidade qtd a quantidade global e disponivel do produto*/
    produto[id_prod].qtd -= qtd;
    pid[id_prod].qtd -= qtd;
}

/*
  remove_prod_encomenda: () -> ()
  Remove um produto de uma encomenda caso o produto exista.
*/
void remove_prod_encomenda(){
    int id_enc, id_prod, i;
    
    scanf("%d:%d",&id_enc,&id_prod);

    /*Verifica se a encomenda e o produto existem*/
    if(id_enc >= size_e){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",id_prod,id_enc);
        return;
    }

    if(id_prod >= size_p){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",id_prod,id_enc);
        return;
    }

    /*Procura o produto na encomenda*/
    for(i=0; i<encomenda[id_enc].size; i++){
        if(encomenda[id_enc].pid[i].id == id_prod){
            /*Atualiza o preco*/
            encomenda[id_enc].peso -= encomenda[id_enc].pid[i].qtd * produto[id_prod].peso;

            /*Atualiza a quantidade de produto disponivel*/
            pid[id_prod].qtd += encomenda[id_enc].pid[i].qtd;

            /*Troca o produto removido com o ultimo elemento do vetor*/            
            troca(&encomenda[id_enc].pid[i],&encomenda[id_enc].pid[encomenda[id_enc].size - 1]);
            
            /*Diminui o tamanho do vetor*/
            encomenda[id_enc].size--;

            break;
        }
    }
}

/*
  calcula_custo: () -> ()
  Calcula o preco de uma encomenda.
*/
void calcula_custo(){
    int id_enc, preco = 0, i;

    scanf("%d",&id_enc);

    /*Verifica se a encomenda existe*/
    if(id_enc >= size_e){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",id_enc);
        return;
    }

    /*Percorre todos os produtos da encomenda e calcula o preco final da encomenda*/
    for(i=0; i<encomenda[id_enc].size; i++){
        preco += produto[encomenda[id_enc].pid[i].id].preco * encomenda[id_enc].pid[i].qtd;
    }

    printf("Custo da encomenda %d %d.\n",id_enc,preco);
}

/*
  altera_preco: () -> ()
  Altera o preco de um produto.
*/
void altera_preco(){
    int id_prod, preco;

    scanf("%d:%d",&id_prod,&preco);

    /*Verifica se o produto existe*/
    if(id_prod >= size_p){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",id_prod);
        return;
    }

    /*Atualiza o preco do produto*/
    produto[id_prod].preco = preco;
}

/*
  lista_por_preco: () -> ()
  Imprime a descricao, preco e quantidade disponivel de todos os produtos existentes por ordem de preco. 
  Caso tenham o mesmo preco o quem tem id menor aparece primeiro.
*/
void lista_por_preco(){    
    int i;

    /*Cria vetor copia que fica sujeito a uma ordenacao destrutiva*/
    Pid copia[MAX_PROD];

    puts("Produtos");

    /*Cria o vetor copia*/
    for(i=0; i<size_p; i++){
        copia[i].id = pid[i].id;
        copia[i].qtd = pid[i].qtd;
    }

    ordena_por_preco(copia, 0, size_p-1, produto);

    imprime_vetor(copia, size_p, produto);
}

/*
  lista_desc_qtd: () -> ()
  Imprime a descricao de um produto e a quantidade desse produto numa encomenda.
*/
void lista_desc_qtd(){
    int id_enc, id_prod, i, found = 0;

    scanf("%d:%d",&id_enc,&id_prod);

    /*Verifica se a encomenda e o produto existem*/
    if(id_enc >= size_e){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_enc);
        return;
    }

    else if(id_prod >= size_p){
        printf("Impossivel listar produto %d. Produto inexistente.\n",id_prod);
        return;
    }

    /*Procura o produto na encomenda*/
    for(i=0; i<encomenda[id_enc].size; i++){
        if(encomenda[id_enc].pid[i].id == id_prod){
            printf("%s %d.\n",produto[id_prod].desc,encomenda[id_enc].pid[i].qtd);
            found = 1;
            break;
        }
    } 

    /*Caso o produto nao exista imprime a descricao do produto com quantidade 0*/
    if(found == 0){
        printf("%s 0.\n",produto[id_prod].desc);
    }
}

/*
  lista_encomenda_nome: () -> ()
  Imprime a descricao, preco e quantidade disponivel dos produtos existentes numa encomenda
  por ordem de alfabetica da sua descricao.
*/
void lista_encomenda_nome(){
    int id_enc, i;

    /*Cria vetor copia que fica sujeito a uma ordenacao destrutiva*/
    Pid copia[MAX_PROD];

    scanf("%d",&id_enc);

    /*Verifica se a encomenda existe*/
    if(id_enc >= size_e){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_enc);
        return;
    }

    printf("Encomenda %d\n",id_enc);

    /*Copia o pid da encomenda para o vetor copia*/
    for(i=0; i<encomenda[id_enc].size; i++){
        copia[i].id = encomenda[id_enc].pid[i].id;
        copia[i].qtd = encomenda[id_enc].pid[i].qtd;
    }

    ordena_por_nome(copia, 0, encomenda[id_enc].size-1, produto);

    imprime_vetor(copia, encomenda[id_enc].size, produto);
}

/*
  lista_maximo: () -> ()
  Imprime o id do produto, o id da encomenda em qual se encontra em maior quantade 
  e a quantidade maxima desse produto numa encomenda.
*/
void lista_maximo(){
    int id_prod, i, j, max = 0, ide = 0;

    scanf("%d",&id_prod);

    /*Verifica se o produto existe*/
    if(id_prod >= size_p){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",id_prod);
        return;
    }

    /*Procura o produto em todas as encomendas*/
    for(i=0; i<size_e; i++){
        for(j=encomenda[i].size - 1; j>=0; j--){  
            if(encomenda[i].pid[j].id == id_prod && encomenda[i].pid[j].qtd > max){
                /*Atualiza quantidade maxima*/
                max = encomenda[i].pid[j].qtd;

                /*Guarda a encomenda em que o maximo se regista*/
                ide = i;
            }
        }
    }

    /*Se o produto nao existir em nenhuma encomenda nao imprime nada*/
    if(max != 0)
        printf("Maximo produto %d %d %d.\n",id_prod,ide,max);
}
