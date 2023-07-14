#include "state.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdbool.h>

struct state{
    Cell** array;
    bool is_game_over;
    bool is_game_won;
    bool is_game_lost;
};

State state_create(void){
    State state = malloc(sizeof(struct state));
    state->array = malloc(sizeof(Cell) * 16);
    for(int i = 0; i < 16; i++){
        state->array[i] = malloc(sizeof(*state->array) * 16);
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
    return state;
}

void state_update(State state){
    if(state->is_game_over){
        return;
    }
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        int MouseX = GetMouseX();
        int MouseY = GetMouseY(); 
        MouseX -= 20;
        MouseX /= (SCREEN_WIDTH/17);
        MouseY -= 20;
        MouseY /= (SCREEN_HEIGHT/17);
        Cell cell = state->array[MouseX][MouseY];
        if(cell_is_mine(cell)){
            cell_set_revealed(cell);
            state->is_game_over = true;
            state->is_game_lost = true;
            return;
        }
        if(!cell_is_flagged(cell))
            cell_set_revealed(cell);
        if(cell_get_mine_count(cell) == 0){
            reveal_zero_pool(state->array, MouseX, MouseY);
        }
        
    }
    if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
        int MouseX = GetMouseX();
        int MouseY = GetMouseY(); 
        MouseX -= 20;
        MouseX /= (SCREEN_WIDTH/17);
        MouseY -= 20;
        MouseY /= (SCREEN_HEIGHT/17);
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
        free(state->array[i]);
    }
    free(state->array);
    free(state);
}