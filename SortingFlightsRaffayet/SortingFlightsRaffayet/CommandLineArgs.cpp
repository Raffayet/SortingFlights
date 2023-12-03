#include "CommandLineArgs.h"

CommandLineArgs::CommandLineArgs(int argc, char* argv[]) {
    // Parse command line arguments to initialize inputFilePath and sortCriteria
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--input") {
            if (i + 1 < argc) {
                inputFilePath = argv[++i];
            }
            else {
                // Handle error: expected argument after "--input"
            }
        }
        // Add additional parsing logic for other arguments to initialize sortCriteria
        // ...
    }
    // After parsing, initialize sortCriteria with the extracted values
    // sortCriteria = SortCriteria(/* extracted values */);
}
