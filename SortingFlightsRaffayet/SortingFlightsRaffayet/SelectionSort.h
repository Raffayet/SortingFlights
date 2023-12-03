#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <vector>
#include "Flight.h"
#include "SortCriteria.h"

class SelectionSort {
public:
    virtual void sort(std::vector<Flight>& flights, const SortCriteria& criteria) = 0;
    virtual ~SelectionSort() {}
};

// Ovde možete dodati dodatne algoritme za sortiranje ako je potrebno.

#endif // SELECTION_SORT_H

