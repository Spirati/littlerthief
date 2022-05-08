#pragma once
#include "SDL.h"

#define SCRIPT_EOF  -1
#define SCRIPT_EOL  -2

/**
 * @brief A struct representing a script file
 * 
 */
typedef struct ScriptFile {
    SDL_RWops *file;
    char* names[];
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