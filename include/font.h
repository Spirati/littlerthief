#pragma once
#include "SDL.h"

#define TEXT_FONT_NAME  "assets/font/orpMedium.png"
#define TEXT_FONT_BBX   6
#define TEXT_FONT_BBY   12
#define TEXT_FONT_WIDTH 68

/**
 * @brief A struct representing a font as converted from BDF format
 * 
 */
typedef struct FontFile {
    uint8_t bbx;
    uint8_t bby;
    uint16_t atlasWidth;
    SDL_Surface *atlasSurface;
} FontFile;

/**
 * @brief Represents a cursor for text
 * 
 */
typedef struct TextCursor {
    int x;
    int y;
    int baseX;
    int baseY;
    int lineWidth;
} TextCursor;

/**
 * @brief Write a character to a surface using the index of the character in a font's atlas
 * 
 * @param font The font to use
 * @param target The surface to place the character
 * @param index The index of the character in the font's atlas
 * @param x The x location, in pixels, of the top left of the target location of the character
 * @param y The y location, in pixels, of the top left of the target location of the character
 * @return 0 on success, -1 on failure
 */
int writeChar(FontFile font, SDL_Surface *target, uint16_t index, int x, int y);

/**
 * @brief Write a character to a surface based on the position of a cursor
 * 
 * @param cursor The cursor to use for text positioning
 * @param font The font to use
 * @param target The surface to place the character
 * @param index The index of the character in the font's atlas
 * @return int 
 */
int cursorWriteChar(TextCursor *cursor, FontFile font, SDL_Surface *target, uint16_t index);

void cursorWriteLine(TextCursor *cursor, FontFile font, SDL_Surface *target, uint16_t *buffer, uint16_t count);

/**
 * @brief Load a monospaced font
 * 
 * @param fontName The path to the font atlas
 * @param bbx The width of the character bounding box
 * @param bby The height of the character bounding box
 * @param atlasWidth The number of characters in a row of the font atlas
 * @return FontFile 
 */
FontFile loadFont(const char* fontPath, uint8_t bbx, uint8_t bby, uint16_t atlasWidth);