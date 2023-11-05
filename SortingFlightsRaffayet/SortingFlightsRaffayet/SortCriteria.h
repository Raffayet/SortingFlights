#ifndef SORTCRITERIA_H
#define SORTCRITERIA_H

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

public:
    SortCriteria(SortField field, SortOrder order)
        : sortField(field), sortOrder(order) {}

    SortField getSortField() const { return sortField; }
    SortOrder getSortOrder() const { return sortOrder; }

    // Možete dodati dodatne metode ako su potrebne
};

#endif // SORTCRITERIA_H
