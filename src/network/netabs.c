#include <network/netabs.h>
#include <naett/naett.h>
#include <nranked.h>
#include <stdlib.h>






// FREE THE BODY POINTER!!!!!!!!
int GetResult(const char* url, char** body, int* returnedLength){
    int result = 0;
    naettReq* req = naettRequestWithOptions(url, 0, NULL);
    naettRes* res = naettMake(req);
    while(!naettComplete(res)){
        REST();
    }
    if(naettGetStatus(res) != 200){
        result = 1;
        goto CLEANUP1;
    }
    int bodyLength = 0;
    *body = (char*)naettGetBody(res, &bodyLength);
    DEBUG_PASS("got something! size: %d\n", bodyLength);
    *returnedLength = bodyLength;
CLEANUP1:
    naettFree(req);
    free(res);
    return result;
}