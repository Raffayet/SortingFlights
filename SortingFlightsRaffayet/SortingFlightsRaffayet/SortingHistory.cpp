#include "SortingHistory.h"
#include <fstream>
#include <sstream>
#include "HistoryWindow.h"
#include <iostream>
using namespace std;

SortingHistory::SortingHistory(const string& file_path) {
    string fileContent = readFileContent(file_path);
    createTableWindow(fileContent);
}

string SortingHistory::readFileContent(const string& file_path) {
    ifstream file(file_path);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

vector<vector<string>> SortingHistory::parseFile(const string& file_path) {
    vector<vector<string>> history;
    ifstream file(file_path);
    string line;

    // Parsing logic goes here

    return history;
}

void SortingHistory::createTableWindow(const string& flights_history) {
    auto lines = splitStringIntoLines(flights_history);
    vector<string> firstBlockDestinations;
    vector<string> lastBlockDestinations;

    vector<string> currentBlock;
    bool isFirstBlock = true; // Flag to identify the first block

    for (const string& line : lines) {
        if (line.empty() || line.find("Sort Count") != string::npos) {
            if (!currentBlock.empty()) {
                if (isFirstBlock) {
                    // For the first block, copy destinations to firstBlockDestinations
                    firstBlockDestinations.clear(); // Clear to ensure it's empty
                    for (const auto& blockLine : currentBlock) {
                        firstBlockDestinations.push_back(extractDestination(blockLine));
                    }
                    isFirstBlock = false; // Set flag to false after processing the first block
                }

                // Always update lastBlockDestinations
                lastBlockDestinations.clear(); // Clear previous block's destinations
                for (const auto& blockLine : currentBlock) {
                    lastBlockDestinations.push_back(extractDestination(blockLine));
                }

                currentBlock.clear();
            }
        }
        else {
            currentBlock.push_back(line);
        }
    }

    // Create HistoryWindow with both the first and last block's destinations
    HistoryWindow* window = new HistoryWindow(800, 600, "Sorting History", firstBlockDestinations, lastBlockDestinations);
    window->end();
    window->show();
}

void SortingHistory::showHistory() {
    // Placeholder for method to show the history window
}

vector<string> SortingHistory::splitStringIntoLines(const string& str) {
    istringstream iss(str);
    vector<string> lines;
    string line;
    while (getline(iss, line)) {
        lines.push_back(line);
    }
    return lines;
}

string SortingHistory::extractDestination(const string& line) {
    const string destinationPrefix = "Destination: ";
    size_t startPos = line.find(destinationPrefix);
    if (startPos != string::npos) {
        startPos += destinationPrefix.length();
        size_t endPos = line.find(",", startPos);
        if (endPos != string::npos) {
            return line.substr(startPos, endPos - startPos);
        }
    }
    return ""; // Return empty string if not found
}
