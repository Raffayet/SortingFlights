#ifndef SORTALGORITHM_H
#define SORTALGORITHM_H

#include <vector>
#include "Flight.h"
#include "SortCriteria.h"

class SortAlgorithm {
public:
    virtual void sort(std::vector<Flight>& flights, const SortCriteria& criteria) = 0;
    virtual ~SortAlgorithm() {}
};

class BubbleSort : public SortAlgorithm {
public:
    void sort(std::vector<Flight>& flights, const SortCriteria& criteria) override;
};

class SelectionSort : public SortAlgorithm {
public:
    void sort(std::vector<Flight>& flights, const SortCriteria& criteria) override;
};

// Ovde možete dodati dodatne algoritme za sortiranje ako je potrebno.

#endif // SORTALGORITHM_H

