#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "SortAlgorithm.h"

class QuickSort : public SortAlgorithm {
public:
    void sort(std::vector<Flight>& flights, const SortCriteria& criteria) override;
private:
    void quickSortHelper(std::vector<Flight>& flights, int low, int high, const SortCriteria& criteria);
    int partition(std::vector<Flight>& flights, int low, int high, const SortCriteria& criteria);
};

#endif // QUICKSORT_H

