#pragma once
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct cell *Cell;

Cell cell_create(int row, int col, bool is_mine, bool is_revealed, bool is_flagged);

void cell_set_revealed(Cell cell);

void cell_set_flagged(Cell cell, bool value);

void cell_set_adjacent_mines(Cell cell, int value);

void reveal_zero_pool(Cell** array, int x, int y);

bool cell_is_mine(Cell cell);

bool cell_is_revealed(Cell cell);  

bool cell_is_flagged(Cell cell);

int cell_get_mine_count(Cell cell);

int compute_adjacent_mines(Cell** array, int x, int y);

void set_mines(Cell** array, int num_mines);

void cell_destroy(Cell cell);