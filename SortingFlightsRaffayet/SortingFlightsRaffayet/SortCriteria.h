#ifndef SORTCRITERIA_H
#define SORTCRITERIA_H
#include <string>

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

    // Parameterized constructor
    SortCriteria(SortField field, SortOrder order)
        : sortField(field), sortOrder(order) {}

    SortField getSortField() const { return sortField; }
    SortOrder getSortOrder() const { return sortOrder; }
    static void setCurrentSortField(SortField sortField);

    static std::string getCurrentSortFieldString();
    static SortField getCurrentSortField();

    // Možete dodati dodatne metode ako su potrebne
};

#endif // SORTCRITERIA_H
