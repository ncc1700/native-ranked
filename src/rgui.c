#include <rgui.h>


#define RAYGUI_IMPLEMENTATION
#include <raylib/raygui.h>


int Width(){
    return GetScreenWidth();
}

int Height(){
    return GetScreenHeight();
}

// doesn't unload style, TODO: make a custom 
// unloadstyle function
void RGUIInit(const char* path){
    GuiLoadStyle(path);
    GuiSetStyle(LISTVIEW, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
    GuiSetStyle(LISTVIEW, TEXT_SIZE, 25);

    //GuiSetStyle(DEFAULT, TEXT_SIZE, 25);
    //GuiSetStyle(TEXTBOX, TEXT_SIZE, 5);
}

Color RGUIGetBackgroundColor(){
    return GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR));
}

Color RGUIGetTextColor(){
    return GetColor(GuiGetStyle(TEXT, TEXT_COLOR_NORMAL));
}

int RGUIDrawButton(Rectangle bounds, const char* text){
    return GuiButton(bounds, text);
}

int RGUITextBox(Rectangle bounds, char* text, int textLength, bool editMode){
    return GuiTextBox(bounds, text, textLength, editMode);  
}

int RGUIDrawText(Vector2 position, const char* text, int fontSize){
    Color color = GetColor(GuiGetStyle(TEXT, TEXT_COLOR_NORMAL));
    DrawTextEx(GuiGetFont(), text, position, fontSize, 1, color);
}

int RGUIMeasureTextWidth(const char *text, float fontSize){
    Vector2 size = MeasureTextEx(GuiGetFont(), text, fontSize, 1);  
    return size.x;
}

int RGUIMeasureTextHeight(const char *text, float fontSize){
    Vector2 size = MeasureTextEx(GuiGetFont(), text, fontSize, 1);  
    return size.y;
}

int RGUIListView(Rectangle bounds, char **text, int count, int *scrollIndex, int *active, int *focus){
    return GuiListViewEx(bounds, text, count, scrollIndex, active, focus); 
}

int RGUIReadBox(Rectangle bounds, const char *text){
    return GuiTextBoxMulti(bounds, (char*)text, strlen(text), false);  // very risky, need to find a better solution
}