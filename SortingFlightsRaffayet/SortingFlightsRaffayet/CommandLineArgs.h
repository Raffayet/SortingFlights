/*
    Klasa za cuvanje argumenata komandne linije - koristi se za unos putanje do ulaznih letova i do izlaznog fajla koji cuva sortirane letove
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/

#ifndef COMMANDLINEARGS_H
#define COMMANDLINEARGS_H
#include <string>
#include "SortCriteria.h"
#include <stdexcept>
using namespace std;

class CommandLineArgs {
private:
    static string inputPath;
    static string outputPath;

public:
    CommandLineArgs(int argc, char* argv[]) {
        if (argc > 2) {
            inputPath = argv[1];
            outputPath = argv[2];
        }
        else {
            //neodgovarajuc broj argumenata komandne linije
            throw runtime_error("Insufficient command-line arguments provided. Expected input and output paths.");
        }
    }

    static string getInputPath() {
        return inputPath;
    }

    static string getOutputPath() {
        return outputPath;
    }
};

#endif // COMMANDLINEARGS_H
