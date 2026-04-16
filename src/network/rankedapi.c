// TODO
#include <network/rankedapi.h>
#include <nranked.h>
#include <network/netabs.h>
#include <stdlib.h>
#include <yyjson/yyjson.h>
#include <string.h>
#include <storage.h>
// a massive mess =(

RankedAPIError FillRankedData(const char* uuid){
    // clear the previous players data
    
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
    GlobalInfo gInfo = {0};
    yyjson_val* globalEloVal = yyjson_obj_get(root, "globalElo");
    if(globalEloVal == NULL) gInfo.globalElo = 0;
    else gInfo.globalElo = yyjson_get_int(globalEloVal);

    yyjson_val* globalPosVal = yyjson_obj_get(root, "globalPosition");
    if(globalPosVal == NULL) gInfo.globalPos = 0;
    else gInfo.globalPos = yyjson_get_int(globalPosVal);
    SetGlobalInfo(&gInfo);
    yyjson_val* rankingsVal = yyjson_obj_get(root, "perLadder");
    if(rankingsVal == NULL){
        DEBUG_FAIL("couldn't find rankings\n");
        result = RAPI_USERNAME_NOT_FOUND;
        goto EXIT2;
    }
    size_t max = 0;
    int idx = 0;
    yyjson_val* gmName;
    yyjson_val* gm;
    yyjson_obj_foreach(rankingsVal, idx, max, gmName, gm){
        if(idx >= MAX_AMOUNT_OF_GAMEMODES){
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
        if(curStreakVal == NULL) currentStreak = 0;
        else currentStreak = yyjson_get_int(curStreakVal);

        yyjson_val* pMatchPlayedVal = yyjson_obj_get(gm, "placementMatchesPlayed");
        int pMatchPlayed = 0;
        if(pMatchPlayedVal == NULL) pMatchPlayed = 0;
        else pMatchPlayed = yyjson_get_int(pMatchPlayedVal);

        yyjson_val* curRankVal = yyjson_obj_get(gm, "currentRank");
        char currentRank[30];
        if(curRankVal == NULL) safe_sprintf(currentRank, 30, "UNKNOWN");
        else safe_sprintf(currentRank, 30, "%s", yyjson_get_str(curRankVal));

        yyjson_val* posVal = yyjson_obj_get(gm, "position");
        int position = 0;
        if(posVal == NULL) position = 0;
        else position = yyjson_get_int(posVal);
        PlayerGMData gmData = {0};
        safe_sprintf(gmData.gameMode, GAMEMODE_STR_SIZE, "%s", name);
        safe_sprintf(gmData.currentRank, CURRENTRANK_STR_SIZE, "%s", currentRank);
        
        gmData.totalRating = totalRating;
        gmData.wins = wins;
        gmData.losses = losses;
        gmData.currentStreak = currentStreak;
        gmData.pMatchPlayed = pMatchPlayed;
        gmData.position = position;
        gmData.played = true;
        DEBUG_PASS("%s: (rank = %s, totalRating = %d)\n", gmData.gameMode, gmData.currentRank, gmData.totalRating);
        SetGameMode(idx, &gmData);
    }
    SetUsername(yyjson_get_str(nameVal));    
    SetAmountFromSearch(idx);
EXIT2:
    yyjson_doc_free(doc);
EXIT1:
    free(body);
    return result;
}

