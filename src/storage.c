#include <storage.h>
#include <string.h>
#include <nranked.h>

static char currentUserName[USERNAME_SIZE];
static PlayerGMData gmData[MAX_AMOUNT_OF_GAMEMODES];
static int amount = 0;
static GlobalInfo gInfo;






void ClearStorage(){
    safe_sprintf(currentUserName, USERNAME_SIZE, "");

    for(int i = 0; i < MAX_AMOUNT_OF_GAMEMODES; i++){
        safe_sprintf(gmData[i].currentRank, CURRENTRANK_STR_SIZE, "???");
        safe_sprintf(gmData[i].gameMode, GAMEMODE_STR_SIZE, "???");
        gmData[i].totalRating = 0;
        gmData[i].wins = 0;
        gmData[i].losses = 0;
        gmData[i].currentStreak = 0;
        gmData[i].pMatchPlayed = 0;
        gmData[i].position = 0;
        gmData[i].played = false;
    }
}


void SetUsername(const char* username){
    safe_sprintf(currentUserName, USERNAME_SIZE, "%s", username);
}

const char* GetUsername(){
    return (const char*)currentUserName;
}

void SetGameMode(int i, PlayerGMData* data){
    if(i >= MAX_AMOUNT_OF_GAMEMODES){
        return;
    }
    memcpy(&gmData[i], data, sizeof(PlayerGMData));
}

PlayerGMData* GetGameModeFromIndex(int i){
    if(i >= 9 || i < 0) return NULL;
    return &gmData[i];
}

void SetGlobalInfo(GlobalInfo* info){
    memcpy(&gInfo, info, sizeof(GlobalInfo));;
}

GlobalInfo* GetGlobalInfo(){
    return &gInfo;
}


void SetAmountFromSearch(int a){
    amount = a;
}

int GetAmountFromSearch(){
    return amount;
}