#include <stdio.h>
#include "littlethief.h"
#include "SDL.h"

int main(void) {
	GameState state = gameInit();

	if(state.window == NULL) return 1;

	bool quit = false;
	while(!quit) {
		SDL_Event e;
		while(SDL_PollEvent(&e) != 0)
			if(e.type == SDL_QUIT) quit = true;
	}

	gameExit(state);

	return 0;
}