# Atividade-Fila-Prioridade
Repositório atividade prática 02 

## Integrantes 
**Pedro Lucas**
**Tiago Lara**
**João Guilherme**
**Matheus Nunes**

# Projeto: Fila de Prioridade (Simulação Hospitalar)

Este projeto implementa uma estrutura de dados de **Fila Ordenada por Prioridade** utilizando listas simplesmente encadeadas em linguagem C. O objetivo é simular um sistema de atendimento hospitalar onde a prioridade (maior valor numérico) determina a ordem de atendimento do cliente.

A regra principal de funcionamento é: **pacientes com maior valor no campo prioridade são sempre posicionados mais próximos ao início da fila para serem atendidos primeiro.**

## 1. Estruturas de Dados (`fila.h`)

O arquivo de cabeçalho define as estruturas e o contrato das funções.

```c
#ifndef FILA_H // Comando utilizado para evitar que o arquivo seja implementado mais de uma vez
#define FILA_H

typedef struct No { //Estrutura do nó da fila (Pacientes)
    char nome[50];   // Definição do nome do paciente        
    int prioridade;  // Definição da prioridade do paciente (Maior valor = Maior prioridade)       
    struct No* prox;  // Ponteiro para o proximo elemento da fila       
} No;

typedef struct { //Estrutura da fila de prioridade
    No* inicio; // Ponteiro para o primeiro elemento da fila (o mais prioritário)            
} FilaPrioridade;


FilaPrioridade* criar_fila();
void inserir(FilaPrioridade* f, char nome[], int prioridade);
void remover(FilaPrioridade* f);
void imprimir(FilaPrioridade* f);
void consultar(FilaPrioridade* f, char nome);

#endif // Finaliza o cabeçalho
```



## 2. Implementação e Lógica Funcional (fila.c)
Este arquivo contém a lógica das funções, com destaque para a função inserir, que garante a ordenação da fila.]

# Lógica:

**Busca Ordenada:** Ao inserir um novo paciente, a função percorre a lista (while) e insere o novo nó antes do primeiro paciente que possui uma prioridade estritamente menor.

**Prioridade no Início**: Se a prioridade do novo paciente for maior que a do primeiro da fila, o novo paciente se torna o novo inicio.

As funções criar_fila, remover (que sempre remove o inicio) e imprimir complementam a funcionalidade básica da estrutura.

```c
void inserir(FilaPrioridade* f, char nome[], int prioridade) {   
    No* novo = malloc(sizeof(No)); //Aloca memoria dinamicamente para um novo nó
    strcpy(novo->nome, nome);           // Copia o nome do paciente
    novo->prioridade = prioridade;      // Define a prioridade
    novo->prox = NULL; //Inicializa o ponteiro prox como NULL

    // Se a lista estiver vazia ou o novo tem prioridade maior do que o primeiro 
    if (f->inicio == NULL || prioridade > f->inicio->prioridade) { 
        novo->prox = f->inicio;// O novo elemento aponta para o antigo inicio
        f->inicio = novo; //atualiza o primeiro elemento 
    } else {  // Caso contrario                               
        No* atual = f->inicio; // coloca o no atual como inicio 
        // Procura a posição correta para inserção mantendo a ordem de prioridade
        while (atual->prox != NULL && atual->prox->prioridade >= prioridade) { 
            atual = atual->prox; // atualiza o ponteiro atual para o proximo nó 
        }
        novo->prox = atual->prox;// novo ponteiro aponta para o proximo nó
        atual->prox = novo; // o nó atual aponta para o novo nó 
    }
}
```

## 3. Programa Principal e Interface (main.c)
Este arquivo contém o menu de interação do usuário e controla o fluxo do programa.
O menu permite ao usuário testar todas as operações da fila.

```c
include <stdio.h>       // Biblioteca padrão de entrada e saída
#include <stdlib.h>      // Biblioteca de funções de sistema
#include <string.h>      // Biblioteca para manipular strings
#include "fila.c"        // Inclui o arquivo com as funções da fila

int main() {
    FilaPrioridade* fila = criar_fila();  // Cria uma nova fila de pacientes
    int opcao;                            // Guarda a opção do menu
    char nome[50];                        // Guarda o nome do paciente
    int prioridade;                       // Guarda a prioridade do paciente

    do {
        // Exibe o menu principal
        printf("\n===== MENU FILA DE PACIENTES =====\n");
        printf("1 - Inserir paciente\n");
        printf("2 - Remover paciente de maior prioridade\n");
        printf("3 - Mostrar lista de pacientes\n");
        printf("4 - Consultar paciente por nome\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);              // Lê a opção digitada
        getchar();                        // Limpa o buffer do teclado (CRUCIAL após scanf)

        // Escolhe a ação de acordo com a opção
        switch (opcao) {
            case 1:   // Inserir novo paciente
                printf("Digite o nome do paciente: ");
                fgets(nome, sizeof(nome), stdin);     // Lê o nome
                nome[strcspn(nome, "\n")] = '\0';     // Remove o '\n' do final
                printf("Digite a prioridade: ");
                scanf("%d", &prioridade);             // Lê a prioridade
                inserir(fila, nome, prioridade);      // Chama função de inserção
                printf("Paciente inserido com sucesso!\n");
                break;

            case 2:   // Remover paciente
                remover(fila);                        // Remove o de maior prioridade
                break;

            case 3:   // Mostrar fila completa
                imprimir(fila);                       // Exibe todos os pacientes
                break;

            case 4:   // Consultar paciente
                printf("Digite o nome do paciente para consultar: ");
                fgets(nome, sizeof(nome), stdin);     // Lê o nome
                nome[strcspn(nome, "\n")] = '\0';     // Remove o '\n'
                consultar(fila, nome);                // Chama a função consultar
                break;

            case 0:   // Encerrar programa
                printf("Encerrando o programa...\n");
                // TODO: Adicionar lógica para liberar toda a memória da lista antes de sair.
                break;

            default:  // Caso o usuário digite opção inválida
                printf("Opcao invalida!\n");
                break;
        }

    } while (opcao != 0);   // Repete até o usuário escolher sair

    return 0;               // Finaliza o programa
}
```

