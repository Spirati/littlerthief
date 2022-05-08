#include "script.h"
#include "SDL.h"

ScriptFile loadScript(const char* scriptPath) {
    ScriptFile output;
    output.file = SDL_RWFromFile(scriptPath, "r");
    return output;
}

int16_t readChar(ScriptFile script) {
    uint16_t character[1];
    int read = SDL_RWread(script.file, character, sizeof(uint16_t), 1);
    if(read == 0) return SCRIPT_EOF;
    if(character[0] == 0) return SCRIPT_EOL;
    return character[0];
}