#include "SortCriteria.h"

SortField SortCriteria::currentSortField = SortField::DepartureTime; // Static member definition

void SortCriteria::setCurrentSortField(SortField sortField) {
    currentSortField = sortField;
}

std::string SortCriteria::getCurrentSortFieldString() {
    switch (currentSortField) {
    case SortField::DepartureTime:
        return "Departure Time";
    case SortField::Destination:
        return "Destination";
    case SortField::FlightNumber:
        return "Flight Number";
    case SortField::GateNumber:
        return "Gate Number";
    default:
        return "Unknown Field";
    }
}