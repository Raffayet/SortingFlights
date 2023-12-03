#include "BubbleSort.h"

void BubbleSort::sort(std::vector<Flight>& flights, const SortCriteria& criteria) {
    bool swapped;
    do {
        swapped = false;
        for (size_t i = 1; i < flights.size(); i++) {
            // Предпоставка да је compare функција подешена да упоређује на основу критеријума
            if (flights[i - 1].compare(flights[i])) {
                std::swap(flights[i - 1], flights[i]);
                swapped = true;
            }
        }
    } while (swapped);
}
