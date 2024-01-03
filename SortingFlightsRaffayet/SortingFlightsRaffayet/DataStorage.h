#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <vector>
#include "Flight.h"
#include "SelectionSort.h"
#include <string>
#include <map>
#include "FlightHistory.h"
using namespace std;
using std::vector;

class DataStorage {
public:
    std::string flightsDataPath;
    std::string flightsHistoryPath;
    bool limitToTen;

    DataStorage(bool limitToTen, std::string flightsDataPath, std::string flightsHistoryPath);

    void addFlight(const Flight& flight);
    vector<Flight>& loadFlights();
    void selectionSortFlights(const SortCriteria& criteria, SelectionSort& selectionSort);
    void saveToFile(const std::string& filename) const;
    void printFlights();
    static void writeSortedFlightHistoryToFile(const std::string& filename, FlightHistory flightHistory);

private:
    vector<Flight> loadedFlights;
};

#endif // DATASTORAGE_H
