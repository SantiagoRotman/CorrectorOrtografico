#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

word CreateWord(char *str, short int step){
  word aux;
  aux.str = str;
  aux.step = step;
  return aux;
}

QNode* newNode(char *k, short int step)
{
    QNode* temp = (QNode*)malloc(sizeof(QNode));
    temp->key = CreateWord(k, step);
    temp->next = NULL;
    return temp;
}
  
Queue* createQueue()
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}
  
void push(Queue* q, char *k, short int step)
{
    // Crea nodo auxiliar
    QNode* temp = newNode(k, step);
  
    // Si la cola esta vacia, entonces el nuevo nodo es el principio y el final
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
  
    // Agrego el nodo nuevo al final y lo pongo como el nuevo final de la cola
    q->rear->next = temp;
    q->rear = temp;
}

void pop(Queue* q)
{
    if (q->front == NULL)
        return ;
  
    // Guardo el primer nodo
    QNode* temp = q->front;

    q->front = q->front->next;
  
    // Si era el unico
    if (q->front == NULL)
        q->rear = NULL;
  
    free(temp);

}

int isQueueEmpty(Queue *q){
    if(q->front) return 0;
    else return 1;
}
