#pragma once
struct RowPosition {
    int x, y, width, height;

    RowPosition(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height) {}
};