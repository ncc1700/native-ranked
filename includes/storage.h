#ifndef STORAGE_H_INCLUDED
#define STORAGE_H_INCLUDED








#include <stdint.h>



#define MAX_AMOUNT_OF_GAMEMODES 9

#define CURRENTRANK_STR_SIZE 30
#define GAMEMODE_STR_SIZE 20

typedef struct _PlayerGMData {
    char gameMode[GAMEMODE_STR_SIZE];
    char currentRank[CURRENTRANK_STR_SIZE];
    uint32_t totalRating;
    uint32_t wins;
    uint32_t losses;
    int32_t currentStreak;
    uint32_t pMatchPlayed;
    uint32_t position;
    bool played;
} PlayerGMData;

typedef struct _GlobalInfo {
    uint32_t globalElo;
    uint32_t globalPos;
} GlobalInfo;


void ClearStorage();
void SetUsername(const char* username);
const char* GetUsername();
void SetGameMode(int i, PlayerGMData* data);
PlayerGMData* GetGameModeFromIndex(int i);
void SetGlobalInfo(GlobalInfo* info);
GlobalInfo* GetGlobalInfo();
void SetAmountFromSearch(int a);
int GetAmountFromSearch();


#endif