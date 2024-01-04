/*
    Klasa koja sluzi za GUI prikaz procesa sortiranja letova, kao i izbora dodatnih parametara (kriterijuma, vrste algoritma sortitanja itd..)
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/

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
#include <FL/Fl_Input.H>
#include "DataStorage.h"
#include "Flight.h" 
#include "RowPosition.h"
#include <stack>
#include "QuickSortState.h"
#include <map>
#include "FlightHistory.h"
#include "SortingManager.h"
using namespace std;

class MyWindow : public Fl_Window {
public:
    DataStorage flightsStorage;
    SortingManager sortingManager;
    SortCriteria sortCriteria;
    SortAlgorithm sortAlgorithm;
    vector<Flight> flightsToShow;
    size_t i, j, min_idx; //indeksi koji se koriste za cuvanje stanja liste letova prilikom sortiranja
    bool isSorting; //indikator koji oznacava da li je sortiranje u toku

    int animationState = 0;
    bool isAnimating = false;
    float animationProgress = 0.0;
    int animatingRow1 = -1, animatingRow2 = -1;
    vector<Fl_Color> originalColors;
    int firstAnimatedRow;
    int secondAnimatedRow;
    vector<RowPosition> rowPositions;
    int sortCount = 0;
    FlightHistory flightHistory;

    MyWindow(int w, int h, const char* title, vector<Flight> flightsToShow, DataStorage storage, SortingManager sortingManager);

    // Metode koje se koriste u svrhu animiranja i vizualizovanja liste letova prilikom sortiranja
    void setFlights(const vector<Flight>& flights);
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
    void onChangePathButton(Fl_Widget*);
    static void onChangePathButtonWrapper(Fl_Widget* w, void* v);

    // Algoritamske metode sortiranja
    void bubbleSort();
    void selectionSort();
    int partition(int low, int high);
    void startQuickSort();
    void quickSort(int low, int high);
    void oneStepQuickSort();

private:
    stack<QuickSortState> quickSortStack;

    Fl_Button* sort_button;
    Fl_Input* input_path;
    Fl_Input* output_path;
    Fl_Button* confirmPathButton;
    Fl_Choice* sort_menu;
    Fl_Scroll* scroll;
    vector<Fl_Box*> boxes;

    Fl_Box* sort_criteria_label;
    Fl_Choice* sort_criteria_choice;

    Fl_Box* sort_algorithm_label;
    Fl_Choice* sort_algorithm_choice;

    static void cb_sort_criteria(Fl_Widget*, void*);
    void sort_criteria_changed(); 

    static void cb_sort_algorithm(Fl_Widget*, void*);
    void sort_algorithm_changed();

    static void cb_sort(Fl_Widget*, void*);

    void sort_pressed();
};

#endif // MYWINDOW_H
