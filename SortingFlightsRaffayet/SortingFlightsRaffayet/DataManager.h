#pragma once
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <vector>
#include "Flight.h"
#include "FlightSorter.h"

std::vector<Flight> loadFlights(const std::string& filePath);
void writeToFile(const std::string& filePath, const std::vector<SortInfo>& sortData);

#endif