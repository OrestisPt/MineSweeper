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
        int size = MeasureText("You Win!", 40);
        DrawRectangle(SCREEN_WIDTH/2 - size/2 ,SCREEN_HEIGHT/2, size, 40, RAYWHITE);
        DrawText("You Win!", SCREEN_WIDTH/2 - size/2 ,SCREEN_HEIGHT/2, 40, BLACK);
    }
    if(info->is_game_lost){
        int size = MeasureText("You Lose!", 40);
        DrawRectangle(SCREEN_WIDTH/2 - size/2 ,SCREEN_HEIGHT/2, size, 40, RAYWHITE);
        DrawText("You Lose!", SCREEN_WIDTH/2 - size/2 ,SCREEN_HEIGHT/2, 40, BLACK);
    }
    EndDrawing();
    stateinfo_destroy(info);
}

void interface_close(void){
    CloseWindow();
    CloseAudioDevice();
}