#ifndef FILA_H // Comando ultilzado para evitar que o arquivo seja implementado mais de uma vez
#define FILA_H

typedef struct No { //Estrutura do nó da fila(Pacientes)
    char nome[50];   //Definição do nome do paciente        
    int prioridade;  //Definição da prioridade do paciente       
    struct No* prox;  //No para o proximo elemento da fila       
} No;

typedef struct {//Estrutura da fila de prioridade
    No* inicio; //Ponteiro para o primeiro elemento da fila            
} FilaPrioridade;


FilaPrioridade* criar_fila();//Função para criação da fila
void inserir(FilaPrioridade* f, char nome, int prioridade);//Função para inserção de um elemento na fila
void remover(FilaPrioridade* f);//Função para remover um elemento da fila
void imprimir(FilaPrioridade* f);//Função para imprimir a fila de pacientes
void consultar(FilaPrioridade* f,char nome);//Função para consultar os pacientes presentes na fila

#endif // Finaliza o cabeçalho