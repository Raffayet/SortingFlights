#ifndef COMMANDLINEARGS_H
#define COMMANDLINEARGS_H

#include <string>
#include "SortCriteria.h"

class CommandLineArgs {
private:
    std::string inputFilePath;
    SortCriteria sortCriteria;
public:
    CommandLineArgs(int argc, char* argv[]); // Constructor declaration

    std::string getInputFilePath() const { return inputFilePath; }
    SortCriteria getSortCriteria() const { return sortCriteria; }
};

#endif // COMMANDLINEARGS_H
