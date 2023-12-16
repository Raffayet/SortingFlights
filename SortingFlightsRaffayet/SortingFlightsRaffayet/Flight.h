#ifndef FLIGHT_H
#define FLIGHT_H
#include <string>
using std::string;

class Flight {
    public:
        string flightNo;
        string destination;
        string departure;
        string gateNo;
        Flight(const string& flightNo, const string& destination,
            const string& departure, const string& gateNo)
            : flightNo(flightNo), destination(destination), departure(departure), gateNo(gateNo) {}

        bool compare(const Flight& other) const;    
        bool operator<(const Flight& other) const;
        string getFlightInfo() const;


};
bool compareTimes(const std::string& time1, const std::string& time2);  // Declare as standalone
#endif // FLIGHT_H