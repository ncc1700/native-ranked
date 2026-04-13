#include <tabs/search/loading.h>
#include <rgui.h>


static char* animation[] = {
    "///",
    "|||",
    "\\\\\\",
    "|||"
};

static int curAnim = 0;
static double curTime;
static bool init = false;



void DrawLoading(){
    if(init == false){
        curTime = GetTime();
        init = true;
    }
    char text[] = "Getting player info";
    Vector2 loadingTextPos = {(Width() - RGUIMeasureTextWidth(text, 30)) / 2, Height() / 2 - 45};
    Vector2 animationPos = {((float)Width() / 2) - (RGUIMeasureTextWidth(animation[curAnim], 40)) / 2, (Height() / 2)};
    RGUIDrawText(loadingTextPos, text, 30);
    RGUIDrawText(animationPos, animation[curAnim], 40);
   
    if((GetTime() - curTime) >= 0.3){
        if(curAnim >= 3){
            curAnim = 0;
        }
        else curAnim++;
        curTime = GetTime();
    }
}