#include <tabs/search/searchstate.h>
#include <tabs/search/search.h>
#include <tabs/search/loading.h>
#include <tabs/search/result.h>



// global state, boo
static CurrentSearchState curState = SSTATE_SEARCH;



void HandleSearch(){
    switch(curState){
        case SSTATE_SEARCH:
            DrawSearch();
            break;
        case SSTATE_LOADING:
            DrawLoading();
            break;
        case SSTATE_RESULT:
            DrawResult();
            break;
        case SSTATE_ERROR:
            break;
        default:
            curState = SSTATE_ERROR;
            break;
    }
}

void SetSearchState(CurrentSearchState state){
    curState = state;
}

CurrentSearchState GetSearchState(){
    return curState;
}