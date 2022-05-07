#pragma once
#include "SDL.h"

/**
 * @brief A container for core SDL objects
 * 
 */
typedef struct GameState {
    SDL_Window *window;
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
