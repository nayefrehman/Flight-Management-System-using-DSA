//
//  AirportInfo.h
//  PlaneAssignment
//
//  Created by Thomas Dean on 2025-10-13.
//

#ifndef AirportInfo_h
#define AirportInfo_h

#include <stdbool.h>
#include <stdio.h>

bool addAirport(char * name, char * icaoName);
bool checkAirport(char * name_or_icao);
char * convertIcaoToName(char * name);
char * convertNameToIcao(char * name);

#endif /* AirportInfo_h */
