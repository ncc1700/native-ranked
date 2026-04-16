#include <nranked.h>
#include <rgui.h>
#include <tabs/search/searchstate.h>
#include <naett/naett.h>

#include <messagebox.h>






int main(){
    naettInit(NULL);
    SetTraceLogLevel(LOG_ERROR);
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    InitWindow(700, 700, "Hello!");
    RGUIInit("resources/theme/jungle.rgs");

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RGUIGetBackgroundColor());
        HandleSearch();
        HandleMessages();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}