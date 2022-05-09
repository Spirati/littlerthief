#pragma once
#include "SDL.h"

#define SCRIPT_EOF  -1
#define SCRIPT_EOL  -2

#define SCRIPT_NAME_MASK 0x0FFF
#define SCRIPT_SKIP_MASK (0b0001 << 12)
#define SCRIPT_FAST_MASK (0b0010 << 12)

#define MAX_NAME_WIDTH  42 // FIXME: don't like hardcode
#define MAX_NAMES       16

/**
 * @brief A struct representing a script file
 * 
 */
typedef struct ScriptFile {
    SDL_RWops *file;
    uint16_t numNames;
    uint16_t names[MAX_NAMES][MAX_NAME_WIDTH];
} ScriptFile;

/**
 * @brief Load a script file
 * 
 * @param scriptPath The path to the script file
 * @return ScriptFile
 */
ScriptFile loadScript(const char* scriptPath);

int16_t readChar(ScriptFile script);

uint16_t readLine(ScriptFile script);