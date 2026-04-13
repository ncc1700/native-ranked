#include <tabs/search/result.h>
#include <tabs/search/searchstate.h>
#include <network/rankedapi.h>
#include <rgui.h>
#include <stdlib.h>
#include <nranked.h>
#include <string.h>

static char* list[AMOUNT_OF_GAMEMODES];
static bool init = false;
static Texture text;
static int amount = 0;
static int scrollIndex = 0;
static int active = 0;
static int focus = 0;

static inline void SetupList(){
    amount = GetAmountFromSearch();
    for(int i = 0; i < amount; i++){
        PlayerGMData* data = GetGameModeFromIndex(i);
        int gameModeLen = strlen(data->gameMode) + 1;
        int currentRank = strlen(data->currentRank) + 1;
        int length = gameModeLen + currentRank + 1;
        list[i] = calloc(length, sizeof(char));
        safe_sprintf(list[i], length, "%s - %s", data->gameMode, data->currentRank);
    }
}



static inline void FreeList(){
    for(int i = 0; i < amount; i++){ 
        free(list[i]);
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
    const char* name = GetUsernameFromSearch();
    int nameLen = RGUIMeasureTextWidth(name, 40);
    Vector2 nameLoc = {(Width() - nameLen) / 2, 30};
    Vector2 textLoc = {(Width() - (nameLen * 2)) / 2, 25};
    Rectangle exitButtonLoc = {10, 10, 90, 40};
    Rectangle resultListLoc = {10, 90, Width() - 20, Height() - 100};
    DrawTextureEx(text, textLoc, 0, 0.3, WHITE);
    RGUIDrawText(nameLoc, name, 30);
    int button = RGUIDrawButton(exitButtonLoc, "Exit");
    
    int result = RGUIListView(resultListLoc, list, 9, &scrollIndex, &active, &focus);
    
    if(button == 1){
        init = false;
        FreeList();
        SetSearchState(SSTATE_SEARCH);
    }
}