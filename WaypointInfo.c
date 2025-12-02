//
//  WaypointInfo.c
//  PlaneAssignment
//
//  Created by Thomas Dean on 2025-11-04.
//

#include "WaypointInfo.h"
#include <stdlib.h>
#include <string.h>


// define a type struct for waypoint
typedef struct waypointNode{
    char name[20]; // waypoint name with 20 char limit
    struct waypointNode * next; // pointer to next waypoint in the list
} waypointNode;

// hash table for waypoints
static waypointNode *hashTable[50]; 

static int initialized = 0; // to check if hash table is initialized

unsigned int hash(char * str){
    unsigned int sum = 0; // initialize sum 
    for(int i = 0; str[i] != '\0'; i++){ // iterate through the non-empty string
        sum = sum + str[i] * (i+1); // weight by position of the first character being 1
    }
    return sum % 50; // return index within the size of hash table
}

bool addWaypoint(char * name){
    if(!initialized){
        for(int i = 0; i < 50; i++){
            hashTable[i] = NULL; // initialize hash table to NULL
        }
        initialized = 1; // mark as initialized
    }


    unsigned int index = hash(name); // get hash index

    // check if waypoint already exists
    waypointNode* current = hashTable[index];
    while(current){
        if(strcmp(current->name, name) == 0){
            return false; // waypoint already exists
        }
        current = current-> next; // moves to the next node
    }


    waypointNode * newNode = (waypointNode *)malloc(sizeof(waypointNode)); // allocates memory for a new waypoint node
    if(!newNode){
        return false; // memory allocation failed
    }

    strcpy(newNode->name, name); // copy waypoint name into new node
    newNode -> next = hashTable[index]; // insert at the beginning of the linked list
    hashTable[index] = newNode; // update head of the list

    return true;
}

bool checkWaypoint(char * name){
    if(!initialized){
        return false; // hash table not initialized
    }

    unsigned int index = hash(name);  // get hash index
    waypointNode * current = hashTable[index]; // start at head of the linked list

    while(current){
        if(strcmp(current->name, name) == 0){
            return true; // waypoint found
        }
        current = current-> next; // moves to the next node
    }


    return false;
}
