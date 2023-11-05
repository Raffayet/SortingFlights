#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "graph_lib/Simple_window.h" // Pretpostavljamo da imate ovakvu strukturu
#include "DataStorage.h"

class MyWindow : public Simple_window {
public:
    MyWindow(Point xy, int w, int h, const string& title);

    // Metode za rad sa korisnickim interfejsom

private:
    // Privatni clanovi, dugmad, unosna polja itd.
    Button sort_button;
    In_box input_path;
    Out_box output_path;
    Menu sort_menu;
    // itd.

    // Callback funkcije za događaje
    static void cb_sort(Address, Address pw);
    // itd.

    // Funkcije koje se pozivaju pri događajima
    void sort_pressed();
    // itd.

    DataStorage dataStorage; // Instanca klase za cuvanje podataka
};

#endif // MYWINDOW_H
