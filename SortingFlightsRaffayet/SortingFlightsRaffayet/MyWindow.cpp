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
MyWindow::MyWindow(int w, int h, const char* title, std::vector<Flight> flightsToShow, DataStorage storage, SortingManager sortingManager)
    : Fl_Window(w, h, title), flightsToShow(flightsToShow), flightsStorage(storage), sortingManager(sortingManager), i(0), j(1), min_idx(0), isSorting(false) {
    // Inicijalizujte korisnički interfejs komponente ovde
    // Na primer, stvaranje dugmeta za sortiranje
    sort_button = new Fl_Button(50, 170, 80, 30, "Sort");
    sort_button->callback(cb_sort, this);
    input_path = new Fl_Input(100, 20, 210, 30, "Input Path");
    output_path = new Fl_Input(450, 20, 210, 30, "Output Path");
    confirmPathButton = new Fl_Button(800, 20, 100, 30, "Confirm path");
    /*sort_menu = new Fl_Choice(100, 90, 200, 30);*/
    scroll = new Fl_Scroll(10, 130, w - 20, h - 140);
    scroll->type(Fl_Scroll::VERTICAL_ALWAYS);
    
    Fl_Input* inputs[2] = { input_path, output_path };
    confirmPathButton->callback(MyWindow::onChangePathButtonWrapper, this);

    int animationState = 0;

    sort_criteria_label = new Fl_Box(180, 170, 120, 25, "Sort Criteria");

    sort_criteria_choice = new Fl_Choice(300, 170, 160, 25); // Adjust position and size as needed
    sort_criteria_choice->add("Departure Time");
    sort_criteria_choice->add("Destination");
    sort_criteria_choice->add("Flight Number");
    sort_criteria_choice->add("Gate Number");
    sort_criteria_choice->value(0);
    sort_criteria_choice->callback(cb_sort_criteria, this);

    sort_algorithm_label = new Fl_Box(520, 170, 120, 25, "Sort Algorithm");

    sort_algorithm_choice = new Fl_Choice(650, 170, 160, 25); // Adjust position and size as needed
    sort_algorithm_choice->add("Selection Sort");
    sort_algorithm_choice->add("Bubble Sort");
    sort_algorithm_choice->add("Quick Sort");
    sort_algorithm_choice->value(0);
    sort_algorithm_choice->callback(cb_sort_algorithm, this);

    sortingCompleteLabel = new Fl_Box(300, 500, 300, 300);
    sortingCompleteLabel->hide();

    this->end(); // End of adding widgets to the window
    this->show(); // Show the window
    // itd.

    // Ovde treba dodati ostale UI elemente...
}

void MyWindow::onChangePathButton(Fl_Widget*) {
    std::cout << "Input File Path: " << input_path->value() << std::endl;
    std::cout << "Output File Path: " << output_path->value() << std::endl;

    flightsStorage.flightsDataPath = input_path->value();
    flightsStorage.flightsHistoryPath = output_path->value();
    vector<Flight> newFlights = flightsStorage.loadFlights();
    this->setFlights(newFlights);
}

void MyWindow::onChangePathButtonWrapper(Fl_Widget* w, void* v) {
    // Cast the void pointer back to MyWindow instance
    MyWindow* window = static_cast<MyWindow*>(v);
    window->onChangePathButton(w);
}

void MyWindow::startAnimation(int firstRowIndex, int secondRowIndex) {
    originalColors.clear();

    firstAnimatedRow = firstRowIndex;
    secondAnimatedRow = secondRowIndex;

    // Store colors for the specified rows
    int startIndexFirstRow = firstRowIndex * 4; // Assuming 4 boxes per row
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
    window->animate(); // Call the member function to handle animation logic
}

void MyWindow::updateRow(int upRowIndex, int downRowIndex, float progress) {
    // Dobijanje početnih i krajnjih pozicija iz rowPositions
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

    // Redraw the scroll to update the view
    scroll->redraw();
}

void MyWindow::returnPreviousColor(int upRowIndex, int downRowIndex) {
    // Reset colors for the up-moving row
    for (int i = 0; i < 4; ++i) {
        int boxIndex = upRowIndex * 4 + i;
        if (boxIndex < boxes.size()) {
            Fl_Box* box = boxes[boxIndex];
            box->color(originalColors[i]); // Use the first 4 colors for up row
            box->redraw();
        }
    }

    // Reset colors for the down-moving row
    for (int i = 0; i < 4; ++i) {
        int boxIndex = downRowIndex * 4 + i;
        if (boxIndex < boxes.size()) {
            Fl_Box* box = boxes[boxIndex];
            box->color(originalColors[i + 4]); // Use the next 4 colors for down row
            box->redraw();
        }
    }
}


void MyWindow::animate() {
    if (isAnimating) {
        const float duration = 1.0; // Total duration of the animation in seconds
        animationProgress += 0.05f / duration;

        if (animationProgress >= 1.0) {
            // Clamp the progress and end the animation
            animationProgress = 1.0;
            isAnimating = false;

            // Zamena pozicija u rowPositions
            std::swap(rowPositions[firstAnimatedRow], rowPositions[secondAnimatedRow]);

            // Reset colors to their original values after the animation ends
            returnPreviousColor(firstAnimatedRow, secondAnimatedRow);

            // Osvežavanje položaja svih box-ova na osnovu novih rowPositions
            updateAllRows();
        }
        else {
            // Update the row positions based on the current progress
            updateRow(firstAnimatedRow, secondAnimatedRow, animationProgress);
        }

        // Redraw the window to reflect the changes
        redraw();

        if (isAnimating) {
            // Schedule the next frame of the animation
            Fl::repeat_timeout(0.05, animate_callback, this);
        }
        else {
            // Here you could start another animation if needed, or perform other actions
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
                std::swap(flightsToShow[min_idx], flightsToShow[i]);
                std::swap(rowPositions[min_idx], rowPositions[i]);
                flightHistory.movementCount++;
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

void MyWindow::bubbleSort() {
    if (!sortingManager.sortingInProgress()) {
        // Initialize sorting parameters
        i = 0;
        j = 0;
        sortingManager.startSorting();
        return;
    }

    // Check if sorting is complete
    if (i >= flightsToShow.size() - 1) {
        sortingManager.finishSorting();
        return;
    }

    if (j < flightsToShow.size() - i - 1) {
        flightHistory.comparisonCount++;
        if (flightsToShow[j] > flightsToShow[j + 1]) {
            // Swap the flights and their positions
            std::swap(flightsToShow[j], flightsToShow[j + 1]);
            std::swap(rowPositions[j], rowPositions[j + 1]);
            flightHistory.movementCount++;
            // Start the animation for this swap
            startAnimation(j, j + 1);

            // Prepare for next comparison
            j++;
            return; // Return here to allow the animation to complete before the next iteration
        }
        j++;
    }
    else {
        // Move to the next pass
        i++;
        j = 0;
    }
}


void MyWindow::oneStepQuickSort() {
    if (quickSortStack.empty()) {
        sortingManager.finishSorting();
        cout << "Sorting complete." << endl;
        return;
    }

    QuickSortState state = quickSortStack.top();
    quickSortStack.pop();

    cout << "Current State: Low = " << state.low << ", High = " << state.high << endl;

    if (state.low < state.high) {
        int pivotIndex = partition(state.low, state.high);
        cout << "Pivot Index: " << pivotIndex << " after partitioning between " << state.low << " and " << state.high << endl;

        // Ensure that the subarrays excluding the pivot are pushed onto the stack
        if (pivotIndex > state.low) {
            quickSortStack.push(QuickSortState(state.low, pivotIndex - 1));
            cout << "Pushing left subarray: Low = " << state.low << ", High = " << pivotIndex - 1 << endl;
        }

        if (pivotIndex < state.high) {
            quickSortStack.push(QuickSortState(pivotIndex + 1, state.high));
            cout << "Pushing right subarray: Low = " << pivotIndex + 1 << ", High = " << state.high << endl;
        }
    }
}


void MyWindow::quickSort(int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[pi] is now at right place 
        int pi = partition(low, high);

        // Separately sort elements before partition and after partition
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

int MyWindow::partition(int low, int high) {
    Flight pivot = flightsToShow[high]; // pivot
    cout << "Partitioning with pivot at index " << high << " (Pivot: " << pivot.gateNo << ")" << endl;
    int i = (low - 1); // Index of smaller element

    for (int j = low; j < high; j++) {
        cout << "Comparing index " << j << " with pivot." << endl;
        flightHistory.comparisonCount++;
        if (flightsToShow[j] < pivot) {
            i++; // increment index of smaller element
            std::swap(flightsToShow[i], flightsToShow[j]);
            std::swap(rowPositions[i], rowPositions[j]);
            cout << "Swapped index " << i << " with index " << j << endl;
            flightHistory.movementCount++;
            // Optionally, start animation for this swap
            startAnimation(i, j);
        }
    }
    std::swap(flightsToShow[i + 1], flightsToShow[high]);
    std::swap(rowPositions[i + 1], rowPositions[high]);
    cout << "Swapped pivot to index " << (i + 1) << endl;
    flightHistory.movementCount++;
    // Optionally, start animation for this swap
    startAnimation(i + 1, high);

    return (i + 1);
}


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
        // Handle default case
        break;
    }
    // Add code to re-sort the flights or update the UI as needed
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
        // Handle default case
        break;
    }
    // Add code to re-sort the flights or update the UI as needed
}

void MyWindow::setFlights(const std::vector<Flight>& flights) {
    this->flightsToShow = flights;
    const int colWidth = 220; // Width for each column
    const int boxHeight = 25;  // Height of the rows
    const int borderWidth = 1; // Width of the border
    const int numCols = 4;     // Number of columns

    // Clear previous widgets and positions
    for (auto* box : boxes) {
        scroll->remove(box);
        delete box;
    }
    boxes.clear();
    rowPositions.clear();

    // Initialize row positions
    const int startX = 50;    // Starting X position for the table
    const int startY = 300;   // Starting Y position for the table
    const int spacingY = 5;   // Spacing between rows
    for (size_t i = 0; i < flightsToShow.size(); ++i) {
        rowPositions.push_back(RowPosition(startX, startY + i * (boxHeight + spacingY), colWidth, boxHeight));
    }

    // Create and add boxes for each flight
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

        // Add the boxes to the vector and the scroll
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


void MyWindow::highlightRows(int row1, int row2) {
    Fl_Color highlightColor = FL_RED; // Color for highlighting

    // Calculate the index for each box in the rows
    int boxIndex1 = row1 * 4; // Assuming 4 boxes per row
    int boxIndex2 = row2 * 4;

    // Highlight the boxes in the specified rows
    for (int i = 0; i < 4; ++i) { // Loop through each box in the row
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
    Fl_Color defaultColor = FL_WHITE; // Default color

    for (auto* box : boxes) {
        box->color(defaultColor);
        box->redraw();
    }
}

