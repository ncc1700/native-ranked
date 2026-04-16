#include <messagebox.h>
#include <rgui.h>

#define MESSAGE_SIZE 50

typedef struct _MessageBoxData {
    char message[MESSAGE_SIZE];
    int width;
    int height;
    bool isAnswered;
} MessageBoxData;

#define MESSAGE_AMOUNT 10

static MessageBoxData data[MESSAGE_AMOUNT];
static int count = 0;

static inline int GetNextIndex(){
    for(int i = 0; i < count; i++){
        if(data[i].isAnswered == true) return i;
    }
    if(count >= MESSAGE_AMOUNT){
        return -1; // remove the latest message and reuse that. Yeah a bad idea i know
    }
    int result = count;
    count++;
    return result;
}

void SendAppMessage(const char* message){
    int index = GetNextIndex();
    if(index == -1) return;
    DEBUG_INFO("Message index = %d\n", index);
    safe_sprintf(data[index].message, MESSAGE_SIZE, "%s", message);
    data[index].width = RGUIMeasureTextWidth(message, 20);
    data[index].height = RGUIMeasureTextHeight(message, 20);
    data[index].isAnswered = false;
    DEBUG_INFO("%d\n", data[index].height);
}

void HandleMessages(){
    for(int i = 0; i < count; i++){
        if(data[i].isAnswered == true) continue;
        // gotta unwind this rat nest later down the road....
        // I #love doing UI stuff while half sleepy
        Rectangle back = {((Width() - 100) + (i * 4) - data[i].width) / 2, 
            ((Height() - 40) + (i * 4) - data[i].height) / 2 - 50,
            100 + data[i].width, 40 + data[i].height + 50};
        Rectangle front = {((Width() - 90) + (i * 4) - data[i].width) / 2, 
            ((Height() - 30) + (i * 4) - data[i].height) / 2 - 50, 
            90 + data[i].width, 30 + data[i].height + 50};
        Vector2 position = {(((Width() - 100) + (i * 4) - data[i].width) / 2) + 10, 
                            (((Height() - 60) + (i * 4) - data[i].height) / 2 - 50) + 20};
        Rectangle exitPos = {(front.x + front.width) - 90, (front.y + front.height) - 40, 80, 30};
        DrawRectangleRec(back, RGUIGetTextColor());  
        DrawRectangleRec(front, RGUIGetBackgroundColor());  
        RGUIDrawText(position, data[i].message, 20);
        int res = RGUIDrawButton(exitPos, "Ok");
        if(res == 1){
            data[i].isAnswered = true;
        }
    }
}