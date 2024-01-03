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
#include "SortAlgorithm.h"
#include <vector>
#include <memory>
#include "SelectionSort.h"
#include <FL/Fl_Input.H>
#include "DataStorage.h"


// Include the header file for the Flight class or declare it
#include "Flight.h" // Adjust this include to your specific file
#include "RowPosition.h"
#include <stack>
#include "QuickSortState.h"
#include <map>
#include "FlightHistory.h"
#include "SortingManager.h"

class MyWindow : public Fl_Window {
public:
    DataStorage flightsStorage;
    SortingManager sortingManager;
    SortCriteria sortCriteria;
    SortAlgorithm sortAlgorithm;
    std::vector<Flight> flightsToShow;
    size_t i, j, min_idx;  // Variables to keep track of sorting state
    bool isSorting;

    Fl_Box* sortingCompleteLabel;
    int animationState = 0;
    bool isAnimating = false;
    float animationProgress = 0.0;
    int animatingRow1 = -1, animatingRow2 = -1;
    std::vector<Fl_Color> originalColors;
    int firstAnimatedRow;
    int secondAnimatedRow;
    std::vector<RowPosition> rowPositions;
    int sortCount = 0;
    FlightHistory flightHistory;

    MyWindow(int w, int h, const char* title, std::vector<Flight> flightsToShow, DataStorage storage);

    // Methods for user interface
    void setFlights(const std::vector<Flight>& flights);
    void highlightRows(int row1, int row2);
    void resetHighlighting();
    void animate();
    static void animate_callback(void* data);
    void startAnimation(int firstRowIndex, int secondRowIndex);
    void updateRow(int upRowIndex, int downRowIndex, float progress);
    void returnPreviousColor(int upRowIndex, int downRowIndex);
    void updateBoxesPosition(int rowIndex, int newY);
    void setupBox(Fl_Box* box);
    void updateAllRows();
    void bubbleSort();
    void selectionSort();
    int partition(int low, int high);
    void startQuickSort();
    void quickSort(int low, int high);
    void oneStepQuickSort();
    void onChangePathButton(Fl_Widget*);
    static void onChangePathButtonWrapper(Fl_Widget* w, void* v);

private:
    std::stack<QuickSortState> quickSortStack;
    Fl_Button* sort_button;
    Fl_Input* input_path;
    Fl_Input* output_path;
    Fl_Button* confirmPathButton;
    Fl_Choice* sort_menu;
    Fl_Scroll* scroll;
    std::vector<Fl_Box*> boxes;

    Fl_Box* sort_criteria_label;
    Fl_Choice* sort_criteria_choice; // Dropdown for sorting criteria

    Fl_Box* sort_algorithm_label;
    Fl_Choice* sort_algorithm_choice; // Dropdown for sorting criteria

    static void cb_sort_criteria(Fl_Widget*, void*); // Callback for the dropdown
    void sort_criteria_changed(); 

    static void cb_sort_algorithm(Fl_Widget*, void*); // Callback for the dropdown
    void sort_algorithm_changed();

    static void cb_sort(Fl_Widget*, void*);

    void sort_pressed();
};

#endif // MYWINDOW_H
