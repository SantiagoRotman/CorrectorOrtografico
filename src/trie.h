#ifndef __TRIE_H__
#define __TRIE_H__

#include "config.h"

/*
  Estructura tipo arbol que tiene los punteros a los hijos y
  un entero que es 1 si una palabra termina en ese nodo, 0 de lo contrario
*/
struct _Trie{
  struct _Trie *children[ALPHABET_SIZE];
  int valid;
};

typedef struct _Trie Trie;

/*
  Funcion de utilidad que crea un trie vacio
*/
Trie *TrieCreate();

/*
  Funcion que toma un puntero a un trie y agraga 
  un nuevo camino dado por los caracteres de una palabra
*/
void TrieInsert(Trie *root, char *string);

/*
  Funcion que toma un puntero a un trie y una palabra.
  Devuelve 1 si el camino dado por los caracteres de la palabra existe y termina en un nodo valido
  Devuelve 0 de lo contrario
*/
int TrieSearch(Trie *root, char *string);

/*
  Funcion que toma un puntero a un trie y lo destruye recursivamente
  liberando la memoria
*/
void TrieDestroy(Trie *root);

#endif