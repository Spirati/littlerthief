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

	state.textState.script = loadScript("assets/script/hhhh_out");

	SDL_Surface* dialogueWait = IMG_Load("assets/font/dialogue_wait.png");

	SDL_UpdateWindowSurface(state.window);

	bool quit = false;
	uint32_t ticksA = 0;
	uint32_t ticksB = 0;
	uint32_t delta = 0;
	uint8_t parity = 0;
	state.textState.read = readChar(state.textState.script);

	while(eventLoop(&state)) {
		ticksA = SDL_GetTicks();
		
		delta = ticksA - ticksB;
		if(delta < FPS60_MS)
			SDL_Delay(FPS60_MS - delta);
		
		if(parity % state.textState.textSpeed == 0 && state.textState.read > SCRIPT_EOF) {
			cursorWriteChar(&state.cursor, orp, state.windowSurface, state.textState.read);
			state.textState.read = readChar(state.textState.script);
		} else if(state.textState.read == SCRIPT_EOL) {
			SDL_BlitSurface(dialogueWait, &(const SDL_Rect){ 8*(parity / DIALOGUE_WAIT_FRAMES), 0, 8, 8 }, state.windowSurface, &(SDL_Rect){ 240, 162, 0, 0 });
		}
		SDL_UpdateWindowSurface(state.window);

		parity = (parity + 1) % (3 * DIALOGUE_WAIT_FRAMES);
		ticksB = SDL_GetTicks64();
	}

	gameExit(state);

	return 0;
}