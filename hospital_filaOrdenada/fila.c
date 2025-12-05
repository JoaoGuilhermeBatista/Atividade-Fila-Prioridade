#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

// Array com os nomes dos setores para exibição
const char* nomesSetores[NUM_SETORES] = {
    "Triagem",
    "Clinica Geral",
    "Ortopedia",
    "Pediatria",
    "Cardiologia",
    "Exames",
    "Internacao"
};

// Funções auxiliares internas (static) para pilha de histórico

static void empilhar_historico(FilaPrioridade* f, char nome[], int prioridade, int setor) {
    if (f == NULL) { // Valida se a fila existe
        return; //Se a fila não existe, não há histórico para empilhar
    }

    NoHistorico* novo = (NoHistorico*) malloc(sizeof(NoHistorico)); //Aloca memoria dinamicamente para um novo nó da pilha
    if (novo == NULL) { //Verifica se a alocação falhou
        printf("Erro de memoria ao salvar historico!\n"); //Mensagem de erro para o usuario
        f->status = STATUS_ERRO_MEMORIA; //Atualiza o status da operação como erro de memoria
        return; //Sai da função
    }

    strcpy(novo->nome, nome);      //Copia o nome do paciente removido
    novo->prioridade = prioridade; //Guarda a prioridade original do paciente
    novo->setor = setor;           //Guarda o setor original do paciente
    novo->prox = f->topoHist;      //Novo nó aponta para o antigo topo da pilha
    f->topoHist = novo;            //Atualiza o topo da pilha para o novo nó
    // Não altera status de sucesso aqui para não sobrescrever o da remoção principal
}

static int desempilhar_historico(FilaPrioridade* f, char nome[], int* prioridade, int* setor) {
    if (f == NULL || f->topoHist == NULL) { //Verifica se a pilha de histórico está vazia ou fila inexistente
        return 0; //Retorna 0 indicando falha ao desempilhar
    }

    NoHistorico* temp = f->topoHist; //Cria ponteiro temporário para o topo da pilha
    f->topoHist = temp->prox;        //Atualiza o topo para o próximo elemento
    strcpy(nome, temp->nome);        //Recupera o nome do paciente
    *prioridade = temp->prioridade;  //Recupera a prioridade do paciente
    *setor = temp->setor;            //Recupera o setor do paciente
    free(temp);                      //Libera a memoria do nó desempilhado
    return 1;                        //Retorna 1 indicando sucesso
}

FilaPrioridade* criar_fila() {                
    FilaPrioridade* f = (FilaPrioridade*) malloc(sizeof(FilaPrioridade));//Aloca memoria dinamicamente para criação da fila
    if (f == NULL) { //Verifica se a alocação falhou
        printf("Erro ao criar fila (memoria insuficiente).\n"); //Mensagem de erro para o usuario
        return NULL; //Retorna NULL indicando falha na criação
    }

    f->inicio = NULL; // Define o inicio como NULL(Vazio)
    f->topoHist = NULL; //Inicializa a pilha de histórico como vazia
    f->tamanho = 0; //Inicia o tamanho da fila como zero
    f->totalAtendidos = 0; //Inicia o total de atendidos como zero
    f->somaPriorAtendidos = 0; //Inicia a soma das prioridades atendidas como zero
    f->status = STATUS_SUCESSO; //Inicializa o status como sucesso
    return f;//Retorna a fila criada
}

void inserir(FilaPrioridade* f, char nome[], int prioridade, int setor) {   
    if (f == NULL) { //Valida se a fila foi criada corretamente
        printf("Fila nao inicializada!\n"); //Informa o usuario sobre o erro
        return; //Sai da função
    }

    No* novo = (No*) malloc(sizeof(No)); //Aloca memoria dinamicamente para um novo nó
    if (novo == NULL) { //Verifica se a alocação falhou
        printf("Erro de memoria ao inserir paciente!\n"); //Mensagem de erro
        f->status = STATUS_ERRO_MEMORIA; //Atualiza o status da ultima operação
        return; //Sai da função
    }

    strcpy(novo->nome, nome);           // Copia o nome do paciente
    novo->prioridade = prioridade;      // Define a prioridade
    novo->setor = setor;                // Define o setor atual do paciente
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

    f->tamanho++; //Incrementa o tamanho da fila após inserção bem sucedida
    f->status = STATUS_SUCESSO; //Atualiza o status da ultima operação como sucesso
    printf("Paciente inserido: %s (Prioridade %d, Setor %s)\n", nome, prioridade, nomesSetores[setor]); //Feedback claro para o usuario
}

void remover(FilaPrioridade* f) {                 
    if (f == NULL) { //Valida se a fila existe
        printf("Fila nao inicializada!\n"); //Mensagem de erro
        return; //Sai da função
    }

    if (f->inicio == NULL) { // Verifica se a fila esta vazia
        printf("Fila vazia! Nao ha pacientes para remover.\n"); //Mensagem clara de underflow
        f->status = STATUS_FILA_VAZIA; //Atualiza o status para fila vazia
        return; // Sai da função 
    }

    No* temp = f->inicio; // Cria um ponteiro para guardar o endereço do elemento que sera removido 
    printf("Removendo paciente: %s (Prioridade %d, Setor %s)\n", temp->nome, temp->prioridade, nomesSetores[temp->setor]);// Exibe uma mensagem para o usuario falando qual elemento sera removido

    // Salva a remoção na pilha de histórico para permitir desfazer
    empilhar_historico(f, temp->nome, temp->prioridade, temp->setor); //Empilha o paciente removido na pilha de histórico

    f->inicio = f->inicio->prox;//O proximo no vira o primeiro no da fila
    f->tamanho--; //Decrementa o tamanho da fila
    f->totalAtendidos++; //Incrementa o total de pacientes atendidos
    f->somaPriorAtendidos += temp->prioridade; //Soma a prioridade do paciente atendido para estatísticas

    free(temp);//libera a memoria do no removido evitando memory leaks
    f->status = STATUS_SUCESSO; //Atualiza o status da ultima operação
}

void imprimir(FilaPrioridade* f) {                
    if (f == NULL) { //Valida se a fila foi criada
        printf("Fila nao inicializada!\n"); //Mensagem para o usuario
        return; //Sai da função
    }

    if (f->inicio == NULL) {// Verifica se a fila esta vazia
        printf("Fila vazia!\n");// Se a fila estiver vazia exibe essa mensagem para o usuario 
        f->status = STATUS_FILA_VAZIA; //Atualiza o status para fila vazia
        return;// Sai da função
    }

    No* atual = f->inicio; // Começa apontando para o primeiro elemento da fila
    printf("\n--- Lista de Pacientes ---\n");
    while (atual != NULL) {// Percorre toda a fila para exibir seus elementos 
        printf("Nome: %s | Prioridade: %d | Setor: %s\n",
               atual->nome, atual->prioridade, nomesSetores[atual->setor]);// exibe os elementos da fila para o usuario
        atual = atual->prox;//atualiza o ponteiro atual para o proximo elemeno da fila
    }
    printf("Total de pacientes na fila: %d\n", f->tamanho); //Exibe o total atual de pacientes
    printf("--------------------------\n");
    f->status = STATUS_SUCESSO; //Atualiza o status como sucesso
}


void consultar(FilaPrioridade* f, char nome[]){
    if (f == NULL) { // Valida se a fila foi criada
        printf("Fila nao inicializada!\n");// Mensagem de erro para o usuario 
        return;// Sai da função
    }

    if(f->inicio == NULL){ // Verifica se a fila esta vazia
        printf("Lista Vazia!\n");// Se a fila estiver vazia exibe essa mensagem para o usuario 
        f->status = STATUS_FILA_VAZIA; //Atualiza o status como fila vazia
        return;// Sai da função
    }
    No* atual = f->inicio;//Começa do inicio a fila 

    while(atual != NULL){//Percorre toda a fila 
        if(strcmp(atual->nome, nome) == 0){//Compara o nome
            printf("Paciente encontrado!\n");//exibe se o paciente foi encontrado ou não
            printf("Nome: %s | Prioridade: %d | Setor: %s\n",
                   atual->nome, atual->prioridade, nomesSetores[atual->setor]);//Exibe os dados do paciente consultado
            f->status = STATUS_SUCESSO; //Atualiza o status para sucesso
            return;//Sai da função 
        }
        atual = atual->prox;//Avança para o proximo no 
    }

    printf("Paciente nao encontrado.\n");// Se não encontra exibe essa mensagem ao usuraio 
    f->status = STATUS_PACIENTE_NAO_ENCONTRADO; //Atualiza o status de consulta como não encontrado
}

// Função para desfazer a última remoção realizada
void desfazer_ultima_remocao(FilaPrioridade* f) {
    if (f == NULL) { //Valida a existência da fila
        printf("Fila nao inicializada!\n"); //Mensagem de erro
        return; //Sai da função
    }

    char nome[50]; //Variável para recuperar o nome do paciente
    int prioridade; //Variável para recuperar a prioridade do paciente
    int setor;      //Variável para recuperar o setor do paciente

    if (!desempilhar_historico(f, nome, &prioridade, &setor)) { //Tenta desempilhar o historico
        printf("Nao ha remocoes para desfazer.\n"); //Mensagem para o usuario
        f->status = STATUS_FILA_VAZIA; //Status indica que não há o que desfazer
        return; //Sai da função
    }

    // Ao desfazer a remoção, devolve o paciente para a fila
    inserir(f, nome, prioridade, setor); //Reinsere o paciente com sua prioridade e setor original

    // Ajusta as estatísticas, pois o atendimento foi "anulado"
    if (f->totalAtendidos > 0) { //Garante que não fique negativo
        f->totalAtendidos--; //Decrementa o total de atendidos
        f->somaPriorAtendidos -= prioridade; //Remove a prioridade do somatorio
    }

    printf("Operacao desfeita! Paciente %s voltou para a fila no setor %s.\n", nome, nomesSetores[setor]); //Feedback para o usuario
    f->status = STATUS_SUCESSO; //Status de sucesso após o desfazer
}

// Função para exibir um relatório estatístico simples
void relatorio(FilaPrioridade* f) {
    if (f == NULL) { //Valida a existência da fila
        printf("Fila nao inicializada!\n"); //Mensagem para o usuario
        return; //Sai da função
    }

    printf("\n===== RELATORIO DA FILA =====\n");
    printf("Pacientes na fila: %d\n", f->tamanho); //Mostra a quantidade atual na fila
    printf("Pacientes atendidos: %d\n", f->totalAtendidos); //Mostra o total já atendido

    if (f->totalAtendidos > 0) { //Verifica se houve algum atendimento
        double media = (double) f->somaPriorAtendidos / f->totalAtendidos; //Calcula a media de prioridade
        printf("Media de prioridade dos pacientes atendidos: %.2f\n", media); //Exibe a média
    } else {
        printf("Ainda nao ha pacientes atendidos para calcular a media de prioridade.\n"); //Mensagem caso não haja atendimentos
    }

    // Relatório simples de distribuição de prioridades ainda na fila
    if (f->inicio != NULL) { //Verifica se há pacientes na fila
        int contPrioAlta = 0; //Contador para prioridades altas
        int contPrioMedia = 0; //Contador para prioridades medias
        int contPrioBaixa = 0; //Contador para prioridades baixas

        No* atual = f->inicio; //Começa pelo inicio da fila
        while (atual != NULL) { //Percorre toda a fila
            if (atual->prioridade >= 8) { //Classifica como prioridade alta
                contPrioAlta++;
            } else if (atual->prioridade >= 4) { //Classifica como prioridade média
                contPrioMedia++;
            } else { //Demais valores são considerados prioridade baixa
                contPrioBaixa++;
            }
            atual = atual->prox; //Avança para o próximo nó
        }

        printf("\nDistribuicao de prioridades na fila:\n");
        printf("Alta   (>= 8): %d pacientes\n", contPrioAlta);
        printf("Media  (4 a 7): %d pacientes\n", contPrioMedia);
        printf("Baixa  (<= 3): %d pacientes\n", contPrioBaixa);
    }

    printf("=============================\n");
    f->status = STATUS_SUCESSO; //Atualiza o status como sucesso
}

// Função de teste automático para auxiliar no debug
void teste_automatico(FilaPrioridade* f) {
    if (f == NULL) { //Valida a existência da fila
        printf("Fila nao inicializada!\n"); //Mensagem para o usuario
        return; //Sai da função
    }

    printf("\n=== Teste automatico iniciado ===\n");
    inserir(f, "Maria", 5, SETOR_CLINICA_GERAL);   //Insere paciente de teste
    inserir(f, "Joao", 9, SETOR_TRIAGEM);          //Insere paciente de teste
    inserir(f, "Ana", 3, SETOR_PEDIATRIA);         //Insere paciente de teste
    inserir(f, "Carlos", 7, SETOR_ORTOPEDIA);      //Insere paciente de teste

    imprimir(f);              //Mostra a fila apos as insercoes

    remover(f);               //Remove o paciente de maior prioridade
    remover(f);               //Remove o proximo paciente de maior prioridade

    imprimir(f);              //Mostra a fila apos algumas remocoes

    desfazer_ultima_remocao(f); //Desfaz a ultima remocao
    imprimir(f);                //Mostra a fila novamente

    relatorio(f);             //Exibe o relatorio estatistico

    printf("=== Teste automatico finalizado ===\n");
    f->status = STATUS_SUCESSO; //Atualiza o status como sucesso
}

// Função para liberar toda a memoria alocada pela fila e pelo historico
void destruir_fila(FilaPrioridade* f) {
    if (f == NULL) { //Verifica se a fila existe
        return; //Se não existir, nada a ser destruído
    }

    // Libera todos os nós da fila de pacientes
    No* atual = f->inicio; //Começa pelo inicio da fila
    while (atual != NULL) { //Percorre toda a fila
        No* temp = atual;   //Guarda o nó atual
        atual = atual->prox;//Avança para o próximo nó
        free(temp);         //Libera a memoria do nó atual
    }

    // Libera todos os nós da pilha de histórico
    NoHistorico* hAtual = f->topoHist; //Começa pelo topo da pilha
    while (hAtual != NULL) { //Percorre toda a pilha
        NoHistorico* temp = hAtual; //Guarda o nó atual
        hAtual = hAtual->prox;      //Avança para o próximo nó
        free(temp);                 //Libera a memoria do nó atual
    }

    free(f); //Libera a estrutura principal da fila
    //Nao há printf aqui para não poluir a saída quando for usada em outros contextos
}


// ======================= PARTE DO GRAFO (SETORES) =======================

// Função para mostrar os setores disponíveis
void mostrar_setores() {
    printf("\n--- Setores do Hospital ---\n");
    for (int i = 0; i < NUM_SETORES; i++) { //Percorre todos os setores
        printf("%d - %s\n", i, nomesSetores[i]); //Mostra o índice e o nome do setor
    }
    printf("---------------------------\n");
}

// Função para inicializar a matriz de adjacencia com zeros
static void zerar_grafo(GrafoHospital* g) {
    for (int i = 0; i < NUM_SETORES; i++) { //Percorre todas as linhas
        for (int j = 0; j < NUM_SETORES; j++) { //Percorre todas as colunas
            g->adj[i][j] = 0; //Define que inicialmente não há ligações
        }
    }
}

// Função simples para adicionar uma aresta entre dois setores (grafo não direcionado)
static void adicionar_aresta(GrafoHospital* g, int a, int b) {
    g->adj[a][b] = 1; //Liga o setor a ao setor b
    g->adj[b][a] = 1; //Liga o setor b ao setor a (pois o grafo é não direcionado)
}

// Cria um grafo padrão com alguns caminhos clínicos comuns
void inicializar_grafo_hospital(GrafoHospital* g) {
    zerar_grafo(g); //Começa com todas as posições zeradas

    // Exemplo de ligações entre os setores:
    adicionar_aresta(g, SETOR_TRIAGEM, SETOR_CLINICA_GERAL);   //Triagem -> Clínica Geral
    adicionar_aresta(g, SETOR_TRIAGEM, SETOR_PEDIATRIA);       //Triagem -> Pediatria
    adicionar_aresta(g, SETOR_CLINICA_GERAL, SETOR_EXAMES);    //Clínica Geral -> Exames
    adicionar_aresta(g, SETOR_CLINICA_GERAL, SETOR_CARDIOLOGIA);//Clínica Geral -> Cardiologia
    adicionar_aresta(g, SETOR_EXAMES, SETOR_INTERNACAO);       //Exames -> Internação
    adicionar_aresta(g, SETOR_CARDIOLOGIA, SETOR_INTERNACAO);  //Cardiologia -> Internação
    adicionar_aresta(g, SETOR_TRIAGEM, SETOR_ORTOPEDIA);       //Triagem -> Ortopedia
    adicionar_aresta(g, SETOR_ORTOPEDIA, SETOR_EXAMES);        //Ortopedia -> Exames
    // Esses caminhos podem representar fluxos clínicos básicos
}

// Função para executar BFS e mostrar o caminho mínimo entre dois setores
void bfs_caminho(GrafoHospital* g, int origem, int destino) {
    int fila[NUM_SETORES];     //Fila simples para BFS
    int inicio = 0, fim = 0;   //Índices de controle da fila
    int visitado[NUM_SETORES]; //Marca quais setores já foram visitados
    int anterior[NUM_SETORES]; //Guarda de onde viemos para cada setor (para reconstruir o caminho)

    // Inicializa os vetores
    for (int i = 0; i < NUM_SETORES; i++) {
        visitado[i] = 0;   //Ninguém foi visitado ainda
        anterior[i] = -1;  //Sem anterior definido
    }

    // Coloca a origem na fila
    fila[fim++] = origem; //Insere na fila
    visitado[origem] = 1; //Marca origem como visitada

    // BFS padrão
    while (inicio < fim) { //Enquanto a fila não estiver vazia
        int atual = fila[inicio++]; //Remove o primeiro elemento da fila

        if (atual == destino) { //Se chegamos no destino, podemos parar
            break;
        }

        // Verifica todos os vizinhos do setor atual
        for (int v = 0; v < NUM_SETORES; v++) {
            if (g->adj[atual][v] == 1 && !visitado[v]) { //Se há ligação e ainda não foi visitado
                fila[fim++] = v;     //Coloca o vizinho na fila
                visitado[v] = 1;     //Marca como visitado
                anterior[v] = atual; //Salva de onde viemos
            }
        }
    }

    // Verifica se o destino foi alcançado
    if (!visitado[destino]) {
        printf("\nNao existe caminho entre %s e %s.\n",
               nomesSetores[origem], nomesSetores[destino]);
        return;
    }

    // Reconstrói o caminho do destino até a origem usando o vetor anterior
    int caminho[NUM_SETORES];
    int tamCaminho = 0;
    int atual = destino;
    while (atual != -1) {
        caminho[tamCaminho++] = atual; //Guarda o setor no caminho
        atual = anterior[atual];       //Volta um passo
    }

    // Imprime o caminho na ordem correta (da origem até o destino)
    printf("\nCaminho minimo (BFS) de %s ate %s:\n", nomesSetores[origem], nomesSetores[destino]);
    for (int i = tamCaminho - 1; i >= 0; i--) { //Imprime do fim para o início
        printf("%s", nomesSetores[caminho[i]]);
        if (i > 0) {
            printf(" -> "); //Setas entre os setores
        }
    }
    printf("\n");
}

// Função recursiva auxiliar para DFS
static void dfs_rec(GrafoHospital* g, int atual, int visitado[]) {
    visitado[atual] = 1; //Marca o setor atual como visitado
    printf("%s ", nomesSetores[atual]); //Imprime o nome do setor

    //Visita todos os vizinhos não visitados
    for (int v = 0; v < NUM_SETORES; v++) {
        if (g->adj[atual][v] == 1 && !visitado[v]) { //Se há ligação e não foi visitado
            dfs_rec(g, v, visitado); //Chama recursivamente
        }
    }
}

// Função para executar DFS e mostrar a ordem de visita a partir de um setor
void dfs_visita(GrafoHospital* g, int origem) {
    int visitado[NUM_SETORES]; //Vetor de visitados

    for (int i = 0; i < NUM_SETORES; i++) { //Inicializa todos como não visitados
        visitado[i] = 0;
    }

    printf("\nOrdem de visita (DFS) a partir de %s:\n", nomesSetores[origem]);
    dfs_rec(g, origem, visitado); //Inicia a busca em profundidade
    printf("\n");
}