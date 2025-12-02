//
//  FlightPlan.h
//  PlaneAssignment
//
//  Created by Thomas Dean on 2025-11-04.
//

#ifndef FlightPlan_h
#define FlightPlan_h

#include <stdio.h>
#include <stdbool.h>


// returns an ID for the flight plan.
unsigned int createFlightPlan(char * name);
unsigned int getFlightPlan(char * name);
bool setAircraft(unsigned int fplan_id, char * aircraftid, char * aircrafttype);
bool setDeparture(unsigned int fplan_id, char * airport, char * dep_time);
bool setArrival(unsigned int fplan_id, char * airport, char * est_arrival_time);
bool addWaypointToFP(unsigned int fplan_id, char * name);

bool printFlightPlan(unsigned int fplan_id);
bool printDepartures(char * airport);
bool printArrivals(char * airport);

#endif /* FlightPlan_h */
