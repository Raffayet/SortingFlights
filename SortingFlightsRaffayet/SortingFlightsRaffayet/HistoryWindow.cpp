/*
    Klasa koja sluzi za zavrsni prikaz poredjenja prvobitne liste i sortirane liste letova - Implementacija
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/

#include "HistoryWindow.h"
#include <FL/Fl.H>
#include <string>
#include <sstream>
#include <map>
#include <utility>
using namespace std;


HistoryWindow::HistoryWindow(int w, int h, const char* title, const vector<HistoryItem>& firstBlockItems, const vector<HistoryItem>& lastBlockItems, int numberOfIterations)
    : Fl_Window(w, h, title), firstBlockItems(firstBlockItems), lastBlockItems(lastBlockItems), numberOfIterations(numberOfIterations){
    int left_y = top_padding;
    int right_y = top_padding;

    iterationsBox = new Fl_Box(400, 20, 20, 20, "ITERATIONS");

    vector<Fl_Box*> rightBoxes(lastBlockItems.size(), nullptr);

    //Mapa koja cuva jedinstvene FL boje za item-e
    map<string, Fl_Color> uniqueColorMap;
    Fl_Color nextColor = FL_RED;

    // Funkcija za dobavljanje sledece jedinstvene boje
    auto getNextUniqueColor = [&nextColor]() {
        Fl_Color color = nextColor;
        int c = (int)color;
        c = (c + 1) % 256;
        nextColor = (Fl_Color)c;
        return color;
    };

    // Finalni prikaz - desna kolona gradova
    for (size_t i = 0; i < lastBlockItems.size(); ++i) {
        const HistoryItem& item = lastBlockItems[i];
        auto* right_box = new Fl_Box(right_window_border_padding, right_y, box_w, box_h, item.destination.c_str());
        right_box->box(FL_UP_BOX);
        right_box->labelfont(FL_BOLD);
        right_box->labelsize(12);
        right_y += box_h + padding;
        rightBoxes[i] = right_box;
    }

    // Finalni prikaz - leva kolona gradova
    for (size_t i = 0; i < firstBlockItems.size(); ++i) {
        const HistoryItem& leftItem = firstBlockItems[i];
        Fl_Color color = FL_YELLOW;

        if (i < rightBoxes.size()) {
            const HistoryItem& rightItem = lastBlockItems[i];
            if (leftItem.flightNumber == rightItem.flightNumber) {
                if (i != rightBoxes.size()) {
                    auto it = uniqueColorMap.find(leftItem.flightNumber);
                    if (it == uniqueColorMap.end()) {
                        color = getNextUniqueColor();
                        uniqueColorMap[leftItem.flightNumber] = color;
                    }
                    else {
                        color = it->second;
                    }
                }
                rightBoxes[i]->color(color);
            }
        }

        auto* left_box = new Fl_Box(left_window_border_padding, left_y, box_w, box_h, leftItem.destination.c_str());
        left_box->box(FL_UP_BOX);
        left_box->color(color);
        left_box->labelfont(FL_BOLD);
        left_box->labelsize(12);
        left_y += box_h + padding;
    }

    // Vertikalni spacing za tacke izmedju dve kolone
    int total_vertical_space = max(left_y, right_y) - top_padding;
    int space_between_dots = (total_vertical_space - (numberOfIterations * box_h)) / (numberOfIterations + 1);

    // Kreiranje matrice tacaka za prikaz iteracija
    for (int i = 0; i < firstBlockItems.size(); ++i) {
        std::vector<Fl_Box*> dotRow;
        for (int j = 0; j < numberOfIterations; ++j) {
            int dot_x = left_window_border_padding + dots_starting_point + box_w + (j + 1) * dots_spacing - (dot_size / 2);
            int dot_y = top_padding + i * (box_h + padding) + (box_h / 2) - (dot_size / 2);
            auto* dot_box = new Fl_Box(dot_x, dot_y, dot_size, dot_size);
            dot_box->box(FL_FLAT_BOX);
            dot_box->color(FL_BLACK); 
            add(dot_box);
            dotRow.push_back(dot_box); 
        }
        dotMatrix.push_back(dotRow); 
    }

    end();
}


