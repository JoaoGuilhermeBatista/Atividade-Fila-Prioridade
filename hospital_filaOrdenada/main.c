#include <stdio.h>       // Biblioteca padrão de entrada e saída
#include <stdlib.h>      // Biblioteca de funções de sistema
#include <string.h>      // Biblioteca para manipular strings
#include "fila.h"        // Inclui o arquivo com as funções da fila e do grafo

int main() {
    FilaPrioridade* fila = criar_fila();  // Cria uma nova fila de pacientes
    if (fila == NULL) { //Verifica se a fila foi criada corretamente
        return 1; //Encerra o programa em caso de erro de memória
    }

    GrafoHospital grafo;                 //Estrutura para o grafo dos setores
    inicializar_grafo_hospital(&grafo);  //Inicializa as ligações entre os setores

    int opcao;                            // Guarda a opção do menu
    char nome[50];                        // Guarda o nome do paciente
    int prioridade;                       // Guarda a prioridade do paciente
    int setor;                            // Guarda o setor atual do paciente

    do {
        // Exibe o menu principal
        printf("\n===== MENU FILA DE PACIENTES =====\n");
        printf("1 - Inserir paciente\n");
        printf("2 - Remover paciente de maior prioridade\n");
        printf("3 - Mostrar lista de pacientes\n");
        printf("4 - Consultar paciente por nome\n");
        printf("5 - Desfazer ultima remocao\n");
        printf("6 - Relatorio estatistico\n");
        printf("7 - Teste automatico\n");
        printf("8 - Simular encaminhamento entre setores (BFS/DFS)\n");
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

                printf("Digite a prioridade (inteiro): ");
                scanf("%d", &prioridade);             // Lê a prioridade
                getchar();                            //Limpa o buffer apos ler a prioridade

                // Mostra os setores disponíveis
                mostrar_setores();
                printf("Digite o codigo do setor atual do paciente: ");
                scanf("%d", &setor);                  //Lê o código do setor
                getchar();                            //Limpa o buffer

                // Validação simples do setor
                if (setor < 0 || setor >= NUM_SETORES) { //Se o setor for inválido
                    printf("Setor invalido! Usando setor Triagem por padrao.\n");
                    setor = SETOR_TRIAGEM; //Define Triagem como padrão
                }

                inserir(fila, nome, prioridade, setor);      // Chama função de inserção
                // Mensagem detalhada já é exibida dentro da função inserir
                break;

            case 2:   // Remover paciente
                remover(fila);                        // Remove o de maior prioridade
                // A função remover já exibe mensagens de feedback
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

            case 5:   // Desfazer a última remoção
                desfazer_ultima_remocao(fila);        // Chama a função para desfazer
                break;

            case 6:   // Exibir relatório estatístico
                relatorio(fila);                      // Mostra dados sobre fila e atendimentos
                break;

            case 7:   // Teste automático para debug e demonstração
                teste_automatico(fila);               // Executa a rotina de teste automático
                break;

            case 8: { // Simular encaminhamento entre setores com BFS e DFS
                int origem, destino;

                printf("\nEscolha o setor de origem:\n");
                mostrar_setores();                    //Mostra a lista de setores
                printf("Digite o codigo do setor de origem: ");
                scanf("%d", &origem);
                getchar();

                printf("\nEscolha o setor de destino:\n");
                mostrar_setores();                    //Mostra a lista novamente
                printf("Digite o codigo do setor de destino: ");
                scanf("%d", &destino);
                getchar();

                //Validação simples dos índices
                if (origem < 0 || origem >= NUM_SETORES ||
                    destino < 0 || destino >= NUM_SETORES) {
                    printf("Setor de origem ou destino invalido!\n");
                } else {
                    bfs_caminho(&grafo, origem, destino); //Mostra o caminho minimo entre os setores
                    dfs_visita(&grafo, origem);           //Mostra uma ordem de visita em profundidade
                }

                break;
            }

            case 0:   // Encerrar programa
                printf("Encerrando o programa...\n");
                break;

            default:  // Caso o usuário digite opção inválida
                printf("Opcao invalida!\n");
                break;
        }

    } while (opcao != 0);   // Repete até o usuário escolher sair

    destruir_fila(fila);    // Libera toda a memoria alocada antes de encerrar
    return 0;               // Finaliza o programa
}