//
//  AirportInfo.c
//  PlaneAssignment
//
//  Created by Thomas Dean on 2025-10-13.
//

#include "AirportInfo.h"
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 40 // defines the size of hash table

// defined a struct type for airport
typedef struct airportNode {
    char civilName[50]; // civil name of the airport
    char icaoName[10]; // ICAO code of the airport
    struct airportNode * next; // pointer to the next airport node
} airportNode;

static airportNode * hashTable[HASH_SIZE]; // hash table for airports
static int initialized = 0; // variable to check if hash table is initialized

unsigned int hashAirport(char * str){
    unsigned int val = 0; // initialize sum
    for(int i = 0; str[i] != '\0'; i++){
        val = val + str[i] * (i+1); // weight by position of the first character being 1
    }
    return val % HASH_SIZE; // return index within the size of hash table
}

bool addAirport(char * name, char * icaoName){
    if(!initialized){
        for(int i = 0; i < HASH_SIZE; i++){
            hashTable[i] = NULL; // initialize hash table to NULL
        }
        initialized = 1; // mark as initialized
    }

    unsigned int index = hashAirport(name); // get hash index
    unsigned int index2 = hashAirport(icaoName); // get hash index for icao

    airportNode * node1 = (airportNode*)malloc(sizeof(airportNode));
    if(!node1){
        return false; // memory allocation failed
    }

    strcpy(node1->civilName, name); // copy civil name into node
    strcpy(node1->icaoName, icaoName); // copy icao name into node
    node1->next = hashTable[index]; // insert at the beginning of the linked list
    hashTable[index] = node1; // update head of the list

    if(index != index2){ // only add second node if indices are different
        airportNode * node2 = (airportNode*)malloc(sizeof(airportNode));
        if(!node2){
            return false; // memory allocation failed
        }

        strcpy(node2->civilName, name); // copy civil name into node
        strcpy(node2->icaoName, icaoName); // copy icao name into node
        node2->next = hashTable[index2]; // insert at the beginning of the linked list
        hashTable[index2] = node2; // update head of the list
        }

    return true;
}

bool checkAirport(char * name_or_icao){

    if(!initialized){
        return false; // hash table not initialized
    }

    unsigned int index = hashAirport(name_or_icao); // get hash index
    airportNode * current = hashTable[index]; // start at head of the linked list

    while(current){
        if(strcmp(current->civilName, name_or_icao) == 0 || strcmp(current->icaoName, name_or_icao) == 0){
            return true; // airport found
        }
        current = current-> next; // moves to the next node
    }

    return false; // airport not found
}

char * convertIcaoToName(char * icao){

    if(!initialized){
        return icao; // hash table not initialized
    }

    unsigned int index = hashAirport(icao); // get hash index
    airportNode * current = hashTable[index]; // start at head of the linked list

    while(current){
        if(strcmp(current->icaoName, icao) == 0){
            return current->civilName; // return civil name if found
        }
        current = current -> next; // moves to the next node
    }

    return icao; // return original icao if not found
}

char * convertNameToIcao(char * name){

    if(!initialized){
        return name; // hash table not initialized
    }

    unsigned int index = hashAirport(name); // get hash index
    airportNode * current = hashTable[index]; // start at head of the linked list

    while(current){
        if(strcmp(current->civilName, name) == 0){
            return current->icaoName; // return icao name if found
        }
        current = current -> next; // moves to the next node
    }

    return name; // return original name if not found
}

