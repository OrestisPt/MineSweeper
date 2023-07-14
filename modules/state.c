#include "state.h"
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
            state->array[i][j] = cell_create(i, j, false, true, false);
        }
    }
    state->array[0][0]->is_mine = true;
    state->array[0][2]->is_mine = true;
    set_mines(state->array, 40);
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            state->array[i][j]->adjacent_mines = compute_adjacent_mines(state->array, i, j);
        }
    }
    return state;
}

void state_update(State state){

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