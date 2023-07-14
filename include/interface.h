#pragma once
#include "state.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

void interface_init(void);

void interface_draw_frame(State state);

void interface_close(void);