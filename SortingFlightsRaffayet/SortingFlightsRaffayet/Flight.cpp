#include "Flight.h"

Flight::Flight(std::string fNo, std::string dest, std::string depart, std::string gNo)
    : flightNo(fNo), destination(dest), departure(depart), gateNo(gNo) {}