#include "raylib.h"
#include "interface.h"
#include "Cell.h"

void interface_init(void){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MineSweeper"); 
    SetTargetFPS(60);
    InitAudioDevice();
}

void interface_draw_frame(State state){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    StateInfo info = state_info(state);
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            if(cell_is_revealed(info->array[i][j])){
                DrawRectangle(i * SCREEN_WIDTH/17 + 20, j * SCREEN_HEIGHT/17 + 20, SCREEN_WIDTH/17, SCREEN_HEIGHT/17, WHITE);
                if(cell_is_mine(info->array[i][j])){
                    DrawRectangle(i * SCREEN_WIDTH/17 + 20, j * SCREEN_HEIGHT/17 + 20, SCREEN_WIDTH/17, SCREEN_HEIGHT/17, RED);
                }
                else{
                    DrawText(TextFormat("%2d", cell_get_mine_count(info->array[i][j])), i * SCREEN_WIDTH/17 + 20, j * SCREEN_HEIGHT/17 + 25, 40, BLACK);
                }
            }
            else{
                DrawRectangle(i * SCREEN_WIDTH/17 + 20, j * SCREEN_HEIGHT/17 + 20, SCREEN_WIDTH/17, SCREEN_HEIGHT/17, GRAY);
            }
            DrawRectangleLines(i * SCREEN_WIDTH/17 + 20, j * SCREEN_HEIGHT/17 + 20, SCREEN_WIDTH/17, SCREEN_HEIGHT/17, BLACK);
        }
    }
    stateinfo_destroy(info);
    EndDrawing();
}

void interface_close(void){
    CloseWindow();
    CloseAudioDevice();
}