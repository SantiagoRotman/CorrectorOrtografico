#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../src/search.h"
#include "../src/io.h"

void testSearchWord(Trie *trie){
    char **found = malloc(sizeof(char*)*MAX_SUGGESTIONS+2);
    int Nfound = 0;

    SearchWord(trie, found, "xxxxxxxxx", &Nfound);
    assert(Nfound == 2);
    assert(IsWithin(found, Nfound, "xxxxxxabc"));
    assert(IsWithin(found, Nfound, "abcxxxxxx"));

    for(int i = 0; i < Nfound; i++) free(found[i]);
    free(found);

    found = malloc(sizeof(char*)*MAX_SUGGESTIONS+2);
    Nfound = 0;

    SearchWord(trie, found, "yyyyyyxxx", &Nfound);
    assert(Nfound == 1);
    assert(IsWithin(found, Nfound, "yyyyyy"));
    for(int i = 0; i < Nfound; i++) free(found[i]);
    free(found);



    found = malloc(sizeof(char*)*MAX_SUGGESTIONS+2);
    Nfound = 0;

    SearchWord(trie, found, "dadada", &Nfound);
    assert(Nfound == 1);
    assert(IsWithin(found, Nfound, "adadad"));
    for(int i = 0; i < Nfound; i++) free(found[i]);
    free(found);



    found = malloc(sizeof(char*)*MAX_SUGGESTIONS+2);
    Nfound = 0;

    SearchWord(trie, found, "holapepe", &Nfound);
    assert(Nfound == 1);
    assert(IsWithin(found, Nfound, "hola pepe"));
    for(int i = 0; i < Nfound; i++) free(found[i]);
    free(found);



    found = malloc(sizeof(char*)*MAX_SUGGESTIONS+2);
    Nfound = 0;

    SearchWord(trie, found, "xaxzw", &Nfound);
    assert(Nfound == 1);
    assert(IsWithin(found, Nfound, "axxy"));
    for(int i = 0; i < Nfound; i++) free(found[i]);
    free(found);

    //for(int i = 0; i < Nfound; i++) printf("%s\n",found[i]);



}

int main() {
    int len = 0;
    char **diccionario = readfile("tests/testDic.txt", &len);

    Trie *trie = TrieCreate();
    for(int i = 0; i < len; i++) TrieInsert(trie, diccionario[i]);
    for(int i = 0; i < len; i++) free(diccionario[i]);
    free(diccionario);

    testSearchWord(trie);

    TrieDestroy(trie);

    printf("Todos los test han sido ejecutados y sin errores.\n");
    return 0;
}