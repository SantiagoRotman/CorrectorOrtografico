#ifndef __IO_H__
#define __IO_H__
#include "queue.h"

//static inline void quit(const char *s);
char ** readfile(const char *path, int *len);
word * ReadDoc(const char *path, int *len);
void PrintSuggestions(char **list, word tuple, int len, FILE *output);

#endif