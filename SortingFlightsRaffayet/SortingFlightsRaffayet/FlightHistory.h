/*
    Informacije prikupljenje prilikom sortiranja letova
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/

#pragma once
#include <vector>
#include <map>
#include "Flight.h"
using namespace std;

class FlightHistory {
public:
    map<int, vector<Flight>> flightMap;
    int comparisonCount;
    int movementCount;
};
