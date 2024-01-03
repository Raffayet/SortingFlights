#include <iostream>
#include <FL/Fl.h> // FLTK osnovne funkcije
#include "Flight.h"
#include <vector>
#include "CommandLineArgs.h"
#include "SelectionSort.h"
#include "MyWindow.h" // Uključujemo zaglavlje za MyWindow klasu
#include "DataStorage.h"
#include <vector>
#include "SortingHistory.h"
using std::vector;
using namespace std;

int main(int argc, char* argv[]) {
    CommandLineArgs(argc, argv);
    DataStorage storage(true, CommandLineArgs::getInputPath(), CommandLineArgs::getOutputPath()); // true/false indicating loading 10 flights or more
    std::vector<Flight> flights = storage.loadFlights();

    SortingManager sortingManager;

    SortCriteria sortCriteria = SortCriteria();
    MyWindow myWindow(1000, 850, "Flight Sorter", flights, storage, sortingManager);
    myWindow.setFlights(flights); // Method to pass flight data to the window

    myWindow.show();

    Fl::run();

    while (sortingManager.sortingInProgress()) {
        Fl::wait();
    }

    SortingHistory history(CommandLineArgs::getOutputPath());

    return Fl::run();
}
