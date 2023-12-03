#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <vector>
#include "Flight.h"
#include "SelectionSort.h"
#include <string>
using std::vector;

class DataStorage {
public:
    static const std::string flightsDataPath;

    DataStorage(bool limitToTen);

    void addFlight(const Flight& flight);
    const vector<Flight>& loadFlights() const;
    void selectionSortFlights(const SortCriteria& criteria, SelectionSort& selectionSort);
    void saveToFile(const std::string& filename) const;
    void printFlights();

private:
    vector<Flight> loadedFlights;
};

#endif // DATASTORAGE_H
