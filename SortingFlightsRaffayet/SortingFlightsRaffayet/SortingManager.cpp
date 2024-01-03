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
    delete window; // Delete the window to free the memory
}

void SortingManager::showPopup(const char* message) {
    Fl_Window* popupWindow = new Fl_Window(200, 100, "Sorting Status");
    Fl_Box* box = new Fl_Box(20, 20, 160, 60, message);
    popupWindow->end();

    popupWindow->callback(closePopup); // Set callback for closing the window
    popupWindow->set_non_modal(); // Make the window non-modal
    popupWindow->show();
}
