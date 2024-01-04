/*
    Repozitorijum za upravljanje podacima o letovima - upis, citanje, printovanje itd.. - Implementacija
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/

#include "DataStorage.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <map>
using namespace std;

/*
    bool limitToTen - flag koji oznacava da li se ucitava samo 10 letova za reprezentaciju ili svi letovi iz fajla
    flightsDataPath - putanja do fajla u kom se nalaze svi letovi za ucitavanje
    flightsHistoryPath - putanja do fajla koji cuva svako stanje letova prilikom sortiranja
*/
DataStorage::DataStorage(bool limitToTen, string flightsDataPath, string flightsHistoryPath) {
    this->flightsDataPath = flightsDataPath;
    this->flightsHistoryPath = flightsHistoryPath;
    this->limitToTen = limitToTen; 
}

void DataStorage::addFlight(const Flight& flight) {
    loadedFlights.push_back(flight);
}

vector<Flight>& DataStorage::loadFlights() {
    loadedFlights.clear();
    ifstream file(flightsDataPath);
    if (file.is_open()) {
        string line;

        getline(file, line);

        int count = 0;

        while (getline(file, line)) {
            if (count >= numberOfRepresentingFlights && this->limitToTen == true) {
                break;
            }
            istringstream iss(line);
            string flightNo, destination, departure, gateNo;

            getline(iss, flightNo, ';');
            getline(iss, destination, ';');
            getline(iss, departure, ';');
            getline(iss, gateNo, ';');

            Flight flight(flightNo, destination, departure, gateNo);
            loadedFlights.push_back(flight);

            ++count;
        }
        file.close();
    }
    return loadedFlights;
}

//Pomocna funkcija za printovanje objekata tipa Flight
void DataStorage::printFlights() { 

    for (const auto& flight : loadedFlights) {
        cout << "Flight Number: " << flight.flightNo
            << ", Destination: " << flight.destination
            << ", Departure Time: " << flight.departure
            << ", Gate Number: " << flight.gateNo << endl;
    }
}

//Posle svake iteracije sortiranja, stanje letova se cuva u ovom fajlu
void DataStorage::writeSortedFlightHistoryToFile(const string& filename, FlightHistory flightHistory) {
    ofstream outFile(filename);

    if (outFile.is_open()) {
        for (const auto& entry : flightHistory.flightMap) {
            outFile << "Sort Count " << entry.first << ":\n";
            for (const auto& flight : entry.second) {
                outFile << flight.getFlightInfo() << "\n";
            }
            outFile << "\n";
        }
        outFile << "Number of comparisons: " << flightHistory.comparisonCount << endl;
        outFile << "Number of movements: " << flightHistory.movementCount << endl;
        outFile.close();
    }
    else {
        cerr << "Unable to open file for writing: " << filename << "\n";
    }
}
