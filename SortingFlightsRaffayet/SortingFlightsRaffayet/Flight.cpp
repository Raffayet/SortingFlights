#include "Flight.h"

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