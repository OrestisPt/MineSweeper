#pragma once
#include "Cell.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

typedef struct state *State;

typedef struct state_info{
    Cell** array;
    bool is_game_over;
    bool is_game_won;
    bool is_game_lost;
} *StateInfo;

State state_create(void);

void state_update(State state);

StateInfo state_info(State state);

void state_destroy(State state);

void stateinfo_destroy(StateInfo info);