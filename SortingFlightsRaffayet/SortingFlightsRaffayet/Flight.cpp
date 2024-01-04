/*
    Model klasa za let - Implementacija
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/

#include "Flight.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "SortCriteria.h"
using namespace std;

/*
    Funkcija za ucitavanje "light" informacija o letu
*/
string Flight::getFlightInfo() const {
    return "Flight Number: " + this->flightNo +
        ", Destination: " + this->destination +
        ", Departure Time: " + this->departure +
        ", Gate Number: " + this->gateNo;
}

/*
    Override operator< funkcija za poredjenje dva objekta po operatoru <
*/
bool Flight::operator<(const Flight& other) const {
    if (SortCriteria::getCurrentSortField() == SortField::DepartureTime) {
        if (compareTimesLess(this->departure, other.departure)) {
            return true;
        }
    }
    
    else if (SortCriteria::getCurrentSortField() == SortField::FlightNumber) {
        if (flightNo < other.flightNo) {
            return true;
        }
    }

    else if (SortCriteria::getCurrentSortField() == SortField::Destination) {
        if (destination < other.destination) {
            return true;
        }
    }

    else if (SortCriteria::getCurrentSortField() == SortField::GateNumber) {
        return gateNo < other.gateNo;
    }
    
    else {
        if (compareTimesLess(this->departure, other.departure)) {
            return true;
        }
    }
    return false;
}


/*
    Override operator> funkcija za poredjenje dva objekta po operatoru >
*/
bool Flight::operator>(const Flight& other) const {
    if (SortCriteria::getCurrentSortField() == SortField::DepartureTime) {
        if (compareTimesMore(this->departure, other.departure)) {
            return true;
        }
    }
    else if (SortCriteria::getCurrentSortField() == SortField::FlightNumber) {
        if (flightNo > other.flightNo) {
            return true;
        }
    }

    else if (SortCriteria::getCurrentSortField() == SortField::Destination) {
        if (destination > other.destination) {
            return true;
        }
    }

    else if (SortCriteria::getCurrentSortField() == SortField::GateNumber) {
        return gateNo > other.gateNo;
    }

    else {
        if (compareTimesLess(this->departure, other.departure)) {
            return true;
        }
    }
    return false;
}


/*
    Override operator< funkcija za poredjenje dva objekta po operatoru < na osnovu poredjenja dva broja
*/
bool compareTimesLess(const string& time1, const string& time2) {
    tm t1 = {};
    tm t2 = {};

    istringstream ss1(time1);
    istringstream ss2(time2);

    ss1 >> get_time(&t1, "%H:%M");
    ss2 >> get_time(&t2, "%H:%M");

    // Check if parsing was successful
    if (ss1.fail() || ss2.fail()) {
        cerr << "Failed to parse time" << endl;
        return false;
    }

    // Compare the times
    if (t1.tm_hour < t2.tm_hour) {
        return true;
    }
    else if (t1.tm_hour == t2.tm_hour && t1.tm_min < t2.tm_min) {
        return true;
    }

    return false;
}

/*
    Override operator> funkcija za poredjenje dva objekta po operatoru > na osnovu poredjenja dva broja
*/
bool compareTimesMore(const string& time1, const string& time2) {
    tm t1 = {};
    tm t2 = {};

    istringstream ss1(time1);
    istringstream ss2(time2);

    ss1 >> get_time(&t1, "%H:%M");
    ss2 >> get_time(&t2, "%H:%M");

    if (ss1.fail() || ss2.fail()) {
        cerr << "Failed to parse time" << endl;
        return false;
    }

    if (t1.tm_hour > t2.tm_hour) {
        return true;
    }
    else if (t1.tm_hour == t2.tm_hour && t1.tm_min > t2.tm_min) {
        return true;
    }

    return false;
}

