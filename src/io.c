#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io.h"

static inline void quit(const char *s)
{
	perror(s);
	exit(1);
}

char ** readfile(const char *path, int *len){
    int sz = 1024;
	char ** diccionario = malloc(sz * sizeof(char*));
	FILE *f = fopen(path, "rb");

	if (f == NULL)
		quit("readfile.fopen");

    char buff[255];
	int i;
    
	for(i = 0; fscanf(f, "%s", buff) != EOF; i++ ) // Recorro el archivo 
	{
		if(i == sz){ // Si se termino el espacio alocado pido mas
			sz = sz * 2;
			diccionario = (char**) realloc(diccionario, sizeof(char*) * sz);
		}
		diccionario[i] = malloc(1+strlen(buff)*sizeof(char));  // Pido memoria para la palabra
		strcpy(diccionario[i], buff); 
	}
	*len = i;
	fclose(f);
	return diccionario;

}

word *ReadDoc(const char *path, int *len){
    int sz = 1024;
	word * doc = malloc(sz * sizeof(word));
	FILE *f = fopen(path, "rb");

	if (f == NULL)
		quit("readfile.fopen");

    char buff[255] = "";
	int i;
	int linea = 1;
    fscanf(f, "%[^a-zA-Z]", buff);
	
	for(int j = 0; buff[j] != '\0'; j++){
		if(buff[j] == '\n') linea++;
	}

	for(i = 0; fscanf(f, "%[a-zA-Z]", buff) != EOF; i++ ) // Recorro el archivo, leyendo letras solamente
	{
		if(i == sz){ // Si se termino el espacio alocado pido mas
			sz = sz * 2;
			doc = (word *) realloc(doc, sizeof(word) * sz);
		}
		doc[i].str = malloc(1+strlen(buff)*sizeof(char)+2);  // Pido memoria para la palabra
		strcpy(doc[i].str, buff);
		doc[i].step = linea;

		fscanf(f, "%[^a-zA-Z]", buff);// Recorro el archivo, leyendo todo menos letras

		for(int j = 0; buff[j] != '\0'; j++){
			if(buff[j] == '\n') {
				linea++;
			}
		}

	}
	*len = i;
	fclose(f);
	return doc;
}

void PrintSuggestions(char **list, word tuple, int len, FILE *output){
	if(!tuple.str) return;
	fprintf(output, "Linea %d, \"%s\" no esta en el diccionario.\n", tuple.step, tuple.str);
	fprintf(output, "Quizas quiso decir: ");

	if(len > 0){
		int i = 0;
		for(; i < len-1; i++){
			fprintf(output, "%s, ", list[i]);
		}
		fprintf(output, "%s\n\n", list[i]);
	}
	//fprintf(output, "\n\n");
	//for(int i = 0; i < len; i++) free(list[i]);
}