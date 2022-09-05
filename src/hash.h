#ifndef __HASH_H__
#define __HASH_H__

#include "config.h"

typedef void (*FuncionInsertadora)(void *dato1, int id);

typedef void *(*FuncionCreadora)(int dato1);

typedef void (*FuncionDestructora)(void *dato);

typedef unsigned (*FuncionHash)(void *dato);

typedef int (*FuncionCarga)(void *dato);


typedef struct _TablaHash *TablaHash;

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCreadora crear,
                          FuncionInsertadora insertar, FuncionDestructora destr,
                          FuncionHash hash, FuncionCarga carga);

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla);



int CellLoad(TablaHash tabla, int id);

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla);

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla);

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 */
void tablahash_insertar(TablaHash tabla, void *dato, int id);

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato);

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato);

#endif /* __HASH_H__ */