#pragma once
#include "SDL.h"
#include "font.h"
#include "script.h"
#include <stdbool.h>

#define FPS60_MS (uint32_t)(1000.0 * (1.0/60.0))
#define DIALOGUE_WAIT_FRAMES 8

typedef struct TextState {
    int16_t read;
    uint16_t textSpeed;
    ScriptFile script;
} TextState;

/**
 * @brief A container for core SDL objects
 * 
 */
typedef struct GameState {
    SDL_Window *window;
    SDL_Surface *windowSurface;
    TextCursor cursor;
    TextState textState;
} GameState;

/**
 * @brief Initialize the game state
 * @returns A struct containing various core SDL objects
 */
GameState gameInit(void);

/**
 * @brief Shut down SDL systems and prepare exit safely
 * 
 * @param state The struct returned from `gameInit`
 */
void gameExit(GameState state);

bool eventLoop(GameState* state);