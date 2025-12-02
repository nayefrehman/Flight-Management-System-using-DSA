cmake_minimum_required(VERSION 3.26)
project(assignment C)

set(CMAKE_C_STANDARD 11)

# Add the executable
add_executable(assignment main.c AircraftInfo.c AirportInfo.c WaypointInfo.c FlightPlan.c)

# Include directories for header files
target_include_directories(assignment PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
