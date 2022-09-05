#include <stdlib.h>
#include <stdio.h>
#include "trie.h"

Trie *TrieCreate(){
    Trie *root = NULL;
    root = (Trie *)malloc(sizeof(Trie));
    root->valid = 0;

    for(int i = 0; i < ALPHABET_SIZE; i++) root->children[i] = NULL; // Inicializo los hijos en NULL

    return root; 
}

void TrieInsert(Trie *root, char *string){
    int i;

    for(i = 0; string[i] != '\0'; i++){
        if(root->children[string[i] - 'a']) // Si ya esta el camino me muevo por el
            root = root->children[string[i] - 'a'];
        else{
            // Si no esta el camino lo creo y me muevo por el
            root->children[string[i] - 'a'] = TrieCreate();
            root = root->children[string[i] - 'a'];
            root->valid = 0;
        }
    }
    root->valid = 1;
    return;
}

int TrieSearch(Trie *root, char *string){
    if(!root) return 0;

    for(int i = 0; string[i] != '\0'; i++){
        if(root->children[string[i] - 'a'] == NULL)
            return 0;
        else
            root = root->children[string[i] - 'a'];
    }
    return root->valid;
}

void TrieDestroy(Trie *root){
    for(int i = 0; i < ALPHABET_SIZE; i++){
        if(root->children[i]) TrieDestroy(root->children[i]);
    }
    free(root);
}

