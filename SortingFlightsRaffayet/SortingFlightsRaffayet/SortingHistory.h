/*
    Pomocna klasa koja se koristi za snabdevanje informacijama o istoriji sortiranja letova 
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/

#ifndef SORTINGHISTORY_H
#define SORTINGHISTORY_H

#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <vector>
#include <string>
#include "HistoryItem.h"
using namespace std;

class SortingHistory {
public:
    SortingHistory(const string& file_path);
    void showHistory();
    string extractDestination(const string& line);
    string extractFlightNumber(const string& line);
    string readFileContent(const string& file_path);
    vector<string> splitStringIntoLines(const string& str);

private:
    vector<HistoryItem> initialBlockItems; //prvobitno stanje liste letova
    vector<HistoryItem> finalSortedBlockItems; //sortirana lista letova

    vector<vector<string>> parseFile(const string& file_path);
    void createTableWindow(const string& flights_history);
};

#endif // SORTINGHISTORY_H
