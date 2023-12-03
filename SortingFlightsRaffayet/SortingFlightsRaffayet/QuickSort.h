#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <cstddef> // For size_t
#include <vector>
#include "Flight.h"
#include "SortCriteria.h"

class QuickSort {
public:
    virtual void sort(std::vector<Flight>& flights, const SortCriteria& criteria) = 0;
private:
    void quickSortHelper(std::vector<Flight>& flights, size_t low, size_t high, const SortCriteria& criteria);
    size_t partition(std::vector<Flight>& flights, size_t low, size_t high, const SortCriteria& criteria);
};

#endif // QUICKSORT_H
