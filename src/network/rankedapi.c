// TODO
#include <network/rankedapi.h>
#include <nranked.h>
#include <network/netabs.h>
#include <stdlib.h>
#include <yyjson/yyjson.h>
#include <string.h>

// a massive mess =(


static char currentUserName[USERNAME_SIZE];
static PlayerGMData gmData[AMOUNT_OF_GAMEMODES];
static int idx = 0;



RankedAPIError FillRankedData(const char* uuid){
    // clear the previous players data off memory
    safe_sprintf(currentUserName, USERNAME_SIZE, "");

    for(int i = 0; i < AMOUNT_OF_GAMEMODES; i++){
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
    const char urlBase[] = "https://flowpvp.gg/api/ranked/";
    char url[100]; 
    RankedAPIError result = RAPI_SUCCESS;
    safe_sprintf(url, 100, "%s/%s", urlBase, uuid);
    char* body = NULL;
    int bodyLength = 0;
    int res = GetResult(url, &body, &bodyLength);
    if(res != 0 || body == NULL){
        DEBUG_FAIL("invalid response\n");
        result = RAPI_INVALID_RESPONSE;
        goto EXIT1;
    }
    yyjson_doc* doc = yyjson_read(body, bodyLength, 0);
    if(doc == NULL){
        DEBUG_FAIL("not a json response");
        result = RAPI_INVALID_RESPONSE;
        goto EXIT1;
    }
    yyjson_val* root = yyjson_doc_get_root(doc);
    if(root == NULL){
        DEBUG_FAIL("invalid or broken json response");
        result = RAPI_INVALID_RESPONSE;
        goto EXIT2;
    }
    yyjson_val* nameVal = yyjson_obj_get(root, "lastKnownName");
    if(nameVal == NULL){
        DEBUG_FAIL("couldn't find username\n");
        result = RAPI_USERNAME_NOT_FOUND;
        goto EXIT2;
    }
    yyjson_val* rankingsVal = yyjson_obj_get(root, "perLadder");
    if(rankingsVal == NULL){
        DEBUG_FAIL("couldn't find rankings\n");
        result = RAPI_USERNAME_NOT_FOUND;
        goto EXIT2;
    }
    size_t max;
    yyjson_val* gmName;
    yyjson_val* gm;
    yyjson_obj_foreach(rankingsVal, idx, max, gmName, gm){
        if(idx >= AMOUNT_OF_GAMEMODES){
            break;
        }
        if(gmName == NULL || gm == NULL){
            DEBUG_FAIL("either gmName or gm is NULL\n");
            result = RAPI_USERNAME_NOT_FOUND;
            goto EXIT2;
        }
        const char* name = yyjson_get_str(gmName);

        yyjson_val* totalRatingVal = yyjson_obj_get(gm, "totalRating");
        int totalRating = 0;
        if(totalRatingVal == NULL) totalRating = 0;
        else totalRating = yyjson_get_int(totalRatingVal);

        yyjson_val* winsVal = yyjson_obj_get(gm, "wins");
        int wins = 0;
        if(winsVal == NULL) wins = 0;
        else wins = yyjson_get_int(winsVal);

        yyjson_val* lossVal = yyjson_obj_get(gm, "losses");
        int losses = 0;
        if(lossVal == NULL) losses = 0;
        else losses = yyjson_get_int(lossVal);

        yyjson_val* curStreakVal = yyjson_obj_get(gm, "currentStreak");
        int currentStreak = 0;
        if(currentStreak == NULL) currentStreak = 0;
        else currentStreak = yyjson_get_int(curStreakVal);

        yyjson_val* pMatchPlayedVal = yyjson_obj_get(gm, "placementMatchesPlayed");
        int pMatchPlayed = 0;
        if(pMatchPlayedVal == NULL) pMatchPlayed = 0;
        else pMatchPlayed = yyjson_get_int(pMatchPlayedVal);

        yyjson_val* curRankVal = yyjson_obj_get(gm, "currentRank");
        if(curRankVal == NULL){

            continue;
        }
        const char* currentRank = yyjson_get_str(curRankVal);

        yyjson_val* posVal = yyjson_obj_get(gm, "position");
        int position = 0;
        if(posVal == NULL) position = 0;
        else position = yyjson_get_int(posVal);

        safe_sprintf(gmData[idx].gameMode, GAMEMODE_STR_SIZE, "%s", name);
        safe_sprintf(gmData[idx].currentRank, CURRENTRANK_STR_SIZE, "%s", currentRank);
        
        gmData[idx].totalRating = totalRating;
        gmData[idx].wins = wins;
        gmData[idx].losses = losses;
        gmData[idx].currentStreak = currentStreak;
        gmData[idx].pMatchPlayed = pMatchPlayed;
        gmData[idx].position = position;
        gmData[idx].played = true;
        DEBUG_PASS("%s: (rank = %s, totalRating = %d)\n", gmData[idx].gameMode, gmData[idx].currentRank, gmData[idx].totalRating);
    }
    safe_sprintf(currentUserName, USERNAME_SIZE, "%s", yyjson_get_str(nameVal));
    

EXIT2:
    yyjson_doc_free(doc);
EXIT1:
    free(body);
    return result;
}

PlayerGMData* GetGameModeFromIndex(int i){
    if(i >= 9 || i < 0) return NULL;
    return &gmData[i];
}

const char* GetUsernameFromSearch(){
    return (const char*)currentUserName;
}

int GetAmountFromSearch(){
    return idx;
}