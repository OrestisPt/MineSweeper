#include "raylib.h"
#include "interface.h"
#include "Cell.h"

Texture2D bomb;
Texture2D flag;

void interface_init(void){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MineSweeper"); 
    bomb = LoadTexture("assets/bomb.png");
    flag = LoadTexture("assets/flag.png");
    SetTargetFPS(60);
    InitAudioDevice();
}

void interface_draw_frame(State state){
    StateInfo info = state_info(state);
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            if(cell_is_revealed(info->array[i][j])){
                DrawRectangle(i * SCREEN_WIDTH/17 + 20, j * SCREEN_HEIGHT/17 + 20, SCREEN_WIDTH/17, SCREEN_HEIGHT/17, WHITE);
                if(cell_is_mine(info->array[i][j])){
                    DrawRectangle(i * SCREEN_WIDTH/17 + 20, j * SCREEN_HEIGHT/17 + 20, SCREEN_WIDTH/17, SCREEN_HEIGHT/17, RED);
                    DrawTexture(bomb, i * SCREEN_WIDTH/17 + 20, j * SCREEN_HEIGHT/17 + 20, WHITE);
                }
                else{
                    DrawText(TextFormat("%2d", cell_get_mine_count(info->array[i][j])), i * SCREEN_WIDTH/17 + 20, j * SCREEN_HEIGHT/17 + 25, 40, BLACK);
                }
            }
            else if(cell_is_flagged(info->array[i][j])){
                DrawRectangle(i * SCREEN_WIDTH/17 + 20, j * SCREEN_HEIGHT/17 + 20, SCREEN_WIDTH/17, SCREEN_HEIGHT/17, YELLOW);
                DrawTexture(flag, i * SCREEN_WIDTH/17 + 20, j * SCREEN_HEIGHT/17 + 20, WHITE);
            }
            else{
                DrawRectangle(i * SCREEN_WIDTH/17 + 20, j * SCREEN_HEIGHT/17 + 20, SCREEN_WIDTH/17, SCREEN_HEIGHT/17, GRAY);
            }
            DrawRectangleLines(i * SCREEN_WIDTH/17 + 20, j * SCREEN_HEIGHT/17 + 20, SCREEN_WIDTH/17, SCREEN_HEIGHT/17, BLACK);
        }
    }
    if(info->is_game_won){
    DrawText("You Win!", 20, 20, 40, BLACK);
    }
    if(info->is_game_lost){
        DrawText("You Lose!", 20, 20, 40, BLACK);
    }
    EndDrawing();
    stateinfo_destroy(info);
}

void interface_close(void){
    CloseWindow();
    CloseAudioDevice();
}