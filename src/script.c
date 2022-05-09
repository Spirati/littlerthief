#include "script.h"
#include "SDL.h"

ScriptFile loadScript(const char* scriptPath) {
    ScriptFile output;
    output.file = SDL_RWFromFile(scriptPath, "r");

    SDL_ReadLE32(output.file); // skip past header
    output.numNames = SDL_ReadLE16(output.file);
    for(int i = 0; i < output.numNames; i++) {
        uint16_t read = SDL_ReadLE16(output.file);
        int index = 0;
        while(read != 0x00) {
            output.names[i][index] = read;
            read = SDL_ReadLE16(output.file);
            index++;
        }
        for(int j = index; j < MAX_NAME_WIDTH; j++) output.names[i][j] = 1;
    }
    SDL_ReadLE32(output.file);

    return output;
}


int16_t readChar(ScriptFile script) {
    uint16_t character[1];
    int read = SDL_RWread(script.file, character, sizeof(uint16_t), 1);
    if(read == 0) return SCRIPT_EOF;
    if(character[0] == 0) return SCRIPT_EOL;
    return character[0];
}