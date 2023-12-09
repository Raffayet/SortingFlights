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

void MyWindow::startAnimation(int row1, int row2) {
    // Set up initial animation states
    isAnimating = true;
    animatingRow1 = row1;
    animatingRow2 = row2;

    // Swap elements in the collection
    if (row1 < flightsToShow.size() && row2 < flightsToShow.size()) {
        std::swap(flightsToShow[row1], flightsToShow[row2]);
    }

    animationProgress = 0.0;

    // Start the animation
    Fl::add_timeout(0.05, &MyWindow::animate_callback, this);
}


void MyWindow::animate_callback(void* data) {
    MyWindow* window = static_cast<MyWindow*>(data);
    window->animate(window); // If 'animate' is a non-static member, you don't need to pass 'window'.
}


void MyWindow::animate(void* window) {
    MyWindow* win = static_cast<MyWindow*>(window);

    if (win->isAnimating) {
        const float duration = 1.0; // Total duration of the animation in seconds
        win->animationProgress += 0.05f / duration;

        if (win->animationProgress >= 1.0) {
            win->isAnimating = false; // Stop the animation
            win->animationProgress = 1.0; // Ensure progress doesn't exceed 1.0
        }

        // Example values for row height and padding
        const int rowHeight = 30; // Height of each row
        const int padding = 5;   // Space between rows

        // Starting Y positions for the first and fifth rows
        int startY1 = 150; // Example starting position for the first row
        int startY2 = startY1 + 4 * (rowHeight + padding); // Calculate position for fifth row

        // Target positions after the swap
        int targetY1 = startY2;
        int targetY2 = startY1;

        // Interpolate the positions
        int newY1 = startY1 + static_cast<int>((targetY1 - startY1) * win->animationProgress);
        int newY2 = startY2 + static_cast<int>((targetY2 - startY2) * win->animationProgress);

        // Update the positions of the elements in the first and fifth rows
        // This might involve moving the Fl_Box widgets or however you're displaying the flights

        win->redraw();

        if (!win->isAnimating) {
            // Swap the elements in the data structure here
            std::swap(win->flightsToShow[0], win->flightsToShow[4]); // Assuming 'flights' is your data structure
            // Reset positions to final locations
        }
        else {
            Fl::repeat_timeout(0.05, animate_callback, window); // Continue the animation
        }
    }
}


void MyWindow::sort_pressed() {
    highlightRows(0, 4);
    startAnimation(0, 4);
    //static int currentIndex = 0; // Tracks the current index for selection sort
    //static int minIndex = 0;     // Tracks the minimum value's index

    //if (currentIndex < flightsToShow.size() - 1) {
    //    resetHighlighting(); // Reset highlighting from the previous step

    //    // Find the minimum element in the unsorted part
    //    minIndex = currentIndex;
    //    for (int i = currentIndex + 1; i < flightsToShow.size(); i++) {
    //        if (flightsToShow[i].departure < flightsToShow[minIndex].departure) {
    //            minIndex = i;
    //        }
    //    }

    //    // Highlight the rows to be swapped
    //    highlightRows(currentIndex, minIndex);

    //    // Swap the found minimum element with the current element
    //    std::swap(flightsToShow[currentIndex], flightsToShow[minIndex]);

    //    // Update the display
    //    // (You should have a method to update the display based on the flights vector)

    //    // Prepare for the next step
    //    currentIndex++;
    //    if (currentIndex >= flightsToShow.size() - 1) {
    //        // Sorting is complete
    //        currentIndex = 0; // Reset for the next sort
    //    }
    //}
    //else {
    //    resetHighlighting(); // Reset highlighting when sorting is complete
    //}
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
