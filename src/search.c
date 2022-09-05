#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "search.h"
#include "io.h"

int IsWithin(char **list, int len, char *string){
    int ban = 0;
    for(int i = 0; i < len; i++){
        if(!strcmp(list[i], string))
            ban = 1;
    }
    return ban;
}


void ChangeCharacter(Trie *trie, Trie *used, Queue *q, char **found, char *string, short int step, int *Nfound){
    int len = strlen(string);
    for(int pos = 0; string[pos] != '\0' && trie != NULL; pos++){ // Recorro el string
        for(int j = 0; j < ALPHABET_SIZE; j++){
            int pushed = 0;
            char *aux = malloc(sizeof(char)*len+1);
            memcpy(aux, string, len+1);

            // Cambio la letra de la posicion $ppos por ('a'+j)
            aux[pos] = 'a' + j; 
            aux[len] = '\0';

            // Si el camino existe y no lo calcule previamente
            if(trie->children[j] && !TrieSearch(used, aux)){
                if(step < MAX_STEPS) {
                    push(q, aux, step+1); // Si puedo aplicarle mas reglas la meto en la cola
                    pushed = 1;
                }
                
                /* Me fijo si la palabra con el nuevo caracter esta en el diccionario
                Tener en cuenta que trie esta en el nodo correspondiente al camino recorrido por la palabra
                        hasta su posicion $pos-1
                
                    Ejemplo: string: "hola", pos=2
                        trie = trie->'h'->'o'->$j
                        string+pos: "a"
                        Equivale a buscar "ho"+('a'+j)+"a" en el arbol original 
                 */
                if(TrieSearch(trie->children[j], string+pos+1)){
                    if(!IsWithin(found, (*Nfound), aux)){
                        char *aux2 = malloc(sizeof(char)*len+1);
                        memcpy(aux2, aux, len+1);
                        if(!pushed) free(aux);
                        found[(*Nfound)++] = aux2;
                        if((*Nfound) == MAX_SUGGESTIONS) return;
                    }
                }

            }
            else free(aux);
            
        }
        // Me muevo por el arbol para no calcular caminos inexistentes y asi 
        //   no recorro el arbol ineccesariamente cada vez que busco una palabra
        trie = trie->children[string[pos]-'a'];
    }
}

void InsertCharacter(Trie *trie, Trie *used, Queue *q, char **found, char *string, short int step, int *Nfound){
    int len = strlen(string);
    for(int pos = 0; pos <= len && trie != NULL; pos++){
        for(int j = 0; j < ALPHABET_SIZE; j++){
            int pushed = 0;
            // Creo una nueva palabra con la letra ('a'+j) en el medio de [pos-1] y [pos]
            char *aux = malloc(sizeof(char)*len+2);
            memcpy(aux, string, pos);
            aux[pos] = 'a' + j;
            memcpy(aux+pos+1, string+pos, len-pos);
            aux[len+1] = '\0';

            // Si el camino existe y no la calcule antes
            if(trie->children[j] && !TrieSearch(used, aux)){
                if(step < MAX_STEPS) {
                    push(q, aux, step+1); // Si puedo aplicarle mas reglas la meto en la cola
                    pushed = 1;
                }

                /* Me fijo si la palabra con el nuevo caracter esta en el diccionario
                Tener en cuenta que trie esta en el nodo correspondiente al camino recorrido por la palabra
                        hasta su posicion $pos-1
                
                    Ejemplo: string: "hola", pos=2
                        trie = trie->'h'->'o'->$j
                        string+pos: "la"
                        Equivale a buscar "ho"+('a'+j)+"la" en el arbol original 
                */
                if(TrieSearch(trie->children[j], string+pos)){
                    if(!IsWithin(found, (*Nfound), aux)){
                        char *aux2 = malloc(sizeof(char)*len+2);
                        memcpy(aux2, aux, len+2);
                        if(!pushed) free(aux);
                        found[(*Nfound)++] = aux2;
                        if((*Nfound) == MAX_SUGGESTIONS) return;
                    }
                }
            }
            else free(aux);
        }
        // Me muevo por el arbol para no calcular caminos inexistentes y asi 
        //   no recorro el arbol ineccesariamente cada vez que busco una palabra
        trie = trie->children[string[pos]-'a'];
    }
}

void SwitchCharacters(Trie *trie, Trie *used, Queue *q, char **found, char *string, short int step, int *Nfound){
    int len = strlen(string);

    for(int pos = 1; pos < len ; pos++){
        int pushed = 0;
        // Creo una nueva palabra intercambiando el caracter [pos-1] por el de [pos]
        char *aux = malloc(sizeof(char)*len+1);
        memcpy(aux, string, len+1);
        char ch = aux[pos-1];
        aux[pos-1] = aux[pos];
        aux[pos] = ch; 

        // Si no calcule previamente esta palabra
        if(!TrieSearch(used, aux)){
            if(step < MAX_STEPS) {
                push(q, aux, step+1); // Si puedo aplicarle mas reglas la meto en la cola
                pushed = 1;
            }

            // Me fijo si la palabra con los caracteres intercambiados esta en el diccionario
            if(TrieSearch(trie, aux)){
                if(!IsWithin(found, (*Nfound), aux)){
                    char *aux2 = malloc(sizeof(char)*len+1);
                    memcpy(aux2, aux, len+1);
                    if(!pushed) free(aux);
                    found[(*Nfound)++] = aux2;
                    if((*Nfound) == MAX_SUGGESTIONS) return;
                }
            }
        }
        else free(aux);
    }
}



void SkipCharacter(Trie *trie, Trie *used, Queue *q, char **found, char *string, short int step, int *Nfound){
    int len = strlen(string);

    for(int pos = 0; pos < len && trie != NULL ; pos++){
        // Creo una nueva palabra saltiandome el caracter de la posicion $pos de la original
        char *aux = malloc(sizeof(char)*len+1);
        aux[0] = '\0';
        strncat(aux, string, pos);
        strcat(aux, string+pos+1);

        // Si no calcule previamente esta palabra
        if(!TrieSearch(used, aux)){
            int pushed = 0;
            if(step < MAX_STEPS) {
                push(q, aux, step+1); // Si puedo aplicarle mas reglas la meto en la cola
                pushed = 1;
            }

            /* Me fijo si la palabra sin el caracter Nro $pos esta en el diccionario
               Tener en cuenta que trie esta en el nodo correspondiente al camino recorrido por la palabra
                    hasta su posicion $pos-1
              
                Ejemplo: string: "hola", pos=2
                    trie = trie->'h'->'o'
                    string+pos+1: "a"
                       Equivale a buscar "hoa" en el arbol original 
            */
            if(TrieSearch(trie, string+pos+1)){
                if(!IsWithin(found, (*Nfound), aux)){
                    char *aux2 = malloc(sizeof(char)*len+1);
                    memcpy(aux2, aux, len+1);
                    if(!pushed) free(aux);
                    found[(*Nfound)++] = aux2;
                    if((*Nfound) == MAX_SUGGESTIONS) return;
                }
            }
            if(!pushed) free(aux);

        }
        else free(aux);

        // Me muevo por el arbol para no calcular caminos inexistentes y asi 
        //   no recorro el arbol ineccesariamente cada vez que busco una palabra
        trie = trie->children[string[pos]-'a']; 
    }
}

void Divide(Trie *trie, char **found, char *string, int *Nfound){
    int len = strlen(string);
    for(int pos = 1; pos < len; pos++){
        // Creo una nueva palabra hasta la posicion $pos
        char *aux = malloc(sizeof(char)*len+2);
        aux[0] = '\0';
        memcpy(aux, string, pos);
        aux[pos] = '\0'; 
        
        // Me fijo si la palabra cortada y su resto no estan en el diccionario
        if(!TrieSearch(trie, aux) || !TrieSearch(trie, string+pos)) {
            free(aux);
            continue;
        }

        // Si ambas estan agrego un espacio y concateno la cortada y su resto
        aux[pos] = ' ';
        aux[pos+1] = '\0';
        strcat(aux, string+pos);

        if(!IsWithin(found, (*Nfound), aux)){
            found[(*Nfound)++] = aux;
            if((*Nfound) == MAX_SUGGESTIONS) return;
        }
        else free(aux);
    }
}

void SearchWord(Trie *trie, char **found, char *string, int *Nfound){
    Queue *queue = createQueue();   // Cola con las palabras a procesar
    Trie *used = TrieCreate();   // Trie con las palabras ya procesadas
    //printf("bbbbbbbbbbbbbbbb\n");
    char *string2 = malloc(sizeof(char)*strlen(string)+1);
    strcpy(string2, string);
    push(queue, string2, 0); // Pongo la palabra original en la cola

    while(!isQueueEmpty(queue)){ // Mientras que la cola no este vacia
        word aux = queue->front->key;
        if(aux.step < MAX_STEPS && (*Nfound) < MAX_SUGGESTIONS){
            Divide(trie, found, aux.str, Nfound);
            if((*Nfound) == MAX_SUGGESTIONS) continue;

            SkipCharacter(trie, used, queue, found, aux.str, aux.step, Nfound); // Busco y agrego a la cola
            if((*Nfound) == MAX_SUGGESTIONS) continue;

            SwitchCharacters(trie, used, queue, found, aux.str, aux.step, Nfound);// Busco y agrego a la cola
            if((*Nfound) == MAX_SUGGESTIONS) continue;

            ChangeCharacter(trie, used, queue, found, aux.str, aux.step, Nfound);// Busco y agrego a la cola
            if((*Nfound) == MAX_SUGGESTIONS) continue;

            InsertCharacter(trie, used, queue, found, aux.str, aux.step, Nfound);// Busco y agrego a la cola
            if((*Nfound) == MAX_SUGGESTIONS) continue;

            TrieInsert(used, aux.str); // Inserto la palabra ya procesada en el arbol de las usadas (Funciona mejor sin este trie pero me da miedo) 
        }
        pop(queue); // Saco el nodo ya procesado de la cola
        free(aux.str);
    }
    free(queue);
    TrieDestroy(used);
}


void Search(char **diccionario, int len_dic, word *doc, int len_doc, FILE *output){

    Trie *trie = TrieCreate();
    for(int i = 0; i < len_dic; i++) TrieInsert(trie, diccionario[i]);
    
    
    for(int i = 0; i < len_dic; i++) free(diccionario[i]);
    free(diccionario);

    for(int i = 0; i < len_doc; i++){
        for(int j = 0; doc[i].str[j] != '\0';j++)  doc[i].str[j] = tolower(doc[i].str[j]);
        if(!TrieSearch(trie, doc[i].str))
        {
            char **found = malloc(sizeof(char*)*MAX_SUGGESTIONS+2);
            int Nfound = 0;

            SearchWord(trie, found, doc[i].str, &Nfound);
            
            PrintSuggestions(found, doc[i], Nfound, output);

            for(int k = 0; k < Nfound; k++) free(found[k]);
            free(found);
        }
    }
    TrieDestroy(trie);
    fclose(output);
    for(int i = 0; i < len_doc; i++) free(doc[i].str);
    free(doc);
    


}

