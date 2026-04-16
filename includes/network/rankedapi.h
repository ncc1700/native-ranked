#ifndef RANKEDAPI_H_INCLUDED
#define RANKEDAPI_H_INCLUDED








#include <stdint.h>




typedef enum _RankedAPIError {
    RAPI_SUCCESS,
    RAPI_USERNAME_NOT_FOUND,
    RAPI_INVALID_RESPONSE
} RankedAPIError;

RankedAPIError FillRankedData(const char* uuid);







#endif