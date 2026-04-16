#include <tabs/search/result.h>
#include <tabs/search/searchstate.h>
#include <storage.h>
#include <rgui.h>
#include <stdlib.h>
#include <nranked.h>
#include <string.h>
#include <messagebox.h>

static char* list[MAX_AMOUNT_OF_GAMEMODES];
static bool init = false;
static Texture text;
static int amount = 0;
static int scrollIndex = 0;
static int active = 0;
static int focus = 0;
static int state = 0;


static inline void SetupList(){
    amount = GetAmountFromSearch();
    for(int i = 0; i < amount; i++){
        PlayerGMData* data = GetGameModeFromIndex(i);
        list[i] = data->gameMode;
    }
}


static inline void FreeList(){
    for(int i = 0; i < amount; i++){ 
        list[i] = NULL;
    }
}


void DrawResult(){
    if(init == false){
        SetupList();
        text = LoadTexture("head.png");
        scrollIndex = 0;
        active = 0;
        focus = 0;
        init = true;
    }
    const char* name = GetUsername();
    int nameLen = RGUIMeasureTextWidth(name, 40);
    Vector2 nameLoc = {(Width() - nameLen) / 2, 30};
    Vector2 globLoc = {10 , 80};
    Vector2 textLoc = {(Width() - 100), 10};
    DrawTextureEx(text, textLoc, 0, 0.4, WHITE);
    RGUIDrawText(nameLoc, name, 30);
    GlobalInfo* gInfo = GetGlobalInfo();
    char gInfoBuffer[100];
    safe_sprintf(gInfoBuffer, 100, "Global Elo: %d (#%d)", gInfo->globalElo, gInfo->globalPos);
    RGUIDrawText(globLoc, gInfoBuffer, 30);
    if(state == 0){
        Rectangle exitButtonLoc = {10, 10, 90, 40};
        Rectangle resultListLoc = {10, 130, Width() - 20, Height() - 160};
        int button = RGUIDrawButton(exitButtonLoc, "Exit");
        
        int result = RGUIListView(resultListLoc, list, amount, &scrollIndex, &active, &focus);

        if(CheckCollisionPointRec(GetMousePosition(), resultListLoc) == true){
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && focus != -1){
                state = 1;
            }   
            DEBUG_INFO("%d - %d\n", active, focus);
        }
        if(button == 1){
            init = false;
            FreeList();
            SetSearchState(SSTATE_SEARCH);
            UnloadTexture(text);
        }

    } else {
        // takes a hit on perf, TODO: try to optimize (maybe don't do sprintf every frame? kind of stupid?)
        Rectangle exitButtonLoc = {10, 10, 90, 40};
        Rectangle resultListLoc = {10, 130, Width() - 20, Height() - 160};
        Vector2 resultLoc = {10, 90};
        int button = RGUIDrawButton(exitButtonLoc, "Go Back");
        if(focus < 0 || focus >= amount){
            focus = 0;
        }
        PlayerGMData* data = GetGameModeFromIndex(focus);
        char buffer[255];

        safe_sprintf(buffer, 255, 
            "%s\n\nRank: %s\nTotal Rating: %d\nWins: %d\nLosses: %d\nCurrent Streak: %d\nPosition: %d\n",
            data->gameMode, data->currentRank, data->totalRating, data->wins,
            data->losses, data->currentStreak, data->pMatchPlayed, data->position);
        
        RGUIReadBox(resultListLoc, buffer);

        if(button == 1){
            state = 0;
        }
    }
}