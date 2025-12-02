//
//  FlightPlan.c
//  PlaneAssignment
//
//  Created by Thomas Dean on 2025-11-04.
//

#include "AirportInfo.h"
#include "AircraftInfo.h"
#include "WaypointInfo.h"
#include "FlightPlan.h"



unsigned int createFlightPlan(char * name){
    return 0;
}

unsigned int getFlightPlan(char * name){
    return 0;
}


bool setAircraft(unsigned int fplan_id, char * aircraftid, char * aircrafttype){
    return false;
}

bool setDeparture(unsigned int fplan_id, char * airport, char * dep_time){
    return false;
}

bool setArrival(unsigned int fplan_id, char * airport, char * est_arrival_time){
    return false;
}

bool addWaypointToFP(unsigned int fplan_id, char * name){
    return false;
}


bool printFlightPlan(unsigned int fplan_id){
    return false;
}

bool printDepartures(char * airport){
    return false;
}

bool printArrivals(char * airport){
    return false;
}

