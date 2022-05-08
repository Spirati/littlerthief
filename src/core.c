#include "state.h"
#include "SDL_image.h"

#define CURSOR_WIDTH    224
#define CURSOR_HEIGHT   60
#define CURSOR_BASEX    16
#define CURSOR_BASEY    132

static void keyHandle(SDL_Scancode key, GameState* state);

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
    
    output.cursor = (TextCursor){ 0, 0, CURSOR_BASEX, CURSOR_BASEY, CURSOR_WIDTH };
    output.textState.textSpeed = 1;

    return output;
}

void gameExit(GameState state) {
    SDL_DestroyWindow(state.window);
    IMG_Quit();
	SDL_Quit();
}

bool eventLoop(GameState* state) {
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0) {
        switch(e.type) {
            case SDL_QUIT:
                return false;
            case SDL_KEYDOWN:
                keyHandle(e.key.keysym.scancode, state);
                break;
        }
        // if(e.type == SDL_QUIT) quit = true;
    }
    return true;
}

static void keyHandle(SDL_Scancode key, GameState* state) {
    switch(key) {
        case SDL_SCANCODE_Z:
            if(state->textState.read == SCRIPT_EOL) {
                state->textState.read = readChar(state->textState.script);
                state->cursor.x = 0;
                state->cursor.y = 0;
                SDL_FillRect(
                    state->windowSurface, 
                    &(const SDL_Rect){ CURSOR_BASEX, CURSOR_BASEY, CURSOR_WIDTH + 8, CURSOR_HEIGHT},
                    SDL_MapRGBA(state->windowSurface->format, 0, 0, 0, 0)
                );
            }
            break;
    } 
}