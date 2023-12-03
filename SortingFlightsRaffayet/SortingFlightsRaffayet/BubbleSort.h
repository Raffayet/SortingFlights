#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "SortAlgorithm.h"

class BubbleSort {
public:
    void sort(std::vector<Flight>& flights, const SortCriteria& criteria) override;
};

#endif // BUBBLESORT_H
