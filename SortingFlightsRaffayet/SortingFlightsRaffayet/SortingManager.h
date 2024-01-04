/*
    Klasa koja upravlja stanjem sortiranja
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/

#ifndef SORTINGMANAGER_H
#define SORTINGMANAGER_H

#include <FL/Fl_Widget.H>

class SortingManager {
public:
    SortingManager();
    void startSorting();
    void finishSorting();
    bool sortingInProgress() const;
    bool isSorting;

private:
    static void closePopup(Fl_Widget* widget, void*);
    void showPopup(const char* message);
};

#endif // SORTINGMANAGER_H
