#include <nranked.h>
#include <rgui.h>
#include <tabs/search/searchstate.h>
#include <naett/naett.h>

#include <messagebox.h>






int main(){
    naettInit(NULL);
    SetTargetFPS(30);
    InitWindow(800, 600, "Hello!");
    RGUIInit("resources/theme/default.rgs");

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