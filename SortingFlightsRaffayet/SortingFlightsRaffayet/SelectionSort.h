#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <vector>
#include "Flight.h"
#include "SortCriteria.h"

class SelectionSort {
private:
    std::vector<Flight>& flights;
    size_t currentIndex;
    size_t minIndex;
    bool isComplete;
public:
    explicit SelectionSort(std::vector<Flight>& data);

    // Initializes the variables needed for the sort
    void initialize();

    // Performs a single step of the selection sort
    bool nextStep();

    // Checks if the sorting is complete
    bool completed() const;

    // Gets the last swap indices
    std::pair<size_t, size_t> getLastSwap() const;
    virtual void sort(std::vector<Flight>& flights, const SortCriteria& criteria) = 0;
    virtual ~SelectionSort() {}
};

// Ovde možete dodati dodatne algoritme za sortiranje ako je potrebno.

#endif // SELECTION_SORT_H

