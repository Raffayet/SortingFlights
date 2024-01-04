/*
    GUI row za prikaz svih atributa jednog leta
    Autor: Nikola Sovilj SW75/2019
    Poslednja izmena: 04/01/2024
*/

#pragma once
struct RowPosition {
    int x, y, width, height;

    RowPosition(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height) {}
};