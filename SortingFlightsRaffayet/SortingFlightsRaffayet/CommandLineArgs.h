#include <string>
#include "SortCriteria.h"

class CommandLineArgs {
private:
    std::string inputFilePath;
    SortCriteria sortCriteria;
public:
    CommandLineArgs(int argc, char* argv[]) {
        // Parse command line arguments to initialize inputFilePath and sortCriteria
    }

    std::string getInputFilePath() const { return inputFilePath; }
    SortCriteria getSortCriteria() const { return sortCriteria; }
};
