#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

FilaPrioridade* criar_fila() {                
    FilaPrioridade* f = malloc(sizeof(FilaPrioridade));//Alaoca memoria dinamicamente para criação da fila
    f->inicio = NULL; // Define o inicio como NULL(Vazio)
    return f;//Retorna a fila criada
}

void inserir(FilaPrioridade* f, char nome[], int prioridade) {   
    No* novo = malloc(sizeof(No)); //Aloca memoria dinamicamente para um novo nó
    strcpy(novo->nome, nome);           // Copia o nome do paciente
    novo->prioridade = prioridade;      // Define a prioridade
    novo->prox = NULL; //Inicializa o ponteiro prox como NULL

    if (f->inicio == NULL || prioridade > f->inicio->prioridade) { //Se a lista estiver vazia ou o novo tem prioridade maior do que o primeiro 
        novo->prox = f->inicio;// O novo elemento aponta para o antigo inicio
        f->inicio = novo; //atualiza o primeiro elemento 
    } else {  // Caso contrario                               
        No* atual = f->inicio; // coloca o no atual como inicio 
        while (atual->prox != NULL && atual->prox->prioridade >= prioridade) { // Procura a posição correta para inserção mantendo a ordem de prioridade
            atual = atual->prox; // atualiza o ponteiro atual para o proximo nó 
        }
        novo->prox = atual->prox;// novo ponteiro aponta para o proximo nó
        atual->prox = novo; // Nó atual aponta para o novo
    }
}

void remover(FilaPrioridade* f) {                 
    if (f->inicio == NULL) { // Verifica se a fila esta vazia
        printf("Fila vazia!\n"); // Se a fila estiver vazia exibe essa mensagem para o usuario 
        return; // Sai da função 
    }
    No* temp = f->inicio; // Cria um ponteiro para guardar o endereço do elemento que sera removido 
    printf("Removendo paciente: %s (Prioridade %d)\n", temp->nome, temp->prioridade);// Exibe uma mensagem para o usuario falando qual elemento sera removido
    f->inicio = f->inicio->prox;//O proximo no vira o primeiro no da fila
    free(temp);//libera a memoria do no removido evitando memory leaks
}

void imprimir(FilaPrioridade* f) {                
    if (f->inicio == NULL) {// Verifica se a fila esta vazia
        printf("Fila vazia!\n");// Se a fila estiver vazia exibe essa mensagem para o usuario 
        return;// Sai da função
    }

    No* atual = f->inicio; // Começa apontando para o primeiro elemento da fila
    printf("\n--- Lista de Pacientes ---\n");
    while (atual != NULL) {// Percorre toda a fila para exibir seus elementos 
        printf("Nome: %s | Prioridade: %d\n", atual->nome, atual->prioridade);// exibe os elementos da fila para o usuario
        atual = atual->prox;//atualiza o ponteiro atual para o proximo elemeno da fila
    }
    printf("--------------------------\n");
}


void consultar(FilaPrioridade* f, char nome){
    if(f->inicio == NULL){ // Verifica se a fila esta vazia
        printf("Lista Vazia!\n");// Se a fila estiver vazia exibe essa mensagem para o usuario 
        return;// Sai da função
    }
    No* atual = f->inicio;//Começa do inicio a fila 

    while(atual != NULL){//Percorre toda a fila 
        if(strcmp(atual->nome, nome) == 0){//Compara o nome
            printf("Paciente encontrado!");//exibe se o paciente foi encontrado ou não
             printf("Nome: %s | Prioridade: %d\n", atual->nome, atual->prioridade);//Exibe os dados do paciente consultado
             return;//Sai da função 
        }
        atual = atual->prox;//Avança para o proximo no 
printf("Paciente nao encontrado");// Se não encontra exibe essa mensagem ao usuraio 
}
}