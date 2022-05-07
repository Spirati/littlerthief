#include <stdio.h>
#include "littlethief.h"

int main(int argc, char *argv[]) {
	GameState state = gameInit();

	if(state.window == NULL) {
		printf(SDL_GetError());
		return 1;
	}

	FontFile orp = loadFont(TEXT_FONT_NAME, TEXT_FONT_BBX, TEXT_FONT_BBY, TEXT_FONT_WIDTH);
	if(orp.atlasSurface == NULL) {
		gameExit(state);
		return 1;
	}
	writeChar(orp, state.windowSurface, 0, 16, 16);
	SDL_UpdateWindowSurface(state.window);

	bool quit = false;
	while(!quit) {
		SDL_Event e;
		while(SDL_PollEvent(&e) != 0)
			if(e.type == SDL_QUIT) quit = true;
	}

	gameExit(state);

	return 0;
}