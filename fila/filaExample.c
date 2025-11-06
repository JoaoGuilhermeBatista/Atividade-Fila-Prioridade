
#include <stdio.h>
#include <stdlib.h>

typedef struct NO{
  struct NO *prox;
  int dados;

}NO;

typedef struct FILA{
  struct NO *head; // "primeira pessoa da fila"
  struct NO *tail; // "ultima pessoa da fila"

}FILA; // fila pertence a NO

FILA *newFILA(){
  FILA *fi = (FILA *)malloc(sizeof(FILA)); // vai ser um ponteiro que vai apontar para a struct LISTA, ou seja, *fi ---> | head | tail |
  fi->head = NULL; // *f nao guarda os dados da fila diretamente, mas sim o endereço do primeiro e o ultimo elemento
  fi->tail = NULL;
  return fi;

}

void enfileirar(FILA *fi, int dados){
  NO *novo = (NO *)malloc(sizeof(NO)); //*novo é um ponteiro para um unico no, um elemento da lista
  novo->dados = dados; // esse novo no vai ser conectado a estrutura de controle FILA
  novo->prox = NULL; // garante que o novo no sempre será o ultimo

  if(fi->tail == NULL){ // caso a lista esteja vazia
    printf("Lista vazia\n");
    fi->head = novo; // como esta vazia o head vai apontar para o novo no
    fi->tail = novo; // e o tail vai apontar para o novo no tambem, por ser o primeiro elemento da lista

  }else { // caso não esteja vazia
    fi->tail->prox = novo; // vai pegar o no que esta no fim atual, vai entrar nesse no e acessar o ponteiro prox e fazer ele apontar para o novo elemento
    fi->tail = novo; // atualiza o ponteiro tail para apontar para o novo no, antes apontava pro antigo (novo fim da fila)
    }
}

int desenfileirar(FILA *fi){
  if(fi->head == NULL){
    printf("Lista vazia\n");
    return -1;
  }
  NO *aux = fi->head; // guarda o endereço do primeiro no, o que vai sair da lista posteriormente
  int valor = aux->dados; // vai guarda o dado que estava guardado no primeiro no para que nao seja perdido apos o free
  fi->head = fi->head->prox; // o inicio da fila agora aponta para o proximo no, logo o aux deixa de ser o primeiro elemento da lista

  if(fi->head == NULL){ // se a fila ficou vazia atualizamos os ponteiros
    fi->tail = NULL;
  }

  free(aux); // exclui o antigo primeiro no da lista
  //return valor; // imprime o dado que estava guardado no antigo no da lista
}

void showFila(FILA *fi){
  NO *temp = fi->head;
  while(temp != NULL){
    printf("%d ", temp->dados);
    temp = temp->prox;
    }
    printf("\n");
}

int main(){
  FILA *fi = newFILA();

  enfileirar(fi, 1);
  enfileirar(fi, 2);
  enfileirar(fi, 3);

  printf("\nLista:\n");
  showFila(fi);
  printf("\n");
  printf("Removendo %d...\n",desenfileirar(fi));
  printf("\nNova Lista\n");
  showFila(fi);

  printf("\n");
  printf("Removendo %d...\n",desenfileirar(fi));
  printf("\nNova Lista\n");
  showFila(fi);

  return 0;
}