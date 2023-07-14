#include "raylib.h"
#include "interface.h"
#include "state.h"

State state;

int main(void){
    state = state_create();
    interface_init();
    while(!WindowShouldClose()){
        state_update(state);
        interface_draw_frame(state);
    }
    interface_close();
    state_destroy(state);
}