#include <stdio.h>
#include "littlethief.h"

int main(int argc, char *argv[]) {
	GameState state = gameInit();

	if(state.window == NULL) {
		printf(SDL_GetError());
		return 1;
	}


	state.textState.textFont = loadFont(TEXT_FONT_NAME, TEXT_FONT_BBX, TEXT_FONT_BBY, TEXT_FONT_WIDTH);
	if(state.textState.textFont.atlasSurface == NULL) {
		gameExit(state);
		return 1;
	}

	state.textState.nameFont = loadFont("assets/font/orpBold.png", 6, 12, 68);
	if(state.textState.nameFont.atlasSurface == NULL) {
		gameExit(state);
		return 1;
	}

	state.textState.script = loadScript("assets/script/hhhh_out_v2");

	SDL_Surface* dialogueWait = IMG_Load("assets/font/dialogue_wait.png");

	bool quit = false;
	uint32_t ticksA = 0;
	uint32_t ticksB = 0;
	uint32_t delta = 0;
	uint8_t parity = 0;

	digestName(&state);
	state.nameCursor.x = 0;
    state.nameCursor.y = 0;
	state.textState.read = readChar(state.textState.script);

	while(eventLoop(&state)) {
		ticksA = SDL_GetTicks();
		
		delta = ticksA - ticksB;
		if(delta < FPS60_MS)
			SDL_Delay(FPS60_MS - delta);
		
		if(parity % state.textState.textSpeed == 0 && state.textState.read > SCRIPT_EOF) {
			cursorWriteChar(&state.cursor, state.textState.textFont, state.drawSurface, state.textState.read);
			state.textState.read = readChar(state.textState.script);
		} else if(state.textState.read == SCRIPT_EOL && state.textState.wait) {
			SDL_BlitSurface(
				dialogueWait, 
				&(const SDL_Rect){ 8*(parity / DIALOGUE_WAIT_FRAMES), 0, 8, 8 }, 
				state.drawSurface, 
				&(SDL_Rect){ CURSOR_WIDTH + 16, CURSOR_BASEY + 30, 0, 0 }
			);
		} else if(state.textState.read == SCRIPT_EOL) {
			consumeLine(&state);
		}
    	SDL_BlitScaled(state.drawSurface, &(const SDL_Rect){0, 0, 256, 192}, state.windowSurface, &(SDL_Rect){0, 0, 512, 384});
		SDL_UpdateWindowSurface(state.window);

		parity = (parity + 1) % (3 * DIALOGUE_WAIT_FRAMES);
		ticksB = SDL_GetTicks64();
	}

	gameExit(state);

	return 0;
}


// FIXME: double check all headers for pragma once and function documentation
// TODO: design chunk-based script system
	// speaker index, post-line effects, etc.?
// TODO: add speaker functionality to python script conversion
// TODO: document tooling for script conversion