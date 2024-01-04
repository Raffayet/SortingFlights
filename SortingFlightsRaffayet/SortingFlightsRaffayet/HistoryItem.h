/*
    Klasa koja cuva informacije za zavrsni prikaz letova
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/

#pragma once
#include <string>
#include <FL/Fl.H>
using namespace std;

struct HistoryItem {
    string destination, flightNumber;
    Fl_Color color;

    HistoryItem(string destination, string flightNumber)
        : destination(destination), flightNumber(flightNumber) {}
};