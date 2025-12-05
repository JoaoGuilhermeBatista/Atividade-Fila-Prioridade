#ifndef FILA_H // Comando ultilzado para evitar que o arquivo seja implementado mais de uma vez
#define FILA_H

// Enum para representar o status das operações realizadas na fila
typedef enum { //Enumeração para categorizar os resultados das operações
    STATUS_SUCESSO = 0,               // Operação concluída com sucesso
    STATUS_FILA_VAZIA,                // Operação falhou porque a fila está vazia
    STATUS_PACIENTE_NAO_ENCONTRADO,   // Consulta não encontrou o paciente
    STATUS_ERRO_MEMORIA               // Falha na alocação de memória
} StatusOperacao;

// Enum para representar os setores do hospital
typedef enum { //Enumeração dos setores do hospital
    SETOR_TRIAGEM = 0,       //Setor de Triagem
    SETOR_CLINICA_GERAL,     //Setor de Clínica Geral
    SETOR_ORTOPEDIA,         //Setor de Ortopedia
    SETOR_PEDIATRIA,         //Setor de Pediatria
    SETOR_CARDIOLOGIA,       //Setor de Cardiologia
    SETOR_EXAMES,            //Setor de Exames
    SETOR_INTERNACAO,        //Setor de Internação
    NUM_SETORES              //Quantidade total de setores (deve ficar por último)
} SetorHospital;

// Nó da fila principal de pacientes
typedef struct No { //Estrutura do nó da fila(Pacientes)
    char nome[50];   //Definição do nome do paciente        
    int prioridade;  //Definição da prioridade do paciente       
    int setor;       //Índice do setor atual do paciente        
    struct No* prox;  //No para o proximo elemento da fila       
} No;

// Nó da pilha de histórico para desfazer operações
typedef struct NoHistorico { //Estrutura da pilha de histórico (para desfazer remoções)
    char nome[50];            //Nome do paciente removido
    int prioridade;           //Prioridade original do paciente
    int setor;                //Setor original do paciente
    struct NoHistorico* prox; //Ponteiro para o proximo elemento da pilha
} NoHistorico;

typedef struct {//Estrutura da fila de prioridade
    No* inicio;              //Ponteiro para o primeiro elemento da fila            
    NoHistorico* topoHist;   //Ponteiro para o topo da pilha de histórico (undo)
    int tamanho;             //Quantidade de pacientes atualmente na fila
    int totalAtendidos;      //Quantidade total de pacientes já atendidos
    int somaPriorAtendidos;  //Soma das prioridades dos pacientes atendidos
    StatusOperacao status;   //Status da última operação realizada
} FilaPrioridade;

// Estrutura para representar o grafo dos setores do hospital
typedef struct { //Estrutura para representar o grafo de setores do hospital
    int adj[NUM_SETORES][NUM_SETORES]; //Matriz de adjacencia (0 = sem ligação, 1 = ligação)
} GrafoHospital;


// Funções da fila de prioridade
FilaPrioridade* criar_fila();//Função para criação da fila
void inserir(FilaPrioridade* f, char nome[], int prioridade, int setor);//Função para inserção de um elemento na fila
void remover(FilaPrioridade* f);//Função para remover um elemento da fila
void imprimir(FilaPrioridade* f);//Função para imprimir a fila de pacientes
void consultar(FilaPrioridade* f,char nome[]);//Função para consultar os pacientes presentes na fila

void desfazer_ultima_remocao(FilaPrioridade* f);//Função para desfazer a última remoção (usa pilha)
void relatorio(FilaPrioridade* f);//Função para exibir relatório estatístico da fila
void teste_automatico(FilaPrioridade* f);//Função para testar automaticamente a fila
void destruir_fila(FilaPrioridade* f);//Função para liberar toda a memória alocada


// Funções relacionadas ao grafo dos setores
void inicializar_grafo_hospital(GrafoHospital* g);//Função para criar as ligações padrão entre os setores
void mostrar_setores();//Função para mostrar os setores e seus índices para o usuário
void bfs_caminho(GrafoHospital* g, int origem, int destino);//Função para executar BFS e mostrar o caminho mínimo entre dois setores
void dfs_visita(GrafoHospital* g, int origem);//Função para executar DFS e mostrar a ordem de visita a partir de um setor

#endif // Finaliza o cabeçalho