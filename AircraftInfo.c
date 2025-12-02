//
//  AircraftInfo.c
//  PlaneAssignment
//
//  Created by Thomas Dean on 2025-11-04.
//

#include "AircraftInfo.h"
#include <stdlib.h>
#include <string.h>

// maximum number of aircraft that can be stored, for later additions
#define MAX_AIRCRAFT 50

// static storage for aircraft names, can store up to MAX_AIRCRAFT (50) aircraft with
// up to 19 character names
static char aircraftList[MAX_AIRCRAFT][20];

// counter for number of aircraft added
static char aircraftCounter = 0; 

bool addAircraft(char * name){
    if(aircraftCounter >= MAX_AIRCRAFT){
        return false; // cannot add more aircraft
    }

    // check for duplicate aircrafts
    for(int i = 0; i < aircraftCounter; i++){
        if(strcmp(aircraftList[i], name) == 0){
            return false; // duplicate found
        }
    }


    // we copy the name into our storage and increment the counter
    strcpy(aircraftList[aircraftCounter], name);
    aircraftCounter++; // increment the count of aircraft
    
    return true;
}

// this function checks if an aircraft exists in our storage
bool checkAircraft(char * name){
    // loop through all added aircraft and compare names
    for(int i = 0; i < aircraftCounter; i++){
        if(strcmp(aircraftList[i], name) == 0){
            return true; // found the aircraft
        }
    }
    return false;
}

