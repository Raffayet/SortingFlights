/*
    Repozitorijum za upravljanje podacima o letovima - upis, citanje, printovanje itd..
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/

#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <vector>
#include "Flight.h"
#include <string>
#include <map>
#include "FlightHistory.h"
using namespace std;

class DataStorage {
public:
    string flightsDataPath;
    string flightsHistoryPath;
    bool limitToTen;
    const int numberOfRepresentingFlights = 10;

    DataStorage(bool limitToTen, string flightsDataPath, string flightsHistoryPath);

    void addFlight(const Flight& flight);
    vector<Flight>& loadFlights();
    void saveToFile(const string& filename) const;
    void printFlights();
    static void writeSortedFlightHistoryToFile(const string& filename, FlightHistory flightHistory);

private:
    vector<Flight> loadedFlights;
};

#endif // DATASTORAGE_H
