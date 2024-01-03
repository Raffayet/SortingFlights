#include "HistoryWindow.h"
#include <FL/Fl.H>
#include <string>
using namespace std;

HistoryWindow::HistoryWindow(int w, int h, const char* title, const vector<string>& firstBlockCities, const vector<string>& lastBlockCities)
    : Fl_Window(w, h, title), firstBlockCities(firstBlockCities), lastBlockCities(lastBlockCities) {
    int left_y = top_padding;
    int right_y = top_padding;
    int right_x = w - box_w - padding;

    // Iteration labels
    int label_w = 60; // Width of the iteration labels
    int label_h = 20; // Height of the iteration labels
    int label_x = padding; // Starting x position for the iteration labels
    int label_y = padding; // Starting y position for the iteration labels
    int label_spacing = 60; // Space between the iteration labels

    for (const string& city : this->firstBlockCities) {
        // Left column boxes
        auto* left_box = new Fl_Box(padding, left_y, box_w, box_h, city.c_str());
        left_box->box(FL_UP_BOX);
        left_box->labelfont(FL_BOLD);
        left_box->labelsize(12);
        left_y += box_h + padding;
    }

    for (const string& city : this->lastBlockCities) {
        auto* right_box = new Fl_Box(right_x, right_y, box_w, box_h, city.c_str());
        right_box->box(FL_UP_BOX);
        right_box->labelfont(FL_BOLD);
        right_box->labelsize(12);
        right_y += box_h + padding;
    }

    end(); // End adding widgets to the window
}


