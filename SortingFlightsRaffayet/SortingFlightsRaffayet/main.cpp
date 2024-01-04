/*
    Polazna tacka programa
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/

#include <iostream>
#include <FL/Fl.h>
#include "Flight.h"
#include <vector>
#include "CommandLineArgs.h"
#include "MyWindow.h"
#include "DataStorage.h"
#include <vector>
#include "SortingHistory.h"
using namespace std;

int main(int argc, char* argv[]) {
    CommandLineArgs(argc, argv);
    DataStorage storage(true, CommandLineArgs::getInputPath(), CommandLineArgs::getOutputPath()); // true/false indikuje da li se ucitava 10 letova ili ne

    //ucitavanje letova
    vector<Flight> flights = storage.loadFlights();

    SortingManager sortingManager;

    SortCriteria sortCriteria = SortCriteria();

    /*
        Instanciranje prozora za prikaz procesa sortiranja
    */
    MyWindow myWindow(1000, 850, "Flight Sorter", flights, storage, sortingManager);
    myWindow.setFlights(flights);

    myWindow.show();

    Fl::run();

    while (sortingManager.sortingInProgress()) {
        Fl::wait();
    }

    /*
       Instanciranje prozora za prikaz finalnog stanja sortiranja
    */
    SortingHistory history(CommandLineArgs::getOutputPath());

    return Fl::run();
}
