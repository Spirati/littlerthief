#include "state.h"
#include "SDL_image.h"

GameState gameInit(void) {

    GameState output;
    output.window = NULL;

    if(IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG != IMG_INIT_PNG) {
        printf(IMG_GetError());
        return output;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf(SDL_GetError());
        return output;
	}
	output.window = SDL_CreateWindow("Little Thief", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 256, 192, SDL_WINDOW_SHOWN);
	if(output.window == NULL) {
		printf(SDL_GetError());
        return output;
	}
    output.windowSurface = SDL_GetWindowSurface(output.window);
    
    SDL_FillRect(
        output.windowSurface, 
        NULL, 
        SDL_MapRGB(output.windowSurface->format, 0, 0, 0)
    );
    SDL_UpdateWindowSurface(output.window);

	SDL_ShowWindow(output.window);
    return output;
}

void gameExit(GameState state) {
    SDL_DestroyWindow(state.window);
    IMG_Quit();
	SDL_Quit();
}