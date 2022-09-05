#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../src/trie.h"

void testTrieCreate(){
    Trie *aux = TrieCreate();
    assert(aux != NULL);
    assert(aux->valid == 0);

    for(int i = 0; i < ALPHABET_SIZE; i++) assert(aux->children[i] == NULL);
    TrieDestroy(aux);
}

void testTrieInsert(){
    Trie *trie = TrieCreate();
    char aux[100] = "hola";

    TrieInsert(trie, "");
    for(int i = 0; i < ALPHABET_SIZE; i++) assert(trie->children[i] == NULL);


    TrieInsert(trie, aux);

    for(int pos = 0; pos < strlen(aux); pos++){
        for(int i = 0; i < ALPHABET_SIZE; i++){
            if(aux[pos] == 'a'+i)   assert(trie->children[i] != NULL);
            else    assert(trie->children[i] == NULL);
        }
        trie = trie->children[aux[pos]-'a'];
    }

    TrieDestroy(trie);
}

void testTrieSearch(){
    Trie *trie = TrieCreate();
    char aux[100] = "hola";
    char aux2[100] = "holaaaas";

    TrieInsert(trie, aux2);
    assert(TrieSearch(trie, aux2) == 1);
    assert(TrieSearch(trie, aux) == 0);
    TrieInsert(trie, aux);
    assert(TrieSearch(trie, aux) == 1);
    assert(TrieSearch(trie, "pepe") == 0);

    TrieDestroy(trie);

}

int main() {
    testTrieCreate();
    testTrieInsert();
    testTrieSearch();

    printf("Todos los test han sido ejecutados y sin errores.\n");
    return 0;
}