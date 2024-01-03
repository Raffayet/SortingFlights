#ifndef SORTINGMANAGER_H
#define SORTINGMANAGER_H

#include <FL/Fl_Widget.H>

class SortingManager {
public:
    SortingManager();
    void startSorting();
    void finishSorting();
    bool sortingInProgress() const;

private:
    bool isSorting;
    static void closePopup(Fl_Widget* widget, void*);
    void showPopup(const char* message);
};

#endif // SORTINGMANAGER_H
