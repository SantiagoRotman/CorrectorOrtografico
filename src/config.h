#ifndef __CONFIG_H__
#define __CONFIG_H__

#define MAX_WORD_LEN 25
#define MAX_SUGGESTIONS 5
#define MAX_STEPS 3
#define ALPHABET_SIZE 26

/*
  Estructura que tiene un puntero a una palabra y un entero que indica
  la cantidad de reglas que se le aplicaron para obtenerla.
*/
typedef struct {
  char *str;
  int step;
} word;

#endif