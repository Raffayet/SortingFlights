#include "SelectionSort.h"

void selectionSort(std::vector<Flight>& flights, const std::string& criterion) {
    // Implementacija
}

void SelectionSort::sort(std::vector<Flight>& flights, const SortCriteria& criteria) {
    size_t n = flights.size();
    for (size_t i = 0; i < n - 1; i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < n; j++) {
            min_idx = j;
        }
        // Swap the found minimum element with the first unsorted element
        std::swap(flights[min_idx], flights[i]);
    }
}

SelectionSort::SelectionSort(std::vector<Flight>& data)
    : flights(data), currentIndex(0), minIndex(0), isComplete(false) {}

void SelectionSort::initialize() {
    currentIndex = 0;
    minIndex = 0;
    isComplete = flights.empty(); // Sorting is complete if there are no flights
}

bool SelectionSort::nextStep() {
    if (isComplete || currentIndex >= flights.size() - 1) {
        isComplete = true;
        return false;
    }

    minIndex = currentIndex;
    for (size_t i = currentIndex + 1; i < flights.size(); ++i) {
        if (flights[i] < flights[minIndex]) {
            minIndex = i;
        }
    }
    if (minIndex != currentIndex) {
        std::swap(flights[currentIndex], flights[minIndex]);
    }
    currentIndex++;

    if (currentIndex >= flights.size() - 1) {
        isComplete = true;
    }

    return true;
}

bool SelectionSort::completed() const {
    return isComplete;
}

std::pair<size_t, size_t> SelectionSort::getLastSwap() const {
    if (currentIndex == 0 || isComplete) {
        return { 0, 0 };
    }
    return { currentIndex - 1, minIndex };
}