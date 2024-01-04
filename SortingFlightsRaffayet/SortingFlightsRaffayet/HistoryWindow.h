/*
    Klasa koja sluzi za zavrsni prikaz poredjenja prvobitne liste i sortirane liste letova
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/

#ifndef HISTORYWINDOW_H
#define HISTORYWINDOW_H

#include <FL/Fl_Window.h>
#include <FL/Fl_Box.h>
#include <vector>
#include <string>
#include "HistoryItem.h"
using namespace std;

class HistoryWindow : public Fl_Window {
public:
    HistoryWindow(int w, int h, const char* title, const vector<HistoryItem>& firstBlockItems, const vector<HistoryItem>& lastBlockItems, int numberOfIterations);
    void createRightColumn();
    auto getUniqueColor();
private:
    int numberOfIterations;
    vector<HistoryItem> firstBlockItems;
    vector<HistoryItem> lastBlockItems;
    vector<Fl_Box*> left_boxes;
    vector<Fl_Box*> right_boxes;
    static const int box_w = 150;
    static const int box_h = 20;
    static const int padding = 20;
    static const int top_padding = 50;
    static const int dot_size = 3;

    static const int left_window_border_padding = 50;
    static const int right_window_border_padding = 600;
    static const int dots_starting_point = 0;
    static const int dots_spacing = 30;

    vector<vector<Fl_Box*>> dotMatrix;

    Fl_Box* iterationsBox;
};

#endif // HISTORYWINDOW_H
