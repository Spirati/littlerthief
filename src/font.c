#include "font.h"
#include "SDL_image.h"
#include <stdio.h>


int writeChar(FontFile font, SDL_Surface *target, uint16_t index, int x, int y) {
    int charX = index % font.atlasWidth;
    int charY = index / font.atlasWidth;

    return SDL_BlitSurface(
        font.atlasSurface, &(const SDL_Rect){ charX, charY, font.bbx, font.bby }, target, &(SDL_Rect){ x, y, 0, 0 } 
    );
}

FontFile loadFont(const char* fontName, uint8_t bbx, uint8_t bby, uint16_t atlasWidth) {
    FontFile output;
    output.bbx = bbx;
    output.bby = bby;
    output.atlasWidth = atlasWidth;

    char path[256];
    sprintf(path, "assets/font/%s.png", fontName);

    output.atlasSurface = IMG_Load(path);
    return output;
}