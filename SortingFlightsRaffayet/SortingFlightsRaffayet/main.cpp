#include <iostream>
#include <FL/Fl.h> // FLTK osnovne funkcije
#include "Flight.h"
#include <vector>
#include "CommandLineArgs.h"
#include "SelectionSort.h"
#include "MyWindow.h" // Uključujemo zaglavlje za MyWindow klasu
#include "DataStorage.h"
#include <vector>
using std::vector;

int main(int argc, char* argv[]) {
    CommandLineArgs args(argc, argv);

    DataStorage storage(true);
    vector<Flight> flights = storage.loadFlights(); // Load flights

    // Assuming SortAlgorithm is properly implemented and create method exists
    /*SortAlgorithm* sortAlgorithm = SortAlgorithm::create(args.getSortAlgorithm());
    sortAlgorithm->sort(flights);*/
    MyWindow myWindow(1000, 700, "Flight Sorter", flights);
    myWindow.setFlights(flights); // Method to pass flight data to the window

    myWindow.show(); // Show window
    return Fl::run(); // Start FLTK event loop
}
