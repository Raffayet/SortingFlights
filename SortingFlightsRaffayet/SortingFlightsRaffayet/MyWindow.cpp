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
MyWindow::MyWindow(int w, int h, const char* title, std::vector<Flight> flightsToShow) : Fl_Window(w, h, title) {
    // Inicijalizujte korisnički interfejs komponente ovde
    // Na primer, stvaranje dugmeta za sortiranje
    sort_button = new Fl_Button(10, 10, 80, 30, "Sort");
    sort_button->callback(cb_sort, this);

    input_path = new Fl_Input(100, 10, 200, 30);
    output_path = new Fl_Output(100, 50, 200, 30);
    sort_menu = new Fl_Choice(100, 90, 200, 30);
    scroll = new Fl_Scroll(10, 10, w - 20, h - 20);
    scroll->type(Fl_Scroll::VERTICAL_ALWAYS);

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

    this->end(); // End of adding widgets to the window
    this->show(); // Show the window
    // itd.

    // Ovde treba dodati ostale UI elemente...
}

void MyWindow::startAnimation() {
    isAnimating = true;
    animationProgress = 0.0;
    Fl::add_timeout(0.05, &MyWindow::animate_callback, this);
}

void MyWindow::animate_callback(void* data) {
    MyWindow* window = static_cast<MyWindow*>(data);
    window->animate();
}

void MyWindow::updateRow(int rowIndex, float progress, Fl_Color color) {
    const int boxHeight = 25;
    const int spacingY = 5;

    int startIndex = rowIndex * 4;

    // Starting and ending Y positions will depend on the row index
    int startY, endY;
    if (rowIndex == 0) {
        startY = 150; // Starting Y position for row 0
        endY = startY + 4 * (boxHeight + spacingY); // Ending Y position for row 0 (downward movement)
    }
    else if (rowIndex == 4) {
        startY = 150 + 4 * (boxHeight + spacingY); // Starting Y position for row 4
        endY = 150; // Ending Y position for row 4 (upward movement)
    }
    else {
        return; // For now, only handle rows 0 and 4
    }

    int newY = static_cast<int>(startY + (endY - startY) * progress);

    for (int i = 0; i < 4; ++i) {
        int boxIndex = startIndex + i;
        if (boxIndex < boxes.size()) {
            Fl_Box* box = boxes[boxIndex];
            box->color(color);
            box->hide();
            box->position(box->x(), newY);
            box->show();
            box->redraw();
        }
    }
}



void MyWindow::animate() {
    if (isAnimating) {
        const float duration = 1.0; // Total duration of the animation in seconds
        animationProgress += 0.05f / duration;

        if (animationProgress >= 1.0) {
            isAnimating = false;
            animationProgress = 1.0;
        }

        // Update the positions and colors of rows 0 and 4
        // Assuming you have a method to update position and color of rows
        updateRow(0, animationProgress, isAnimating ? FL_RED : FL_GRAY);
        updateRow(4, animationProgress, isAnimating ? FL_RED : FL_GRAY);

        redraw();

        if (!isAnimating) {
            std::swap(flightsToShow[0], flightsToShow[4]); // Final swap after animation ends
        }
        else {
            Fl::repeat_timeout(0.05, animate_callback, this);
        }
    }
}

void MyWindow::sort_pressed() {
    startAnimation();
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
    const int colWidth = 200; // Width for each column
    const int boxHeight = 25;  // Height of the rows
    const int borderWidth = 1; // Width of the border
    const int numCols = 4;     // Number of columns
    const int startX = 10;     // Starting X position for the table
    const int startY = 150;    // Starting Y position for the table
    const int spacingY = 5;    // Spacing between rows

    Fl_Color borderColor = fl_rgb_color(200, 200, 200); // Light grey border

    // Clear previous widgets
    for (auto* box : boxes) {
        scroll->remove(box);
        delete box;
    }
    boxes.clear();

    int y = startY;
    for (size_t i = 0; i < flights.size(); ++i) {
        int x = startX;
        // Create a border box for each row
        if (i > 0) { // Skip the border above the first row
            Fl_Box* borderBox = new Fl_Box(startX, y, this->w() - 20, borderWidth);
            borderBox->box(FL_FLAT_BOX); // Flat box looks like a line
            borderBox->color(borderColor);
            scroll->add(borderBox);
            boxes.push_back(borderBox);
            y += borderWidth;
        }

        // Create a box for each field in the Flight object
        Fl_Box* flightNoBox = new Fl_Box(x, y, colWidth, boxHeight);
        flightNoBox->box(FL_FLAT_BOX);
        flightNoBox->color(FL_WHITE);
        flightNoBox->label(flights[i].flightNo.c_str());
        x += colWidth + borderWidth;

        Fl_Box* destinationBox = new Fl_Box(x, y, colWidth, boxHeight);
        destinationBox->box(FL_FLAT_BOX);
        destinationBox->color(FL_WHITE);
        destinationBox->label(flights[i].destination.c_str());
        x += colWidth + borderWidth;

        Fl_Box* departureBox = new Fl_Box(x, y, colWidth, boxHeight);
        departureBox->box(FL_FLAT_BOX);
        departureBox->color(FL_WHITE);
        departureBox->label(flights[i].departure.c_str());
        x += colWidth + borderWidth;

        Fl_Box* gateNoBox = new Fl_Box(x, y, colWidth, boxHeight);
        gateNoBox->box(FL_FLAT_BOX);
        gateNoBox->color(FL_WHITE);
        gateNoBox->label(flights[i].gateNo.c_str());

        // Add the boxes to the vector and the scroll
        boxes.push_back(flightNoBox);
        boxes.push_back(destinationBox);
        boxes.push_back(departureBox);
        boxes.push_back(gateNoBox);

        scroll->add(flightNoBox);
        scroll->add(destinationBox);
        scroll->add(departureBox);
        scroll->add(gateNoBox);

        y += boxHeight + spacingY; // Move to the next row
    }

    scroll->redraw();
    this->redraw();
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
