#include "state.h"

GameState gameInit(void) {

    GameState output;
    output.window = NULL;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf(SDL_GetError());
        return output;
	}
	output.window = SDL_CreateWindow("Little Thief", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 256, 192, SDL_WINDOW_SHOWN);
	if(output.window == NULL) {
		printf(SDL_GetError());
        return output;
	}
	SDL_ShowWindow(output.window);
    return output;
}

void gameExit(GameState state) {
    SDL_DestroyWindow(state.window);
	SDL_Quit();
}