#ifndef MCAPI_H_INCLUDED
#define MCAPI_H_INCLUDED








#include <stdint.h>


typedef enum _MCAPIError {
    MCAPI_SUCCESS,
    MCAPI_USERNAME_NOT_FOUND,
    MCAPI_INVALID_RESPONSE,
    MCAPI_BUFFER_TOO_SMALL,
    MCAPI_ALREADY_EXISTS
} MCAPIError;


void TrimmedUUIDToUUID(const char* trimmed, char* normal, int length);
MCAPIError GetUserUUID(const char* username, char* uuid, int length);
MCAPIError SaveUserHead(const char* username, const char* path);










#endif