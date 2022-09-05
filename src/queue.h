#ifndef __STACK_H__
#define __STACK_H__
#include "config.h"


/*
  Estructura nodo de la cola, tiene un unico elemento que es (palabra, Nro de reglas aplicadas)
  y un puntero al siguiente de la cola
*/
struct _QNode {
    word key;
    struct _QNode* next;
};
typedef struct _QNode QNode;

/*
  Estructura de la cola que tiene el primer elemento y el ultimo
*/
struct _Queue {
    struct _QNode *front, *rear;
};
typedef struct _Queue Queue;


word CreateWord(char *str, short int step);
/*
  Funcion que toma un puntero a una palabra y la cantidad de reglas que se 
  aplicaron para conseguirla y devuelve un puntero a un QNode creado con esos datos
*/
QNode* newNode(char *k, short int step);

/*
  Funcion de utilidad que crea una cola vacia y devuelve el puntero a la misma
*/
Queue* createQueue();

/*
  Funcion que toma un puntero a una cola, un puntero a una palabra y la cantidad de reglas que se 
  aplicaron para conseguirla y agrega un nodo al final de la cola
*/
void push(Queue* q, char *k, short int step);

/*
  Funcion que toma un puntero a una cola y elimina el primer elemento
*/
void pop(Queue* q);

/*
  Funcion que toma un puntero a una cola y devuelve 1 si esta vacia
  0 de lo contrario
*/
int isQueueEmpty(Queue* q);

#endif