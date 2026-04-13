#ifndef RGUI_H_INCLUDED
#define RGUI_H_INCLUDED




#include <nranked.h>


int Width();
int Height();
void RGUIInit(const char* path);
Color RGUIGetBackgroundColor();
Color RGUIGetTextColor();
int RGUIDrawButton(Rectangle bounds, const char* text);
int RGUITextBox(Rectangle bounds, char* text, int textLength, bool editMode);
int RGUIDrawText(Vector2 position, const char* text, int fontSize);
int RGUIMeasureTextWidth(const char *text, float fontSize);
int RGUIMeasureTextHeight(const char *text, float fontSize);
int RGUIListView(Rectangle bounds, char **text, int count, int *scrollIndex, int *active, int *focus);


#endif