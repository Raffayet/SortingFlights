#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_Button.h>
#include <FL/Fl_Input.h>
#include <FL/Fl_Output.h>
#include <FL/Fl_Choice.h>
#include <FL/Fl_Box.H>
#include <FL/Fl_Scroll.H>
#include <vector>
#include "SortCriteria.h"

// Include the header file for the Flight class or declare it
#include "Flight.h" // Adjust this include to your specific file

class MyWindow : public Fl_Window {
public:
    SortCriteria sortCriteria;

    MyWindow(int w, int h, const char* title);

    // Methods for user interface
    void setFlights(const std::vector<Flight>& flights);

private:
    // Private members, buttons, input fields, etc.
    Fl_Button* sort_button;
    Fl_Input* input_path;
    Fl_Output* output_path;
    Fl_Choice* sort_menu;
    Fl_Scroll* scroll;
    std::vector<Fl_Box*> boxes;

    Fl_Choice* sort_criteria_choice; // Dropdown for sorting criteria

    static void cb_sort_criteria(Fl_Widget*, void*); // Callback for the dropdown
    void sort_criteria_changed(); 

    // etc.

    // Callback functions for events
    static void cb_sort(Fl_Widget*, void*);
    // etc.

    // Functions called during events
    void sort_pressed();
    // etc.

    // DataStorage dataStorage; // Instance of data storage class
};

#endif // MYWINDOW_H
