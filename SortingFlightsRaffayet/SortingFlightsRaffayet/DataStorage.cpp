#include "DataStorage.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
using std::vector;
using std::string;

const string DataStorage::flightsDataPath = "flights.txt";

DataStorage::DataStorage(bool limitToTen) {
    std::ifstream file(flightsDataPath);
    if (file.is_open()) {
        std::string line;

        std::getline(file, line);

        int count = 0;

        while (std::getline(file, line)) {
            if (count >= 10 && limitToTen == true) { // no limit if limitToTen params is false (testing purposes)
                break;
            }
            std::istringstream iss(line);
            std::string flightNo, destination, departure, gateNo;

            std::getline(iss, flightNo, ';');
            std::getline(iss, destination, ';');
            std::getline(iss, departure, ';');
            std::getline(iss, gateNo, ';');

            Flight flight(flightNo, destination, departure, gateNo);
            loadedFlights.push_back(flight);

            ++count;
        }
        file.close();
    }
}


void DataStorage::addFlight(const Flight& flight) {
    loadedFlights.push_back(flight);
}

const vector<Flight>& DataStorage::loadFlights() const {
    return loadedFlights;
}

void DataStorage::selectionSortFlights(const SortCriteria& criteria, SelectionSort& selectionSort) {
    selectionSort.sort(loadedFlights, criteria);
}

void DataStorage::saveToFile(const std::string& filename) const {
    // Implement if needed
}

void DataStorage::printFlights() {

    for (const auto& flight : loadedFlights) {
        std::cout << "Flight Number: " << flight.flightNo
            << ", Destination: " << flight.destination
            << ", Departure Time: " << flight.departure
            << ", Gate Number: " << flight.gateNo << std::endl;
    }
}
