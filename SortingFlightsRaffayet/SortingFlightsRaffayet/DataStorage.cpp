#include "DataStorage.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <map>
using namespace std;
using std::vector;
using std::string;

DataStorage::DataStorage(bool limitToTen, std::string flightsDataPath, std::string flightsHistoryPath) {
    this->flightsDataPath = flightsDataPath;
    this->flightsHistoryPath = flightsHistoryPath;
    this->limitToTen = limitToTen;
}

void DataStorage::addFlight(const Flight& flight) {
    loadedFlights.push_back(flight);
}

vector<Flight>& DataStorage::loadFlights() {
    loadedFlights.clear();
    std::ifstream file(flightsDataPath);
    if (file.is_open()) {
        std::string line;

        std::getline(file, line);

        int count = 0;

        while (std::getline(file, line)) {
            if (count >= 10 && this->limitToTen == true) { // no limit if limitToTen params is false (testing purposes)
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

void DataStorage::writeSortedFlightHistoryToFile(const std::string& filename, FlightHistory flightHistory) {
    std::ofstream outFile(filename);

    if (outFile.is_open()) {
        for (const auto& entry : flightHistory.flightMap) {
            outFile << "Sort Count " << entry.first << ":\n";
            for (const auto& flight : entry.second) {
                outFile << flight.getFlightInfo() << "\n";
            }
            outFile << "\n"; // Add a blank line between different sort counts
        }
        outFile << "Number of comparisons: " << flightHistory.comparisonCount << endl;
        outFile << "Number of movements: " << flightHistory.movementCount << endl;
        outFile.close();
    }
    else {
        std::cerr << "Unable to open file for writing: " << filename << "\n";
    }
}
