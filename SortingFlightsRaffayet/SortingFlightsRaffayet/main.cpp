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
using namespace std;

int main(int argc, char* argv[]) {
    CommandLineArgs(argc, argv);
    DataStorage::flightsDataPath = CommandLineArgs::getInputPath();
    DataStorage::flightsHistoryPath = CommandLineArgs::getOutputPath();
    
    std::cout << "Number of arguments: " << argc << std::endl;

    // Iterate through the argument list and print each one
    for (int i = 0; i < argc; ++i) {
        std::cout << "Argument " << i << ": " << argv[i] << std::endl;
    }
    DataStorage storage(true); //true/false indicating loading 10 flights or more
    vector<Flight> flights = storage.loadFlights();

    SortCriteria sortCriteria = SortCriteria();
    MyWindow myWindow(1000, 700, "Flight Sorter", flights);
    myWindow.setFlights(flights); // Method to pass flight data to the window

    myWindow.show();
    return Fl::run();
}
