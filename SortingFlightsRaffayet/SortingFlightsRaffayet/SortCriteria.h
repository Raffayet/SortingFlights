/*
    Enumeracije kriterijuma sortiranja koji su se koristili u ovom projektu
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/

#ifndef SORTCRITERIA_H
#define SORTCRITERIA_H
#include <string>
using namespace std;

enum class SortField {
    DepartureTime,
    Destination,
    FlightNumber,
    GateNumber
};

enum class SortOrder {
    Ascending,
    Descending
};

class SortCriteria {
private:
    SortField sortField;
    SortOrder sortOrder;
    static SortField currentSortField;

public:
    // Default constructor
    SortCriteria() : sortField(SortField::DepartureTime), sortOrder(SortOrder::Ascending) {}

    SortCriteria(SortField field): sortField(field), sortOrder(SortOrder::Ascending) {}

    SortCriteria(SortField field, SortOrder order)
        : sortField(field), sortOrder(order) {}

    SortField getSortField() const { return sortField; }
    SortOrder getSortOrder() const { return sortOrder; }
    static void setCurrentSortField(SortField sortField);

    static string getCurrentSortFieldString();
    static SortField getCurrentSortField();
};

#endif // SORTCRITERIA_H
