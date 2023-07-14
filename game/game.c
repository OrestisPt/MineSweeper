#include "raylib.h"
#include "interface.h"
#include "state.h"

State state;

int main(void){
    state = state_create();
    interface_init();
    while(!WindowShouldClose()){
        StateInfo info = state_info(state);
        if(info->is_game_over){
            if(IsKeyPressed(KEY_R)){
                state_destroy(state);
                state = state_create();
            }
        }
        if(IsKeyPressed(KEY_R) && IsKeyDown(KEY_LEFT_CONTROL)){
            state_destroy(state);
            state = state_create();
        }
        state_update(state);
        interface_draw_frame(state);
        stateinfo_destroy(info);
    }
    interface_close();
    state_destroy(state);
}