#include "state.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdbool.h>

struct state{
    Cell** array;
    bool is_game_over;
    bool is_game_won;
    bool is_game_lost;
    int revealed_count;
};

State state_create(void){
    State state = malloc(sizeof(struct state));
    state->array = malloc(sizeof(Cell*) * 16);
    for(int i = 0; i < 16; i++){
        state->array[i] = malloc(sizeof(Cell) * 16);
    }
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            state->array[i][j] = cell_create(i, j, false, false, false);
        }
    }
    set_mines(state->array, 40);
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            cell_set_adjacent_mines(state->array[i][j], compute_adjacent_mines(state->array, i, j)); 
        }
    }
    state->is_game_over = false;
    state->is_game_won = false;
    state->is_game_lost = false;
    state->revealed_count = 0;

    return state;
}

void state_update(State state){
    if(state->is_game_over){
        return;
    }
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        int MouseX = GetMouseX();
        int MouseY = GetMouseY(); 
        if(MouseX < 20 || MouseX > 780 || MouseY < 20 || MouseY > 780){
            return;
        }
        MouseX -= 20;
        MouseX /= (SCREEN_WIDTH/17);
        MouseY -= 20;
        MouseY /= (SCREEN_HEIGHT/17);
        if(MouseX < 0 || MouseX > 15 || MouseY < 0 || MouseY > 15){
            return;
        }
        Cell cell = state->array[MouseX][MouseY];
        if(cell_is_mine(cell) && !cell_is_flagged(cell)){
            cell_set_revealed(cell);
            reveal_all_mines(state->array);
            state->is_game_over = true;
            state->is_game_lost = true;
            return;
        }
        if(!cell_is_flagged(cell)){
            cell_set_revealed(cell);
        }
        if(cell_get_mine_count(cell) == 0 && !cell_is_flagged(cell)){
            state->revealed_count -= 1;
            reveal_zero_pool(state->array, MouseX, MouseY);
        }
        
    }
    int count = 0;
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            if(cell_is_revealed(state->array[i][j]) && !cell_is_mine(state->array[i][j])){
                count += 1;
            }
        }
    }
    state->revealed_count = count;
    if(state->revealed_count >= 216){
        state->is_game_over = true;
        state->is_game_won = true;
        return;
    }
    if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
        int MouseX = GetMouseX();
        int MouseY = GetMouseY(); 
        if(MouseX < 20 || MouseX > 780 || MouseY < 20 || MouseY > 780){
            return;
        }
        MouseX -= 20;
        MouseX /= (SCREEN_WIDTH/17);
        MouseY -= 20;
        MouseY /= (SCREEN_HEIGHT/17);
        if(MouseX < 0 || MouseX > 15 || MouseY < 0 || MouseY > 15){
            return;
        }
        Cell cell = state->array[MouseX][MouseY];
        cell_set_flagged(cell, !cell_is_flagged(cell));
    }
}

StateInfo state_info(State state){
    StateInfo info = malloc(sizeof(struct state_info));
    info->is_game_over = state->is_game_over;
    info->is_game_won = state->is_game_won;
    info->is_game_lost = state->is_game_lost;
    info->array = state->array;
    return info;
}

void stateinfo_destroy(StateInfo info){
    free(info);
}

void state_destroy(State state){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            cell_destroy(state->array[i][j]);
        }
    }
    for(int i = 0; i < 16; i++){
        free(state->array[i]);
    }
    free(state->array);
    free(state);
}