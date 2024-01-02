#ifndef COMMANDLINEARGS_H
#define COMMANDLINEARGS_H

#include <string>
#include "SortCriteria.h"
#include <stdexcept>

class CommandLineArgs {
private:
    static std::string inputPath;
    static std::string outputPath;

public:
    CommandLineArgs(int argc, char* argv[]) {
        if (argc > 2) {
            inputPath = argv[1];
            outputPath = argv[2];
        }
        else {
            throw std::runtime_error("Insufficient command-line arguments provided. Expected input and output paths.");
        }
    }

    static std::string getInputPath() {
        return inputPath;
    }

    static std::string getOutputPath() {
        return outputPath;
    }
};

#endif // COMMANDLINEARGS_H
