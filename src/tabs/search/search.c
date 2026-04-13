#include <tabs/search/search.h>
#include <rgui.h>
#include <network/netthread.h>
#include <tabs/search/searchstate.h>

// more global state, yay =(
static char searchBuffer[16];

void DrawSearch(){
    const char greetingText[] = "Search for a player";
    const char buttonText[] = "Search";
    int greetingTextSize = RGUIMeasureTextWidth(greetingText, 40);
    Vector2 textPos = {(Width() - greetingTextSize) / 2, Height() / 2 - 60};
    Rectangle textBoxBounds = {250, Height() / 2, Width() - 500, 20};
    Rectangle enterButtonBounds = {(Width() - 90) / 2, Height() / 2 + 30, 90, 30};
    
    RGUIDrawText(textPos, greetingText, 40);
    RGUITextBox(textBoxBounds, searchBuffer, 16, true);
    int enterButton = RGUIDrawButton(enterButtonBounds, buttonText);
    if(enterButton == 1){
        SetSearchState(SSTATE_LOADING);
        StartNetSearchThread(searchBuffer);
    }
}