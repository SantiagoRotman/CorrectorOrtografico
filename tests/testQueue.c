#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../src/queue.h"

void testCreateWord(){
    word aux = CreateWord("hola", 0);
    assert(!strcmp(aux.str, "hola"));
    assert(aux.step == 0);

}

void testnewNode(){
    char aux[100] = "holas";
    QNode *nodo = newNode(aux, 0);

    assert(nodo != NULL);
    assert(!strcmp(nodo->key.str, aux)); 
    assert(nodo->key.step == 0);
    assert(nodo->next == NULL);

    free(nodo);
}

void testcreateQueue(){
    Queue* cola = createQueue();
    assert(cola != NULL);
    assert(cola->front == NULL);
    assert(cola->rear == NULL);
    free(cola);

}

void testPush(){
    char aux[100] = "holas";
    char aux1[100] = "holas";
    char aux2[100] = "holas";
    Queue* cola = createQueue();

    push(cola, aux, 0);
    assert(cola->front != NULL);
    assert(cola->rear != NULL);
    assert(cola->rear == cola->front);
    assert(!strcmp(cola->front->key.str, aux));
    assert(cola->front->key.step == 0);

    push(cola, aux1, 1);
    assert(cola->rear != cola->front);
    assert(!strcmp(cola->front->next->key.str, aux1));
    assert(cola->front->next->key.step == 1);

    push(cola, aux2, 2);
    assert(!strcmp(cola->front->next->next->key.str, aux2));
    assert(cola->front->next->next->key.step == 2);

}

int main() {
    testCreateWord();
    testnewNode();
    testcreateQueue();
    testPush();

    printf("Todos los test han sido ejecutados y sin errores.\n");
    return 0;
}