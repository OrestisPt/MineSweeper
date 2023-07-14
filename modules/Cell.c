#include "Cell.h"

Cell cell_create(int x, int y, bool is_mine, bool is_revealed, bool is_flagged){
    Cell cell = malloc(sizeof(struct cell));
    cell->x = x;
    cell->y = y;
    cell->is_mine = is_mine;
    cell->is_revealed = is_revealed;
    cell->is_flagged = is_flagged;
    return cell;
}

int cell_get_x(Cell cell){
    return cell->x;
}

int cell_get_y(Cell cell){
    return cell->y;
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
    
}