//
//  FlightPlan.c
//  PlaneAssignment
//
//  Created by Thomas Dean on 2025-11-04.
//

#include "FlightPlan.h"
#include "AirportInfo.h"
#include "AircraftInfo.h"
#include "WaypointInfo.h"
#include <stdlib.h>
#include <string.h>

// define a struct type for waypoints in flight plan
typedef struct WaypointNode {
    char name[20]; // number of characters in waypoint name
    struct WaypointNode *next; // pointer to the next waypoint node 
} WaypointNode;


// define a struct type for flight plans
typedef struct FlightPlan {
    unsigned int id; // unique flight plan ID
    char name[50]; // number of characters in flight plan name
    char aircraftId[10]; // aircraft ID with 10 characters
    char aircraftType[20]; // aircraft type with 20 characters
    char departureAirport[10]; // departure airport ICAO code with 10 characters
    char departureTime[20]; // departure time with 20 characters
    char arrivalAirport[10]; // arrival airport ICAO code with 10 characters
    char arrivalTime[20]; // arrival time with 20 characters
    WaypointNode *waypointsHead; // pointer to the head of the waypoints linked list
    struct FlightPlan *next; // pointer to the next flight plan node
} FlightPlan;

// head pointer for the linked list of flight plans
static FlightPlan *flightPlansHead = NULL;
static unsigned int nextId = 1; // variable to generate unique flight plan IDs

// Function implementations
unsigned int createFlightPlan(char *name) {
    FlightPlan *current = flightPlansHead; // start at head of flight plans list
    // while loop to check for existing flight plan with the same name 
    while (current) {
        if (strcmp(current->name, name) == 0) { // if the name matches
            return 0; // return 0 indicating a failure to create
        }
        current = current->next; // moves to the next flight plan node
    }

    // allocate memory for a new flight plan
    FlightPlan *newPlan = (FlightPlan *)malloc(sizeof(FlightPlan));
    if (!newPlan) { 
        return 0; // memory allocation failed
    }

    newPlan->id = nextId++; // assign unique ID and increment for next 
    strcpy(newPlan->name, name); // copy the name into the new flight plan
    newPlan->aircraftId[0] = '\0'; // initialize aircraft ID to empty string
    newPlan->aircraftType[0] = '\0'; // initialize aircraft type to empty string 
    newPlan->departureAirport[0] = '\0'; // initialize departure airport to empty string
    newPlan->departureTime[0] = '\0'; // initialize departure time to empty string
    newPlan->arrivalAirport[0] = '\0'; // initialize arrival airport to empty string
    newPlan->arrivalTime[0] = '\0'; // initialize arrival time to empty string
    newPlan->waypointsHead = NULL; // initialize waypoints head to NULL
    newPlan->next = flightPlansHead; // link new plan to the current head of the list
    flightPlansHead = newPlan; // update the head to the new flight plan

    return newPlan->id; // return the unique ID of the new flight plan 
}

// Function to get flight plan ID by name
unsigned int getFlightPlan(char *name) {
    FlightPlan *current = flightPlansHead; // start at the head of the flight plan linked list

 // while loop which iterates and checks for matching name 
    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current->id; // return the flight id if name matches
        }
        current = current->next; // moves on to the next flight plan node 
    }

    return 0;
}

// Function to set aircraft for a flight plan
bool setAircraft(unsigned int fplan_id, char *aircraftid, char *aircrafttype) {
    // check if aircraft ID and type are valid 
    if (!checkAircraft(aircrafttype)) {
        return false; // invalid aircraft type
    }

    FlightPlan *current = flightPlansHead; // set the current ptr to the head of flight plan list
    while (current) { // iterate through the flight plan linked list
        if (current->id == fplan_id) { // if the flight plan ID matches
            strcpy(current->aircraftId, aircraftid); // copy the aircraft ID
            strcpy(current->aircraftType, aircrafttype); // copy the aircraft type
            return true;
        }
        current = current->next; // move to the next flight plan node
    }

    return false;
}

// func to set departure info for a flight plan
bool setDeparture(unsigned int fplan_id, char *airport, char *dep_time) {
    if (!checkAirport(airport)) { // check if airport is valid 
        return false; 
    }

    // iterate through flight plans to find matching ID
    FlightPlan *current = flightPlansHead; // set current ptr to head of flight plan list 
    while (current) { 
        if (current->id == fplan_id) { // is id matches
            strcpy(current->departureAirport, convertNameToIcao(airport)); // convert and copy airport icao name 
            strcpy(current->departureTime, dep_time); // copy departure time
            return true;
        }
        current = current->next; // move to the next flight plan node
    }

    return false;
}

// func to set arrival info for a flight plan
bool setArrival(unsigned int fplan_id, char *airport, char *est_arrival_time) {
    if (!checkAirport(airport)) { // check if airport is valid 
        return false; // return false is not valid 
    } 

    // again we set current ptr to head of flight plan list
    FlightPlan *current = flightPlansHead;
    while (current) {
        // iterate through flight plans to find matching id 
        if (current->id == fplan_id) { // if the id matches
            strcpy(current->arrivalAirport, convertNameToIcao(airport)); // convert icao to civil name and copy
            strcpy(current->arrivalTime, est_arrival_time); // copy estimated arrival time 
            return true;
        }
        current = current->next; // move to the next flight plan node 
    }

    return false;
}

// func to add waypoint to flight plan
bool addWaypointToFP(unsigned int fplan_id, char *name) {
    if (!checkWaypoint(name)) {
        return false; // return false if waypoint is not valid 
    }

    // set current ptr to head of flight plan list
    FlightPlan *current = flightPlansHead;
    while (current) {
        // iterate through flight plans to find matching id 
        if (current->id == fplan_id) { // if the id matches 
            WaypointNode *newWaypoint = (WaypointNode *)malloc(sizeof(WaypointNode)); // allocate memory for new waypoint 
            if (!newWaypoint) {
                return false; // return false if memory allocation fails
            }

            strcpy(newWaypoint->name, name); // copy waypoint name into new waypoint node
            newWaypoint->next = NULL; // initialize next pointer to NULL

            if (!current->waypointsHead) {
                current->waypointsHead = newWaypoint; // if no waypoints, set head to new waypoint 
            } else {
                WaypointNode *temp = current->waypointsHead; // otherwise, traverse to the end of the waypoint list 
                // traverse to the last waypoint node
                while (temp->next) {
                    temp = temp->next; // move to the next waypoint node 
                }
                temp->next = newWaypoint; // add new waypoint at the end of the list
            }

            return true;
        }
        current = current->next; // move to the next flight plan node
    }

    return false;
}

// func to print flight plan details
bool printFlightPlan(unsigned int fplan_id) {
    FlightPlan *current = flightPlansHead; // set current ptr to head of flight plan list 
     // iterate through flight plans to find matching id

    while (current) {
        if (current->id == fplan_id) { // if the id matches 
            printf("Flight Plan: %s\n", current->name); // print flight plan name
            printf("Aircraft: %s (%s)\n", current->aircraftId, current->aircraftType); // print aircraft details
            printf("Departure: %s at %s\n", current->departureAirport, current->departureTime); // print departure info
            printf("Arrival: %s at %s\n", current->arrivalAirport, current->arrivalTime); // print arrival info
            printf("Waypoints: ");

            WaypointNode *wp = current->waypointsHead; // set pointer to head of waypoint list
            while (wp) { // iterate through waypoints
                printf("%s", wp->name);
                if (wp->next) { // if there is a next waypoint
                    printf(" -> ");
                }
                wp = wp->next; // move to the next waypoint node
            }
            printf("\n\n"); // print a newline for better readability

            return true;
        }
        current = current->next; // move to the next flight plan node
    }

    return false;
}

// func to print departures from a specific airport
bool printDepartures(char *airport) {
    char *icaoName = convertNameToIcao(airport); // convert civil name to icao name

    printf("Departures from %s:\n", icaoName); 

    FlightPlan *planArray[100]; // array to hold flight plans 
    int planCount = 0; // counter for number of flight plans

    FlightPlan *current = flightPlansHead; // set the current ptr to head of flight plan list 
    while (current) { // iterate through flight plans 
        if (strcmp(current->departureAirport, icaoName) == 0) { // if departure airport matches 
            planArray[planCount++] = current;
        }
        current = current->next; // move to the next flight plan node
    }
 
    // sort the flight plans by departure time using bubble sort
    int i, j;
    for (i = 0; i < planCount - 1; i++) {
        for (j = 0; j < planCount - i - 1; j++) {
            if (strcmp(planArray[j]->departureTime, planArray[j + 1]->departureTime) > 0) {
                FlightPlan *temp = planArray[j];
                planArray[j] = planArray[j + 1];
                planArray[j + 1] = temp;
            }
        }
    }

    // print the sorted flight plans
    for (i = 0; i < planCount; i++) {
        printf("  %s - %s to %s at %s\n",
               planArray[i]->name,
               planArray[i]->aircraftType,
               planArray[i]->arrivalAirport,
               planArray[i]->departureTime);
    }

    printf("\n");

    return planCount > 0;
}

// func to print arrivals at a specific airport
bool printArrivals(char *airport) {
    char *icaoName = convertNameToIcao(airport); // convert civil name to icao name 

    printf("Arrivals at %s:\n", icaoName);

    FlightPlan *planArray[100]; // array to hold flight plans
    int planCount = 0; // counter for number of flight plans

    FlightPlan *current = flightPlansHead; // set the current ptr to head of flight plan list 
    while (current) { // iterate through flight plans 
        if (strcmp(current->arrivalAirport, icaoName) == 0) { // if arrival airport matches 
            planArray[planCount++] = current; // add to plan array 
        }
        current = current->next; // move to the next flight plan node
    }

    // sort the flight plans by arrival time using bubble sort
    int i, j;
    for (i = 0; i < planCount - 1; i++) {
        for (j = 0; j < planCount - i - 1; j++) {
            if (strcmp(planArray[j]->arrivalTime, planArray[j + 1]->arrivalTime) > 0) {
                FlightPlan *temp = planArray[j];
                planArray[j] = planArray[j + 1];
                planArray[j + 1] = temp;
            }
        }
    }

    // print the sorted flight plans
    for (i = 0; i < planCount; i++) {
        printf("  %s - %s from %s at %s\n",
               planArray[i]->name,
               planArray[i]->aircraftType,
               planArray[i]->departureAirport,
               planArray[i]->arrivalTime);
    }

    printf("\n"); // print a newline for better readability

    return planCount > 0;
}