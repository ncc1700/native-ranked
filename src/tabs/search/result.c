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
    
    if(state == 0){
        GlobalInfo* gInfo = GetGlobalInfo();
        char gInfoBuffer[100];
        safe_sprintf(gInfoBuffer, 100, "Global Elo: %d (#%d)", gInfo->globalElo, gInfo->globalPos);
        RGUIDrawText(globLoc, gInfoBuffer, 30);
        Rectangle exitButtonLoc = {10, 10, 90, 40};
        Rectangle resultListLoc = {10, 130, Width() - 20, Height() - 160};
        int button = RGUIDrawButton(exitButtonLoc, "Exit");
        
        int result = RGUIListView(resultListLoc, list, amount, &scrollIndex, &active, &focus);

        if(CheckCollisionPointRec(GetMousePosition(), resultListLoc) == true){
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && focus != -1){
                state = 1;
            }   
        }
        if(button == 1){
            init = false;
            FreeList();
            SetSearchState(SSTATE_SEARCH);
            UnloadTexture(text);
        }

    } else {
        int tierScrollIndex = -1;
        int tierActive = -1;
        int tierFocus = -1;
        // takes a hit on perf, TODO: try to optimize (maybe don't do sprintf every frame? kind of stupid?)
        Rectangle exitButtonLoc = {10, 10, 90, 40};
        Rectangle resultListLoc = {10, 130, Width() - 20, Height() - 160};
        Vector2 resultLoc = {10, 90};
        int button = RGUIDrawButton(exitButtonLoc, "Go Back");
        if(focus < 0 || focus >= amount){
            focus = 0;
        }
        PlayerGMData* data = GetGameModeFromIndex(focus);
        char rank[50];
        if(data->currentRank != NULL) safe_sprintf(rank, 50, "Rank: %s", data->currentRank);
        else safe_sprintf(rank, 50, "Rank: UNSUPPORTED");

        char rating[50];
        if(data->totalRating >= 0) safe_sprintf(rating, 50, "Rating: %d", data->totalRating);
        else safe_sprintf(rating, 50, "Rating: UNSUPPORTED");

        char wins[25];
        if(data->wins >= 0) safe_sprintf(wins, 25, "Wins: %d", data->wins);
        else safe_sprintf(wins, 25, "Wins: UNSUPPORTED");

        char losses[25];
        if(data->losses >= 0) safe_sprintf(losses, 25, "Losses: %d", data->losses);
        else safe_sprintf(losses, 25, "Losses: UNSUPPORTED");

        char streak[50];
        if(data->currentStreak >= 0)  safe_sprintf(streak, 50, "Streak: %d", data->currentStreak);
        else safe_sprintf(streak, 50, "Streak: UNSUPPORTED");

        char position[50];
        if(data->position >= 0) safe_sprintf(position, 50, "Position: %d", data->position);
        else safe_sprintf(position, 50, "Position: UNSUPPORTED");
        
        char* resArr[6] = {rank, rating, wins, losses, streak, position};
        
        RGUIDrawText(globLoc, data->gameMode, 30);
        RGUIListView(resultListLoc, resArr, 6, &tierScrollIndex, &tierActive, &tierFocus);


        if(button == 1){
            state = 0;
        }
    }
}