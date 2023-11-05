#include <iostream>
#include "Flight.h"
#include <vector>
#include "CommandLineArgs.h"
#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_Button.h>
// ... остали инклудс

int main(int argc, char* argv[]) {
    // Руковање аргументима командне линије
    CommandLineArgs args(argc, argv);

    // Учитавање података и сортирање
    std::vector<Flight> flights = FileLoader::load(args.getInputFilePath());
    SortAlgorithm* sortAlgorithm = SortFactory::create(args.getSortAlgorithm());
    sortAlgorithm->sort(flights);

    // ... остатак имплементације
    return 0;
}
