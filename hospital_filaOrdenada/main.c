#include <stdio.h>       // Biblioteca padrão de entrada e saída
#include <stdlib.h>      // Biblioteca de funções de sistema
#include <string.h>      // Biblioteca para manipular strings
#include "fila.h"       // Inclui o arquivo com as funções da fila

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
        getchar();                        // Limpa o buffer do teclado

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
                break;

            default:  // Caso o usuário digite opção inválida
                printf("Opcao invalida!\n");
                break;
        }

    } while (opcao != 0);   // Repete até o usuário escolher sair

    return 0;               // Finaliza o programa
}