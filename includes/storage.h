#ifndef STORAGE_H_INCLUDED
#define STORAGE_H_INCLUDED








#include <stdint.h>



#define MAX_AMOUNT_OF_GAMEMODES 9

#define CURRENTRANK_STR_SIZE 30
#define GAMEMODE_STR_SIZE 20

// big struct
// yes also ik 64bits is a bit much but
// idk
typedef struct _PlayerGMData {
    char gameMode[GAMEMODE_STR_SIZE];
    char currentRank[CURRENTRANK_STR_SIZE];
    int64_t totalRating;
    int64_t wins;
    int64_t losses;
    int64_t currentStreak;
    int64_t pMatchPlayed;
    int64_t position;
    bool played;
} PlayerGMData;

typedef struct _GlobalInfo {
    int64_t globalElo;
    int64_t globalPos;
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