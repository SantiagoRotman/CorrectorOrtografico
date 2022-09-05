#ifndef __SEARCH_H__
#define __SEARCH_H__
#include "trie.h"
#include "queue.h"
#include "config.h"

/*
    Funcion que toma una lista de palabras, su largo y otra palabra
    Devuelve 1 si la palabra esta en la lista y 0 de lo contrario
*/
int IsWithin(char **list, int len, char *string);

/*
    Funcion que toma una palabra, calcula todas las palabras que se obtienen de variar un caracter
        por todos los otros caracteres posibles.
    Luego agrega todos las palabras calculadas, que no esten en el Trie used, a la cola "q" 
    Si alguna de las palabras calculadas se encuetra en el trie del diccionario la agrego a la lista 'found'
        y aumento el contador Nfound
*/
void ChangeCharacter(Trie *trie, Trie *used, Queue *q, char **found, char *string, short int step, int *Nfound);

/*
    Funcion que toma una palabra, calcula todas las palabras que se obtienen de incertar un caracter
        al principio, final y entre medio de cada caracter de la palabra.
    Luego agrega todos las palabras calculadas, que no esten en el Trie used, a la cola "q" 
    Si alguna de las palabras calculadas se encuetra en el trie del diccionario la agrego a la lista 'found'
        y aumento el contador Nfound
*/
void InsertCharacter(Trie *trie, Trie *used, Queue *q, char **found, char *string, short int step, int *Nfound);

/*
    Funcion que toma una palabra, calcula todas las palabras que se obtienen de intercambiar cada
        par de caracteres adyacentes de la palabra
    Luego agrega todos las palabras calculadas, que no esten en el Trie used, a la cola "q" 
    Si alguna de las palabras calculadas se encuetra en el trie del diccionario la agrego a la lista 'found'
        y aumento el contador Nfound
*/
void SwitchCharacters(Trie *trie, Trie *used, Queue *q, char **found, char *string, short int step, int *Nfound);

/*
    Funcion que toma una palabra, calcula todas las palabras que se obtienen de eliminar cada
        caracter de la palabra (uno solo a la vez)
    Luego agrega todos las palabras calculadas, que no esten en el Trie used, a la cola "q" 
    Si alguna de las palabras calculadas se encuetra en el trie del diccionario la agrego a la lista 'found'
        y aumento el contador Nfound
*/
void SkipCharacter(Trie *trie, Trie *used, Queue *q, char **found, char *string, short int step, int *Nfound);

/*
    Funcion que toma una palabra, calcula el par de palabras que se optiene de divir la palabra en 
        cualquier posicion 
    Si el par de las palabras calculadas se encuetran en el trie del diccionario, agrego a la lista 'found'
        la concatenacion del par de palabras separadas por un espacio y aumento el contador Nfound
*/
void Divide(Trie *trie, char **found, char *string, int *Nfound);

/*
    Funcion que toma una palabra y un diccionario dado en un Trie
    Calcula todas las palabras generadas al aplicar 5 reglas hasta $MAX_STEPS veces
    Calcula hasta que no se puedan generar mas palabras o encuentre $MAX_SUGGESTIONS palabras
        que esten en el diccionario
    Agrega todas las encontradas a la lista 'found' y da el numero de encontradas en 'Nfound' 
*/
void SearchWord(Trie *trie, char **found, char *string, int *Nfound);

/*
    Toma un diccionario, su largo. Las palabras de un texto, la cantidad y un archivo salida.
    Para cada palabra si no esta en el diccionario le aplica la funcion SearchWord a cada palabra del texto generado 
        generado aproximaciones que si esten en el diccionario.
    Imprime el resultado en el archivo de salida.
*/
void Search(char **diccionario, int len_dic, word *doc, int len_doc, FILE *output);

#endif