#pragma once
#include "SDL.h"

/**
 * @brief A struct representing a script file
 * 
 */
typedef struct ScriptFile {
    SDL_RWops *file;
} ScriptFile;

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
 * @brief Load a monospaced font from the assets/font directory
 * 
 * @param fontName The name of the font face to load
 * @param bbx The width of the character bounding box
 * @param bby The height of the character bounding box
 * @param atlasWidth The number of characters in a row of the font atlas
 * @return FontFile 
 */
FontFile loadFont(const char* fontName, uint8_t bbx, uint8_t bby, uint16_t atlasWidth);