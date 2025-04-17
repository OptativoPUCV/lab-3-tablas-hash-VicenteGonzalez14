#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    long indice = hash(key, map->capacity);
    long inicial = indice; 
    Pair *newPair = createPair(key, value);
    while(map->buckets[indice] != NULL && map->buckets[indice]->key != NULL ){

        if (strcmp(map->buckets[indice]->key, key) == 0) {
            free(newPair->key);  // Liberar la memoria de la clave
            free(newPair);        // Liberar la memoria del par
            return;  // No insertar claves repetidas
        }
        indice = (indice + 1) % map->capacity;
        
        // Si volvemos al índice inicial, hemos recorrido toda la tabla
        if (indice == inicial) {
            printf("El mapa hash está lleno.\n");
            return;  // El mapa está lleno
        }
    }
    map->buckets[indice] = newPair;
    map->size++;  // Incrementar el tamaño

    // Actualizar el índice del último dato accedido
    map->current = indice;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)

}


HashMap * createMap(long capacity) {
    HashMap *map = (HashMap*)malloc(sizeof(HashMap));
    map->capacity = capacity;  // Establecer la capacidad inicial
    map->size = 0;  // Al principio no hay elementos
    map->current = -1;

    map->buckets = (Pair**)malloc(sizeof(Pair*) * map->capacity);
    for (long i = 0; i < map->capacity; i++) {
        map->buckets[i] = NULL;
    }
    return map; 
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {  

    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
