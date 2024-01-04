/*
    Klasa koja upravlja stanjem sortiranja
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/

#include "SortingManager.h"
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

SortingManager::SortingManager() : isSorting(false) {}

void SortingManager::startSorting() {
    isSorting = true;
}

void SortingManager::finishSorting() {
    isSorting = false;
    showPopup("Sorting Complete");
}

bool SortingManager::sortingInProgress() const {
    return isSorting;
}

void SortingManager::closePopup(Fl_Widget* widget, void*) {
    Fl_Window* window = (Fl_Window*)widget;
    window->hide();
    delete window;
}

/*
    Funkcija za kreiranje iskakajuceg prozora koji oznacava kraj procesa sortiranja
    const char* message - Poruka koja se prikazuje na prozoru
*/
void SortingManager::showPopup(const char* message) {
    Fl_Window* popupWindow = new Fl_Window(200, 100, "Sorting Status");
    Fl_Box* box = new Fl_Box(20, 20, 160, 60, message);
    popupWindow->end();

    popupWindow->callback(closePopup);
    popupWindow->set_non_modal(); 
    popupWindow->show();
}
