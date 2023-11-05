#pragma once
#include <string>
#include <vector>

class ArgumentHandler {
public:
    ArgumentHandler(int argc, char** argv);
    std::string getInputFilePath() const;
    std::string getOutputFilePath() const;
    std::string getSortingCriteria() const;
    std::string getSortingAlgorithm() const;

private:
    std::string inputFilePath;
    std::string outputFilePath;
    std::string sortingCriteria;
    std::string sortingAlgorithm;
};
