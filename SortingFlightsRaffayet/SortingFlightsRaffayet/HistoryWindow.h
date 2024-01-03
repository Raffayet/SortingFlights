#ifndef HISTORYWINDOW_H
#define HISTORYWINDOW_H

#include <FL/Fl_Window.h>
#include <FL/Fl_Box.h>
#include <vector>
#include <string>
using namespace std;

class HistoryWindow : public Fl_Window {
public:
    HistoryWindow(int w, int h, const char* title, const std::vector<std::string>& firstBlockCities, const std::vector<std::string>& lastBlockCities);
private:
    vector<string> firstBlockCities;
    vector<string> lastBlockCities;
    vector<Fl_Box*> left_boxes;
    vector<Fl_Box*> right_boxes;
    static const int box_w = 100;
    static const int box_h = 25;
    static const int padding = 10;
    static const int top_padding = 50;
};

#endif // HISTORYWINDOW_H
