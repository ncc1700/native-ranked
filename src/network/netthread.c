#include <network/netthread.h>
#include <nranked.h>
#include <stdlib.h>
#define ZTHREAD_IMPLEMENTATION
#include <z-lib/zthread.h>
#include <network/mcapi.h>
#include <network/rankedapi.h>
#include <tabs/search/searchstate.h>

static void SearchThreadEntry(void* args){
    char* username = (char*)args;
    printf("Starting Search....\n", username);
    // 32 + 4 just in case they decide to add dashes for some reason
    char uuid[33];
    MCAPIError result = GetUserUUID(username, uuid, 33);
    if(result != MCAPI_SUCCESS){
        DEBUG_FAIL("GetUserUUID returned result %d\n", result);
        goto EXIT;
    }
    DEBUG_PASS("UUID of %s is %s\n", username, uuid);

    result = SaveUserHead(username, "head.png");
    if(result != MCAPI_SUCCESS){
        DEBUG_FAIL("SaveUserHead returned result %d\n", result);
        goto EXIT;
    }
    char fullUuid[37] = "";
    TrimmedUUIDToUUID(uuid, fullUuid, 36);
    DEBUG_PASS("FULL: %s\n", fullUuid);
    RankedAPIError rresult = FillRankedData(fullUuid);
    if(rresult != RAPI_SUCCESS){
        DEBUG_FAIL("FillRankedData returned result %d\n", rresult);
        goto EXIT;
    }
    SetSearchState(SSTATE_RESULT);
EXIT:
    free(username);
}





int StartNetSearchThread(const char* username){
    char* userGlobal = (char*)calloc(16, sizeof(char));
    safe_sprintf(userGlobal, 16, "%s", username);
    zthread_t thrd;
    int res = zthread_create(&thrd, SearchThreadEntry, (void*)userGlobal);
    if(res != Z_OK){
        return -1;
    }
    zthread_detach(thrd);
    return 0;
}