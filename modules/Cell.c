#include "Cell.h"

struct cell {
    bool is_mine;
    bool is_revealed;
    bool is_flagged;
    int adjacent_mines;
};

Cell cell_create(int x, int y, bool is_mine, bool is_revealed, bool is_flagged){
    Cell cell = malloc(sizeof(struct cell));
    cell->is_mine = is_mine;
    cell->is_revealed = is_revealed;
    cell->is_flagged = is_flagged;
    return cell;
}

bool cell_is_mine(Cell cell){
    return cell->is_mine;
}

bool cell_is_revealed(Cell cell){
    return cell->is_revealed;
}

bool cell_is_flagged(Cell cell){
    return cell->is_flagged;
} 

void cell_set_adjacent_mines(Cell cell, int value){
    cell->adjacent_mines = value;
}

void cell_set_revealed(Cell cell){
    cell->is_revealed = true;
}

void cell_set_flagged(Cell cell, bool value){
    cell->is_flagged = value;
}

int compute_adjacent_mines(Cell** array, int x, int y){
    int count = 0;
    for(int i = x - 1; i <= x + 1; i++){
        for(int j = y - 1; j <= y + 1; j++){
            if(i >= 0 && i < 16 && j >= 0 && j < 16){
                if(cell_is_mine(array[i][j])){
                    count++;
                }
            }
        }
    }
    return count;
}

int cell_get_mine_count(Cell cell){
    return cell->adjacent_mines;
}

void set_mines(Cell** array, int nummines){
    srand(time(NULL));
    for(int i = 0; i < nummines; i++){
        int x = rand() % 16;
        int y = rand() % 16;
        if(!cell_is_mine(array[x][y])){
            array[x][y]->is_mine = true;
        }
        else{
            i--;
        }
    }
}

void reveal_zero_pool(Cell** array, int x, int y){
    for(int i = x - 1; i <= x + 1; i++){
        for(int j = y - 1; j <= y + 1; j++){
            if(i >= 0 && i < 16 && j >= 0 && j < 16){
                if(cell_get_mine_count(array[i][j]) == 0 && !cell_is_revealed(array[i][j])){
                    array[i][j]->is_revealed = true;
                    reveal_zero_pool(array, i, j);
                }
                else{
                    array[i][j]->is_revealed = true;
                }
            }
        }
    }
}

void cell_destroy(Cell cell){
    free(cell);
}