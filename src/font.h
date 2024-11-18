#ifndef XUI_font_h
#define XUI_font_h

#include "../include/xui.h"

#include <SDL2/SDL.h>

void initFont();
SDL_Texture *createText(const char *text, int ptsize, Color color);

#endif
