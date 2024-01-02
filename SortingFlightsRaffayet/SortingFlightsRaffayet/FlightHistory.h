#pragma once
#include <vector>
#include <map>
#include "Flight.h"

class FlightHistory {
public:
    std::map<int, std::vector<Flight>> flightMap;
    int comparisonCount;
    int movementCount;
};
