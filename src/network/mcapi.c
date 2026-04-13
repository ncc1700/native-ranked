#include <network/mcapi.h>
#include <nranked.h>
#include <network/netabs.h>
#include <stdlib.h>
#include <yyjson/yyjson.h>

void TrimmedUUIDToUUID(const char* trimmed, char* normal, int length){
    if(length < 36){
        DEBUG_FAIL("buffer too small\n");
        return;
    }
    int trimmedLength = strlen(trimmed);
    int i = 0;
    int curTrimmed = 0;
    int curNormal = 0;
    while(curTrimmed < trimmedLength || curNormal < (length - 1)){
        if(i == 8 || i == 13 || i == 18 || i == 23){
            normal[curNormal] = '-';
            curNormal++;
        } else {
            normal[curNormal] = trimmed[curTrimmed];
            curNormal++;
            curTrimmed++;
        }
        i++;
    }
    normal[curNormal] = '\0';
}

MCAPIError GetUserUUID(const char* username, char* uuid, int length){
    const char urlBase[] = "https://api.mojang.com/users/profiles/minecraft/";
    char url[100]; 
    MCAPIError result = MCAPI_SUCCESS;
    safe_sprintf(url, 100, "%s/%s", urlBase, username);
    if(length < 32){
        DEBUG_FAIL("buffer too small\n");
        return MCAPI_BUFFER_TOO_SMALL;
    }
    char* body = NULL;
    int bodyLength = 0;
    int res = GetResult(url, &body, &bodyLength);
    if(res != 0 || body == NULL){
        DEBUG_FAIL("invalid response\n");
        result = MCAPI_INVALID_RESPONSE;
        goto EXIT1;
    }
    yyjson_doc* doc = yyjson_read(body, bodyLength, 0);
    if(doc == NULL){
        DEBUG_FAIL("not a json response");
        result = MCAPI_INVALID_RESPONSE;
        goto EXIT1;
    }
    yyjson_val* root = yyjson_doc_get_root(doc);
    if(root == NULL){
        DEBUG_FAIL("invalid or broken json response");
        result = MCAPI_INVALID_RESPONSE;
        goto EXIT2;
    }
    yyjson_val* uuidVal = yyjson_obj_get(root, "id");
    if(uuidVal == NULL){
        DEBUG_FAIL("couldn't find username\n");
        result = MCAPI_USERNAME_NOT_FOUND;
        goto EXIT2;
    }

    const char* str = yyjson_get_str(uuidVal);
    safe_sprintf(uuid, length, "%s", str);
EXIT2:
    yyjson_doc_free(doc);
EXIT1:
    free(body);
    return result;
}

 


// not really an mc api from mojang but idk where to put it
MCAPIError SaveUserHead(const char* username, const char* path){
    const char urlBase[] = "https://www.mc-heads.net/head/";
    char url[100]; 
    MCAPIError result = MCAPI_SUCCESS;
    safe_sprintf(url, 100, "%s/%s", urlBase, username);
    char* body = NULL;
    int bodyLength = 0;
    int res = GetResult(url, &body, &bodyLength);
    if(res != 0 || body == NULL){
        DEBUG_FAIL("invalid response\n");
        result = MCAPI_INVALID_RESPONSE;
        goto EXIT1;
    }
    FILE* fp = fopen(path, "wb");
    if(!fp){
        result = MCAPI_ALREADY_EXISTS;
        goto EXIT1;
    }
    fwrite(body, 1, bodyLength, fp);
    fclose(fp);
EXIT1:
    free(body);
    return result;
}