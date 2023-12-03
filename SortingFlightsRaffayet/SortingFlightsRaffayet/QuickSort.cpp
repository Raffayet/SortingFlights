#include "QuickSort.h"

void QuickSort::sort(std::vector<Flight>& flights, const SortCriteria& criteria) {
    quickSortHelper(flights, 0, flights.size() - 1, criteria);
}

void QuickSort::quickSortHelper(std::vector<Flight>& flights, size_t low, size_t high, const SortCriteria& criteria) {
    if (low < high) {
        size_t pi = partition(flights, low, high, criteria);
        quickSortHelper(flights, low, pi - 1, criteria);
        quickSortHelper(flights, pi + 1, high, criteria);
    }
}

size_t QuickSort::partition(std::vector<Flight>& flights, size_t low, size_t high, const SortCriteria& criteria) {
    Flight pivot = flights[high];
    size_t i = (low - 1);

    for (size_t j = low; j <= high - 1; j++) {
        if (flights[j].compare(pivot)) {
            i++;
            std::swap(flights[i], flights[j]);
        }
    }
    std::swap(flights[i + 1], flights[high]);
    return (i + 1);
}

