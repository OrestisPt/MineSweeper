#pragma once
#include <stdlib.h>
#include <stdbool.h>

typedef struct cell *Cell;

struct cell {
    int x;
    int y;
    bool is_mine;
    bool is_revealed;
    bool is_flagged;
    int adjacent_mines;
};

Cell cell_create(int row, int col, bool is_mine, bool is_revealed, bool is_flagged);

bool cell_is_mine(Cell cell);

bool cell_is_revealed(Cell cell);  

int cell_get_mine_count(Cell cell);

int cell_get_x(Cell cell);

int cell_get_y(Cell cell);

int compute_adjacent_mines(Cell** array, int x, int y);

void set_mines(Cell** array, int num_mines);