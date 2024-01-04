/*
    Model klasa za let
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/

#ifndef FLIGHT_H
#define FLIGHT_H
#include <string>
using namespace std;

class Flight {
    public:
        string flightNo;
        string destination;
        string departure;
        string gateNo;
        Flight(const string& flightNo, const string& destination,
            const string& departure, const string& gateNo)
            : flightNo(flightNo), destination(destination), departure(departure), gateNo(gateNo) {}
  
        bool operator<(const Flight& other) const;
        bool operator>(const Flight& other) const;
        string getFlightInfo() const;


};
bool compareTimesLess(const string& time1, const string& time2);  // funkcija koja imitira operator < na osnovu poredjenja dva broja
bool compareTimesMore(const string& time1, const string& time2);  // funkcija koja imitira operator > na osnovu poredjenja dva broja
#endif // FLIGHT_H