#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <vector>
#include "Flight.h"
#include "SortAlgorithm.h"

class DataStorage {
public:
    DataStorage();

    void addFlight(const Flight& flight);
    const std::vector<Flight>& getFlights() const;
    void sortFlights(const SortCriteria& criteria, SortAlgorithm& algorithm);
    void saveToFile(const std::string& filename) const;

private:
    std::vector<Flight> flights;
};

#endif // DATASTORAGE_H

