#include "MyWindow.h"
#include <vector>
#include <string>
#include "Flight.h"
#include <iostream>
#include <FL/Fl_Box.h>
#include "SortCriteria.h"
#include "SortAlgorithm.h"
#include <vector>

// Ovde morate da koristite potpis konstruktora koji ste definisali u .h fajlu
MyWindow::MyWindow(int w, int h, const char* title, std::vector<Flight> flightsToShow)
    : Fl_Window(w, h, title), flightsToShow(flightsToShow), i(0), j(1), min_idx(0), isSorting(false) {
    // Inicijalizujte korisnički interfejs komponente ovde
    // Na primer, stvaranje dugmeta za sortiranje
    sort_button = new Fl_Button(10, 10, 80, 30, "Sort");
    sort_button->callback(cb_sort, this);

    input_path = new Fl_Input(100, 10, 200, 30);
    output_path = new Fl_Output(100, 50, 200, 30);
    sort_menu = new Fl_Choice(100, 90, 200, 30);
    scroll = new Fl_Scroll(10, 10, w - 20, h - 20);
    scroll->type(Fl_Scroll::VERTICAL_ALWAYS);

    int animationState = 0;

    sort_criteria_label = new Fl_Box(130, 10, 120, 25, "Sort Criteria");

    sort_criteria_choice = new Fl_Choice(250, 10, 120, 25); // Adjust position and size as needed
    sort_criteria_choice->add("Departure Time");
    sort_criteria_choice->add("Destination");
    sort_criteria_choice->add("Flight Number");
    sort_criteria_choice->add("Gate Number");
    sort_criteria_choice->callback(cb_sort_criteria, this);

    sort_algorithm_label = new Fl_Box(520, 10, 120, 25, "Sort Algorithm");

    sort_algorithm_choice = new Fl_Choice(650, 10, 120, 25); // Adjust position and size as needed
    sort_algorithm_choice->add("Selection Sort");
    sort_algorithm_choice->add("Quick Sort");
    sort_algorithm_choice->callback(cb_sort_criteria, this);

    sortingCompleteLabel = new Fl_Box(160, 10, 120, 25);
    sortingCompleteLabel->hide();

    this->end(); // End of adding widgets to the window
    this->show(); // Show the window
    // itd.

    // Ovde treba dodati ostale UI elemente...
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

void MyWindow::sort_pressed() {
    if (!isSorting) {
        i = 0;
        isSorting = true;
    }

    if (i < flightsToShow.size() - 1) {
        if (j <= flightsToShow.size()) {
            min_idx = i;
            for (j = i + 1; j < flightsToShow.size(); ++j) {
                if (flightsToShow[j] < flightsToShow[min_idx]) {
                    min_idx = j;
                }
            }

            if (min_idx != i) {
                std::swap(flightsToShow[min_idx], flightsToShow[i]);
                startAnimation(i, min_idx);
                i++;
                return;
            }
            i++;
        }
        else {
            isSorting = false;
            sortingCompleteLabel->show();
        }
    }
    else {
        isSorting = false;
        sortingCompleteLabel->show();
    }
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
        sortCriteria = SortCriteria(SortField::DepartureTime);
        break;
    case 1:
        sortCriteria = SortCriteria(SortField::Destination);
        break;
    case 2:
        sortCriteria = SortCriteria(SortField::FlightNumber);
        break;
    case 3:
        sortCriteria = SortCriteria(SortField::GateNumber);
        break;
    default:
        // Handle default case
        break;
    }

    // Add code to re-sort the flights or update the UI as needed
}

void MyWindow::sort_algorithm_changed() {
    int choice = sort_algorithm_choice->value();
    switch (choice) {
    case 0:
        sortAlgorithm = SortAlgorithm::SelectionSort;
        break;
    case 1:
        sortAlgorithm = SortAlgorithm::QuickSort;
        break;
    default:
        // Handle default case
        break;
    }

    // Add code to re-sort the flights or update the UI as needed
}

void MyWindow::setFlights(const std::vector<Flight>& flights) {
    flightsToShow = flights;
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
    const int startY = 150;   // Starting Y position for the table
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





// Nastavite sa definisanjem ostalih funkcija po potrebi...
