#ifndef SEARCHSTATE_H_INCLUDED
#define SEARCHSTATE_H_INCLUDED





typedef enum _CurrentSearchState {
    SSTATE_SEARCH,
    SSTATE_LOADING,
    SSTATE_RESULT,
    SSTATE_ERROR
} CurrentSearchState;


void HandleSearch();
void SetSearchState(CurrentSearchState state);
CurrentSearchState GetSearchState();







#endif