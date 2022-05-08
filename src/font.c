#include "font.h"
#include "SDL_image.h"
#include <stdio.h>

int writeChar(FontFile font, SDL_Surface *target, uint16_t index, int x, int y) {
    int charX = index % font.atlasWidth;
    int charY = index / font.atlasWidth;

    return SDL_BlitSurface(
        font.atlasSurface, &(const SDL_Rect){ font.bbx*charX, font.bby*charY, font.bbx, font.bby }, target, &(SDL_Rect){ x, y, 0, 0 } 
    );
}

FontFile loadFont(const char* fontPath, uint8_t bbx, uint8_t bby, uint16_t atlasWidth) {
    FontFile output;
    output.bbx = bbx;
    output.bby = bby;
    output.atlasWidth = atlasWidth;

    output.atlasSurface = IMG_Load(fontPath);
    return output;
}

int cursorWriteChar(TextCursor *cursor, FontFile font, SDL_Surface *target, uint16_t index) {
    if(cursor->x + font.bbx > cursor->lineWidth) {
        cursor->y += font.bby;
        cursor->x = 0;
    }
    int result = writeChar(font, target, index, cursor->baseX + cursor->x, cursor->baseY + cursor->y);
    cursor->x += font.bbx;
    return result;
}