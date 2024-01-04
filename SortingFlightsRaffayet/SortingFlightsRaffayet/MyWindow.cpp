/*
    Klasa koja sluzi za GUI prikaz procesa sortiranja letova, kao i izbora dodatnih parametara (kriterijuma, vrste algoritma sortitanja itd..) - Implementacija
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/

#include "MyWindow.h"
#include <vector>
#include <string>
#include "Flight.h"
#include <iostream>
#include <FL/Fl_Box.h>
#include "SortCriteria.h"
#include "SortAlgorithm.h"
#include <stack>
#include <fstream>
#include "DataStorage.h"
using namespace std;

// Ovde morate da koristite potpis konstruktora koji ste definisali u .h fajlu
MyWindow::MyWindow(int w, int h, const char* title, vector<Flight> flightsToShow, DataStorage storage, SortingManager sortingManager)
    : Fl_Window(w, h, title), flightsToShow(flightsToShow), flightsStorage(storage), sortingManager(sortingManager), i(0), j(1), min_idx(0), isSorting(false) {
    // Inicijalizacija korisničkog interfejsa komponente 
    sort_button = new Fl_Button(50, 170, 80, 30, "Sort");
    sort_button->callback(cb_sort, this);
    input_path = new Fl_Input(100, 20, 210, 30, "Input Path");
    output_path = new Fl_Input(450, 20, 210, 30, "Output Path");
    confirmPathButton = new Fl_Button(800, 20, 100, 30, "Confirm path");
    scroll = new Fl_Scroll(10, 130, w - 20, h - 140);
    scroll->type(Fl_Scroll::VERTICAL_ALWAYS);
    
    Fl_Input* inputs[2] = { input_path, output_path };
    confirmPathButton->callback(MyWindow::onChangePathButtonWrapper, this);

    int animationState = 0;

    //Izbor kriterijuma sortiranja
    sort_criteria_label = new Fl_Box(180, 170, 120, 25, "Sort Criteria");

    sort_criteria_choice = new Fl_Choice(300, 170, 160, 25);
    sort_criteria_choice->add("Departure Time");
    sort_criteria_choice->add("Destination");
    sort_criteria_choice->add("Flight Number");
    sort_criteria_choice->add("Gate Number");
    sort_criteria_choice->value(0);
    sort_criteria_choice->callback(cb_sort_criteria, this);

    //Izbor algoritma za sortiranje
    sort_algorithm_label = new Fl_Box(520, 170, 120, 25, "Sort Algorithm");

    sort_algorithm_choice = new Fl_Choice(650, 170, 160, 25);
    sort_algorithm_choice->add("Selection Sort");
    sort_algorithm_choice->add("Bubble Sort");
    sort_algorithm_choice->add("Quick Sort");
    sort_algorithm_choice->value(0);
    sort_algorithm_choice->callback(cb_sort_algorithm, this);

    this->end();
    this->show();
}

//Funkcije koje omogucuju menjanje putanje ulaznog i izlaznog fajla - time se resetuje stanje tabele i opet pocinje proces citanja iz fajla
void MyWindow::onChangePathButton(Fl_Widget*) {
    cout << "Input File Path: " << input_path->value() << endl;
    cout << "Output File Path: " << output_path->value() << endl;

    flightsStorage.flightsDataPath = input_path->value();
    flightsStorage.flightsHistoryPath = output_path->value();
    vector<Flight> newFlights = flightsStorage.loadFlights();
    this->setFlights(newFlights);
}

void MyWindow::onChangePathButtonWrapper(Fl_Widget* w, void* v) {
    MyWindow* window = static_cast<MyWindow*>(v);
    window->onChangePathButton(w);
}

/*
    Funkcija za animiranje sporog menjanja pozicija dva leta
    int firstRowIndex - indeks prvog leta za promenu pozicije
    int secondRowIndex - indeks drugog leta za promenu pozicije
*/
void MyWindow::startAnimation(int firstRowIndex, int secondRowIndex) {
    originalColors.clear();

    firstAnimatedRow = firstRowIndex;
    secondAnimatedRow = secondRowIndex;

    int startIndexFirstRow = firstRowIndex * 4; 
    int startIndexSecondRow = secondRowIndex * 4;

    for (int i = startIndexFirstRow; i < startIndexFirstRow + 4; ++i) {
        originalColors.push_back(boxes[i]->color());
    }
    for (int i = startIndexSecondRow; i < startIndexSecondRow + 4; ++i) {
        originalColors.push_back(boxes[i]->color());
    }

    isAnimating = true;
    animationProgress = 0.0;
    Fl::add_timeout(0.05, &MyWindow::animate_callback, this);
}

void MyWindow::animate_callback(void* data) {
    MyWindow* window = static_cast<MyWindow*>(data);
    window->animate();
}


/*
    Funkcija za azuriranje pozicija letova nakon njihovog menjanja
    int upRowIndex - indeks leta koji se penje ka gore
    int downRowIndex - indeks leta koji se spusta na dole
    float progress - brzina animacije - poboljsava UI
*/
void MyWindow::updateRow(int upRowIndex, int downRowIndex, float progress) {
    RowPosition& startUpPos = rowPositions[upRowIndex];
    RowPosition& startDownPos = rowPositions[downRowIndex];

    RowPosition endUpPos = rowPositions[downRowIndex];
    RowPosition endDownPos = rowPositions[upRowIndex];

    // Izračunavanje trenutnih pozicija na osnovu napretka animacije
    int currentYUp = static_cast<int>(startUpPos.y + (endUpPos.y - startUpPos.y) * progress);
    int currentYDown = static_cast<int>(startDownPos.y + (endDownPos.y - startDownPos.y) * progress);

    // Ažuriranje položaja redova
    for (int i = 0; i < 4; ++i) {
        int boxIndexUp = upRowIndex * 4 + i;
        int boxIndexDown = downRowIndex * 4 + i;

        if (boxIndexUp < boxes.size() && boxIndexDown < boxes.size()) {
            Fl_Box* boxUp = boxes[boxIndexUp];
            Fl_Box* boxDown = boxes[boxIndexDown];

            boxUp->position(boxUp->x(), currentYUp);
            boxDown->position(boxDown->x(), currentYDown);

            // Primena crvene boje tokom animacije
            boxUp->color(FL_RED);
            boxDown->color(FL_RED);

            boxUp->redraw();
            boxDown->redraw();
        }
    }

    scroll->redraw();
}

// Menjanje boje kada animacija za dva leta prestane - letovi koji su u procesu menjanja su obojeni crvenom bojom
void MyWindow::returnPreviousColor(int upRowIndex, int downRowIndex) {
    for (int i = 0; i < 4; ++i) {
        int boxIndex = upRowIndex * 4 + i;
        if (boxIndex < boxes.size()) {
            Fl_Box* box = boxes[boxIndex];
            box->color(originalColors[i]); 
            box->redraw();
        }
    }

    for (int i = 0; i < 4; ++i) {
        int boxIndex = downRowIndex * 4 + i;
        if (boxIndex < boxes.size()) {
            Fl_Box* box = boxes[boxIndex];
            box->color(originalColors[i + 4]);
            box->redraw();
        }
    }
}


void MyWindow::animate() {
    if (isAnimating) {
        const float duration = 1.0; 
        animationProgress += 0.05f / duration;

        if (animationProgress >= 1.0) {
            animationProgress = 1.0;
            isAnimating = false;

            swap(rowPositions[firstAnimatedRow], rowPositions[secondAnimatedRow]);

            returnPreviousColor(firstAnimatedRow, secondAnimatedRow);

            updateAllRows();
        }
        else {
            updateRow(firstAnimatedRow, secondAnimatedRow, animationProgress);
        }

        redraw();

        if (isAnimating) {
            Fl::repeat_timeout(0.05, animate_callback, this);
        }
        else {
        }
    }
}

void MyWindow::updateAllRows() {
    for (size_t i = 0; i < rowPositions.size(); ++i) {
        for (int j = 0; j < 4; ++j) {
            int boxIndex = i * 4 + j;
            if (boxIndex < boxes.size()) {
                Fl_Box* box = boxes[boxIndex];
                box->position(box->x(), rowPositions[i].y);
                box->redraw();
            }
        }
    }
}

// Funkcija za implementaciju Selection sort algoritma - najbrzi, jer ima najmanji broj poredjenja, uzima min i max elemenat za svaku iteraciju
void MyWindow::selectionSort() {
    if (i < flightsToShow.size() - 1) {
        if (j <= flightsToShow.size()) {
            min_idx = i;
            for (j = i + 1; j < flightsToShow.size(); ++j) {
                flightHistory.comparisonCount++;
                if (flightsToShow[j] < flightsToShow[min_idx]) {
                    min_idx = j;
                }
            }

            if (min_idx != i) {
                // Prvo se promene pozicije dva leta
                swap(flightsToShow[min_idx], flightsToShow[i]);
                swap(rowPositions[min_idx], rowPositions[i]);
                flightHistory.movementCount++;
                // Nakon toga, sledi prikaz njihovog menjanja pomocu funkcije za animiranje
                startAnimation(i, min_idx);
                i++;
                return;
            }
            i++;
        }
        else {
            sortingManager.finishSorting();
        }
    }
    else {
        sortingManager.finishSorting();
    }
}

// Funkcija za implementaciju Bubble sort algoritma - najlaksi za implementaciju ali je najsporiji, poredi svaki sa svakim i manji pomera na gore a veci na dole
void MyWindow::bubbleSort() {
    if (!sortingManager.sortingInProgress()) {
        // Initialize sorting parameters
        i = 0;
        j = 0;
        sortingManager.startSorting();
        return;
    }

    if (i >= flightsToShow.size() - 1) {
        sortingManager.finishSorting();
        return;
    }

    if (j < flightsToShow.size() - i - 1) {
        flightHistory.comparisonCount++;
        if (flightsToShow[j] > flightsToShow[j + 1]) {
            swap(flightsToShow[j], flightsToShow[j + 1]);
            swap(rowPositions[j], rowPositions[j + 1]);
            flightHistory.movementCount++;
            startAnimation(j, j + 1);
            j++;
            return;
        }
        j++;
    }
    else {
        i++;
        j = 0;
    }
}


void MyWindow::oneStepQuickSort() {
    if (quickSortStack.empty()) {
        sortingManager.finishSorting();
        return;
    }

    QuickSortState state = quickSortStack.top();
    quickSortStack.pop();

    if (state.low < state.high) {
        int pivotIndex = partition(state.low, state.high);

        if (pivotIndex > state.low) {
            quickSortStack.push(QuickSortState(state.low, pivotIndex - 1));
        }

        if (pivotIndex < state.high) {
            quickSortStack.push(QuickSortState(pivotIndex + 1, state.high));
        }
    }
}

// Funkcija za implementaciju Quick sort algoritma - brzi od buble sort-a, a sporiji od selection sort-a. Koristi pivot element za poredjenje
void MyWindow::quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);

        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

int MyWindow::partition(int low, int high) {
    Flight pivot = flightsToShow[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        flightHistory.comparisonCount++;
        if (flightsToShow[j] < pivot) {
            i++;
            swap(flightsToShow[i], flightsToShow[j]);
            swap(rowPositions[i], rowPositions[j]);
            flightHistory.movementCount++;
            startAnimation(i, j);
        }
    }
    swap(flightsToShow[i + 1], flightsToShow[high]);
    swap(rowPositions[i + 1], rowPositions[high]);
    cout << "Swapped pivot to index " << (i + 1) << endl;
    flightHistory.movementCount++;
    startAnimation(i + 1, high);

    return (i + 1);
}


// Funkcija koja se okida kada se pritisne dugme sort za prikaz naredne iteracije sortiranja
void MyWindow::sort_pressed() {
    if (!sortingManager.sortingInProgress()) {
        sortingManager.startSorting();
        quickSortStack.push(QuickSortState(0, flightsToShow.size() - 1));
    }

    if (sortAlgorithm == SortAlgorithm::BubbleSort) {
        bubbleSort();
    }

    else if (sortAlgorithm == SortAlgorithm::QuickSort) {
        oneStepQuickSort();
    }

    else {
        selectionSort();
    }
    
    flightHistory.flightMap[sortCount] = flightsToShow;
    sortCount++;
    //Nakon svake iteracije sortiranja, belezi se stanje liste letova i cuva u flights_history.txt fajl
    flightsStorage.writeSortedFlightHistoryToFile(flightsStorage.flightsHistoryPath, flightHistory);
}

// Callback funkcija mora da odgovara deklaraciji u .h fajlu
void MyWindow::cb_sort(Fl_Widget*, void* v) {
    MyWindow* window = static_cast<MyWindow*>(v);
    window->sort_pressed();
}


void MyWindow::cb_sort_criteria(Fl_Widget* widget, void* data) {
    MyWindow* window = static_cast<MyWindow*>(data);
    window->sort_criteria_changed();
}

void MyWindow::cb_sort_algorithm(Fl_Widget* widget, void* data) {
    MyWindow* window = static_cast<MyWindow*>(data);
    window->sort_algorithm_changed();
}

void MyWindow::sort_criteria_changed() {
    int choice = sort_criteria_choice->value();
    switch (choice) {
    case 0:
        SortCriteria::setCurrentSortField(SortField::DepartureTime);
        break;
    case 1:
        SortCriteria::setCurrentSortField(SortField::Destination);
        break;
    case 2:
        SortCriteria::setCurrentSortField(SortField::FlightNumber);
        break;
    case 3:
        SortCriteria::setCurrentSortField(SortField::GateNumber);
        break;
    default:
        break;
    }
    cout << SortCriteria::getCurrentSortFieldString() << endl;
}

void MyWindow::sort_algorithm_changed() {
    int choice = sort_algorithm_choice->value();
    i = 0;
    switch (choice) {
    case 0:
        sortAlgorithm = SortAlgorithm::SelectionSort;
        break;
    case 1:
        sortAlgorithm = SortAlgorithm::BubbleSort;
        break;
    case 2:
        sortAlgorithm = SortAlgorithm::QuickSort;
        break;
    default:
        break;
    }
}

void MyWindow::setFlights(const std::vector<Flight>& flights) {
    this->flightsToShow = flights;
    const int colWidth = 220; 
    const int boxHeight = 25;  
    const int borderWidth = 1;
    const int numCols = 4;    

    for (auto* box : boxes) {
        scroll->remove(box);
        delete box;
    }
    boxes.clear();
    rowPositions.clear();

    const int startX = 50;   
    const int startY = 300;   
    const int spacingY = 5; 
    for (size_t i = 0; i < flightsToShow.size(); ++i) {
        rowPositions.push_back(RowPosition(startX, startY + i * (boxHeight + spacingY), colWidth, boxHeight));
    }

    // Inicijalizacija tabele koja prikazuje letove
    for (size_t i = 0; i < flightsToShow.size(); ++i) {
        RowPosition& pos = rowPositions[i];
        int x = pos.x;

        Fl_Box* flightNoBox = new Fl_Box(x, pos.y, colWidth, boxHeight, flightsToShow[i].flightNo.c_str());
        setupBox(flightNoBox);
        x += colWidth + borderWidth;

        Fl_Box* destinationBox = new Fl_Box(x, pos.y, colWidth, boxHeight, flightsToShow[i].destination.c_str());
        setupBox(destinationBox);
        x += colWidth + borderWidth;

        Fl_Box* departureBox = new Fl_Box(x, pos.y, colWidth, boxHeight, flightsToShow[i].departure.c_str());
        setupBox(departureBox);
        x += colWidth + borderWidth;

        Fl_Box* gateNoBox = new Fl_Box(x, pos.y, colWidth, boxHeight, flightsToShow[i].gateNo.c_str());
        setupBox(gateNoBox);

        boxes.push_back(flightNoBox);
        boxes.push_back(destinationBox);
        boxes.push_back(departureBox);
        boxes.push_back(gateNoBox);

        scroll->add(flightNoBox);
        scroll->add(destinationBox);
        scroll->add(departureBox);
        scroll->add(gateNoBox);
    }

    scroll->redraw();
    this->redraw();
}

void MyWindow::setupBox(Fl_Box* box) {
    box->box(FL_FLAT_BOX);
    box->color(FL_WHITE);
    box->redraw();
}

/*
    Funkcija za boldovanje redova (letova) koji menjaju poziciju unutar tabele - oznaceni su crvenom bojom tokom animacije
    int row1, int row2 - Redovi u tabeli koji menjaju pozicije
*/
void MyWindow::highlightRows(int row1, int row2) {
    Fl_Color highlightColor = FL_RED;

    int boxIndex1 = row1 * 4; 
    int boxIndex2 = row2 * 4;

    for (int i = 0; i < 4; ++i) { 
        if (boxIndex1 + i < boxes.size()) {
            boxes[boxIndex1 + i]->color(highlightColor);
            boxes[boxIndex1 + i]->redraw();
        }
        if (boxIndex2 + i < boxes.size()) {
            boxes[boxIndex2 + i]->color(highlightColor);
            boxes[boxIndex2 + i]->redraw();
        }
    }
}

void MyWindow::resetHighlighting() {
    Fl_Color defaultColor = FL_WHITE;

    for (auto* box : boxes) {
        box->color(defaultColor);
        box->redraw();
    }
}

