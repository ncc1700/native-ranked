#ifndef RANKEDAPI_H_INCLUDED
#define RANKEDAPI_H_INCLUDED








#include <stdint.h>


#define AMOUNT_OF_GAMEMODES 9
typedef enum _GameMode {
    SWORD,
    AXE,
    UHC,
    VANILLA,
    MACE,
    POT,
    NETHOP,
    SMP,
    DIAMONDSMP
} GameMode;

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

typedef enum _RankedAPIError {
    RAPI_SUCCESS,
    RAPI_USERNAME_NOT_FOUND,
    RAPI_INVALID_RESPONSE
} RankedAPIError;

typedef struct _GlobalInfo {
    uint32_t globalElo;
    uint32_t globalPos;
} GlobalInfo;

RankedAPIError FillRankedData(const char* uuid);
PlayerGMData* GetGameModeFromIndex(int i);
GlobalInfo* GetGlobalInfo();
const char* GetUsernameFromSearch();
int GetAmountFromSearch();






#endif