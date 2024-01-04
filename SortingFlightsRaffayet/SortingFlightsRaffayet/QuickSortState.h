/*
    Struktura za cuvanje stanja letova prilikom sortiranja pomocu Quick Sort algoritma
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/


#pragma once
struct QuickSortState {
    int low, high;
    QuickSortState(int low, int high) : low(low), high(high) {}
};

