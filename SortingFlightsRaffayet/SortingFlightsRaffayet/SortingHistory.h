#ifndef SORTINGHISTORY_H
#define SORTINGHISTORY_H

#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <vector>
#include <string>
using namespace std;

class SortingHistory {
public:
    SortingHistory(const string& file_path);
    void showHistory();
    string extractDestination(const string& line);
    string readFileContent(const string& file_path);
    vector<string> splitStringIntoLines(const string& str);

private:
    vector<vector<string>> parseFile(const string& file_path);
    void createTableWindow(const string& flights_history);
};

#endif // SORTINGHISTORY_H
