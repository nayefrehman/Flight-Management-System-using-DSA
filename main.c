//
//  main.c
//  PlaneAssignment
//
//  Created by Thomas Dean on 2025-10-13.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "AirportInfo.h"
#include "WaypointInfo.h"
#include "AircraftInfo.h"
#include "FlightPlan.h"

char * AirportName[] = {
    "JFK",
    "LaGuardia",
    "Newark",
    "Teterboro",
    "Logan International",
    "Green International",
    "Bradly International",
    "Albany International",
    "Leigh Vally International",
    "Atlantic City International",
    "Dover AFB",
    "Dulles International",
    "Ronald Regan International",
    "Andrews AFB",
    "Philadelpha Int",
    NULL,
};

char * icao[] = {
    "KJFK",
    "KLGA",
    "KEWR",
    "KTEB",
    "KBOS",
    "KPVD",
    "KBAF",
    "KALB",
    "KABE",
    "KACY",
    "KDOV",
    "KIAD",
    "KDCA",
    "KADW",
    "KPHL",
    NULL,
};

char * waypoints[] = {
    "3NY8",
    "KEPM",
    "GDM",
    "METRO",
    "SWAN",
    "LEEAH",
    "BIGGY",
    "BOPLY",
    "HIKES",
    "DEPDY",
    "GAVEL",
    "CAMMO",
    "BRISS",
    "CREAM",
    "JAFFY",
    "TRANZ",
    "WRENN",
    "MOVFA",
    "CASVI",
    "NECCK",
    "ZUVIV",
    "SARAA",
    "SNOWY",
    "BOYER",
    "BEUTY",
    "DEEDE",
    "FALLZ",
    "TINNI",
    "BORKE",
    "MANTA",
    "FALON",
    "KEYED",
    NULL,
};

char * aircraftTypes[] = {
    "B737",
    "A320",
    "B767",
    "Q400",
    "E195",
    NULL
};

void addAllAirports(char *name[], char *icao[]){
    int airportIndex = 0;
    while(name[airportIndex]!= NULL){
        if (!addAirport(name[airportIndex], icao[airportIndex])){
            fprintf(stderr, "error adding airport %s %s\n",name[airportIndex],icao[airportIndex]);
            exit(1);
        }
        airportIndex++;
    }
}

void addAllWaypoints(char *name[]){
    int waypointIndex = 0;
    while(name[waypointIndex]!= NULL){
        if (!addWaypoint(name[waypointIndex])){
            fprintf(stderr, "error adding waypoint %s\n",name[waypointIndex]);
            exit(1);
        }
        waypointIndex++;
    }
}

void addAllAircraft(char *name[]){
    int aircraftIndex = 0;
    while(name[aircraftIndex]!= NULL){
        if (!addAircraft(name[aircraftIndex])){
            fprintf(stderr, "error adding aircraft type %s\n",name[aircraftIndex]);
            exit(1);
        }
        aircraftIndex++;
    }
}
int main(int argc, const char * argv[]) {
    // insert code here...
    addAllAirports(AirportName, icao);
    addAllWaypoints(waypoints);
    addAllAircraft(aircraftTypes);
    
    // KBOS -> 3NY8 -> KEPM -> KJFK
    unsigned int flight_id;
    if ((flight_id= createFlightPlan("Flight1")) == 0){
        fprintf(stderr, "could not create flight plan Flight1\n");
        exit(1);
    }
    if (setAircraft(flight_id, "NXYZY", "B737")){
        fprintf(stderr, "could not add aircraft to %d\n",flight_id);
        exit(1);
    }
    if (setDeparture(flight_id, "KBOS", "20251114 14:30")){
        fprintf(stderr, "could not set departure for %d\n",flight_id);
        exit(1);
    }
    if (setArrival(flight_id, "JFK", "20251114 17:00")){
        fprintf(stderr, "could not set arrival for %d\n",flight_id);
        exit(1);
    }
    if (addWaypointToFP(flight_id, "3NY8")){
        fprintf(stderr, "could not add waypoint to %d\n",flight_id);
        exit(1);
    }
    if (addWaypointToFP(flight_id, "KEPM")){
        fprintf(stderr, "could not add waypoint to %d\n",flight_id);
        exit(1);
    }
    
    // KBOS -> GDM -> KALB
    if ((flight_id= createFlightPlan("Flight2")) == 0){
        fprintf(stderr, "could not create flight plan Flight2\n");
        exit(1);
    }
    if (setAircraft(flight_id, "NX74W", "Q400")){
        fprintf(stderr, "could not add aircraft to %d\n",flight_id);
        exit(1);
    }
    if (setDeparture(flight_id, "KBOS", "20251114 10:30")){
        fprintf(stderr, "could not set departure for %d\n",flight_id);
        exit(1);
    }
    if (setArrival(flight_id, "KALB", "20251114 11:40")){
        fprintf(stderr, "could not set arrival for %d\n",flight_id);
        exit(1);
    }
    if (addWaypointToFP(flight_id, "GDM")){
        fprintf(stderr, "could not add waypoint to %d\n",flight_id);
        exit(1);
    }

    // KJFK -> METRO -> SWAN -> KDCA
    if ((flight_id= createFlightPlan("Flight3")) == 0){
        fprintf(stderr, "could not create flight plan Flight3\n");
        exit(1);
    }
    if (setAircraft(flight_id, "NUNCW", "Q400")){
        fprintf(stderr, "could not add aircraft to %d\n",flight_id);
        exit(1);
    }
    if (setDeparture(flight_id, "KDCA", "20251114 11:00")){
        fprintf(stderr, "could not set departure for %d\n",flight_id);
        exit(1);
    }
    if (setArrival(flight_id, "KALB", "20251114 13:10")){
        fprintf(stderr, "could not set arrival for %d\n",flight_id);
        exit(1);
    }
    if (addWaypointToFP(flight_id, "METRO")){
        fprintf(stderr, "could not add waypoint to %d\n",flight_id);
        exit(1);
    }
    if (addWaypointToFP(flight_id, "SWAN")){
        fprintf(stderr, "could not add waypoint to %d\n",flight_id);
        exit(1);
    }

    // KACY -> LEEAH -> SWAN -> KDCA
    if ((flight_id= createFlightPlan("Flight4")) == 0){
        fprintf(stderr, "could not create flight plan Flight4\n");
        exit(1);
    }
    if (setAircraft(flight_id, "NUMPY", "Q400")){
        fprintf(stderr, "could not add aircraft to %d\n",flight_id);
        exit(1);
    }
    if (setDeparture(flight_id, "KACY", "20251114 17:00")){
        fprintf(stderr, "could not set departure for %d\n",flight_id);
        exit(1);
    }
    if (setArrival(flight_id, "KDCA", "20251114 18:40")){
        fprintf(stderr, "could not set arrival for %d\n",flight_id);
        exit(1);
    }
    if (addWaypointToFP(flight_id, "LEEAH")){
        fprintf(stderr, "could not add waypoint to %d\n",flight_id);
        exit(1);
    }
    if (addWaypointToFP(flight_id, "SWAN")){
        fprintf(stderr, "could not add waypoint to %d\n",flight_id);
        exit(1);
    }
    
    // reports
    if ((flight_id = getFlightPlan("Flight3")) == 0){
        fprintf(stderr, "could not find flight plan Flight3\n");
        exit(1);
    }
    if (printFlightPlan(flight_id)){
        fprintf(stderr, "could print flight plan %d\n",flight_id);
        exit(1);
    }

    if (printDepartures("KBOS")==0){
        fprintf(stderr, "could print departures for BOSTON\n");
        exit(1);
    }
    
    if (printDepartures("KDCA")==0){
        fprintf(stderr, "could print arrivals for Ronal Regan\n");
        exit(1);
    }
    
    return EXIT_SUCCESS;
}
