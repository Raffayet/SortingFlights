/*
    Pomocna klasa koja se koristi za snabdevanje informacijama o istoriji sortiranja letova - Implementacija
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/

#include "SortingHistory.h"
#include <fstream>
#include <sstream>
#include "HistoryWindow.h"
#include <iostream>
#include <regex>
#include "HistoryItem.h"
using namespace std;

SortingHistory::SortingHistory(const string& file_path) {
    string fileContent = readFileContent(file_path);
    createTableWindow(fileContent);
}

// Citanje iz fajla flights_history.txt
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

    return history;
}

void SortingHistory::createTableWindow(const string& flights_history) {
    auto lines = splitStringIntoLines(flights_history);
    vector<string> currentBlock;
    bool isFirstBlock = true; 
    int numberOfIterations = 0;
    regex sortCountRegex("Sort Count (\\d+):");
    smatch match;

    for (const string& line : lines) {
        if (regex_search(line, match, sortCountRegex)) {
            numberOfIterations = stoi(match[1]);
            if (!currentBlock.empty()) {
                if (isFirstBlock) {
                    initialBlockItems.clear();
                    for (const auto& blockLine : currentBlock) {
                        if (!blockLine.empty()) {
                            string destination = extractDestination(blockLine);
                            string flightNumber = extractFlightNumber(blockLine);
                            HistoryItem historyItem(destination, flightNumber);
                            initialBlockItems.push_back(historyItem);
                        }
                    }
                    isFirstBlock = false;
                }

                finalSortedBlockItems.clear();
                for (const auto& blockLine : currentBlock) {
                    if (!blockLine.empty()) {
                        string destination = extractDestination(blockLine);
                        string flightNumber = extractFlightNumber(blockLine);
                        HistoryItem historyItem(destination, flightNumber);
                        finalSortedBlockItems.push_back(historyItem);
                    }
                }

                currentBlock.clear();
            }
        }
        else {
            if (!line.empty()) {
                currentBlock.push_back(line);
            }
        }
    }

    HistoryWindow* window = new HistoryWindow(800, 600, "Sorting History", initialBlockItems, finalSortedBlockItems, numberOfIterations);
    window->end();
    window->show();
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

// Izvlacenje destnacije iz ucitanih objekata letova
string SortingHistory::extractDestination(const string& line) {
    string destination = "";
    const string destinationPrefix = "Destination: ";
    size_t startPos = line.find(destinationPrefix);
    if (startPos != string::npos) {
        startPos += destinationPrefix.length();
        size_t endPos = line.find(",", startPos);
        if (endPos != string::npos) {
            destination = line.substr(startPos, endPos - startPos);
        }
    }

    return destination;
}

// Izvlacenje broja leta iz ucitanih objekata letova
string SortingHistory::extractFlightNumber(const string& line) {
    string flightNumber = "";
    const string flightNumberPrefix = "Flight Number: ";
    size_t startPos = line.find(flightNumberPrefix);
    if (startPos != string::npos) {
        startPos += flightNumberPrefix.length();
        size_t endPos = line.find(",", startPos);
        if (endPos != string::npos) {
            flightNumber = line.substr(startPos, endPos - startPos);
        }
    }
    return flightNumber;
}