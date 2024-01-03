#include "Flight.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "SortCriteria.h"

bool Flight::compare(const Flight& other) const {
    if (this->departure != other.departure) {
        return this->departure < other.departure;
    }
    else if (this->destination != other.destination) {
        return this->destination < other.destination;
    }
    else if (this->flightNo != other.flightNo) {
        return this->flightNo < other.flightNo;
    }
    else {
        return this->gateNo < other.gateNo;
    }
}

string Flight::getFlightInfo() const {
    return "Flight Number: " + this->flightNo +
        ", Destination: " + this->destination +
        ", Departure Time: " + this->departure +
        ", Gate Number: " + this->gateNo;
}


bool Flight::operator<(const Flight& other) const {
    // Primary comparison on departure time
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

bool compareTimesLess(const std::string& time1, const std::string& time2) {
    std::tm t1 = {};
    std::tm t2 = {};

    std::istringstream ss1(time1);
    std::istringstream ss2(time2);

    ss1 >> std::get_time(&t1, "%H:%M");
    ss2 >> std::get_time(&t2, "%H:%M");

    // Check if parsing was successful
    if (ss1.fail() || ss2.fail()) {
        std::cerr << "Failed to parse time" << std::endl;
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

bool compareTimesMore(const std::string& time1, const std::string& time2) {
    std::tm t1 = {};
    std::tm t2 = {};

    std::istringstream ss1(time1);
    std::istringstream ss2(time2);

    ss1 >> std::get_time(&t1, "%H:%M");
    ss2 >> std::get_time(&t2, "%H:%M");

    // Check if parsing was successful
    if (ss1.fail() || ss2.fail()) {
        std::cerr << "Failed to parse time" << std::endl;
        return false;
    }

    // Compare the times
    if (t1.tm_hour > t2.tm_hour) {
        return true;
    }
    else if (t1.tm_hour == t2.tm_hour && t1.tm_min > t2.tm_min) {
        return true;
    }

    return false;
}

