#include "MyWindow.h"
#include <vector>
#include <string>
#include "Flight.h"
#include <iostream>
#include <FL/Fl_Box.h>
#include "SortCriteria.h"
#include "SortAlgorithm.h"

// Ovde morate da koristite potpis konstruktora koji ste definisali u .h fajlu
MyWindow::MyWindow(int w, int h, const char* title) : Fl_Window(w, h, title) {
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

void MyWindow::sort_pressed() {
    // Logika koja se izvršava kada se pritisne dugme za sortiranje
    const char* path = input_path->value();
    // Pretpostavljam da morate nekako koristiti ovu putanju i sortirati fajlove ili slično
    // ...
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




// Nastavite sa definisanjem ostalih funkcija po potrebi...
