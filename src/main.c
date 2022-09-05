#include <stdlib.h>
#include <stdio.h>
#include "search.h"
#include "config.h"
#include "io.h"

int main(int argc, char **argv){

    if(argc != 4 ) {
        printf("Para ejecutar: ./main 'diccionario' 'texto' 'salida'\n");
        return 1;
    }


    int len = 0;
    int len2 = 0;
    char **diccionario = readfile(argv[1], &len);
    word *doc = ReadDoc(argv[2], &len2);

    FILE *out = fopen(argv[3], "wb");

    Search(diccionario, len, doc, len2, out);



}