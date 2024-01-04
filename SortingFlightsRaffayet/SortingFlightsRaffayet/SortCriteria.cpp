/*
    Enumeracije kriterijuma sortiranja koji su se koristili u ovom projektu - Implementacija
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/

#include "SortCriteria.h"
using namespace std;

SortField SortCriteria::currentSortField = SortField::DepartureTime;

void SortCriteria::setCurrentSortField(SortField sortField) {
    currentSortField = sortField;
}

SortField SortCriteria::getCurrentSortField() {
    return currentSortField;
}


string SortCriteria::getCurrentSortFieldString() {
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