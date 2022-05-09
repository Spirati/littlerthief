#include "state.h"
#include "SDL_image.h"

static void keyHandle(SDL_Scancode key, GameState* state);

void digestName(GameState* state) {
    uint16_t nameBytes = SDL_ReadLE16(state->textState.script.file);
    if(nameBytes & SCRIPT_SKIP_MASK) {
        state->textState.wait = false;
    } else {
        state->textState.wait = true;
    }
    if(nameBytes & SCRIPT_FAST_MASK) {
        state->textState.textSpeed = 1;
    } else {
        state->textState.textSpeed = 2;
    }
    cursorWriteLine(
        &state->nameCursor, 
        state->textState.nameFont, 
        state->drawSurface, 
        state->textState.script.names[nameBytes & SCRIPT_NAME_MASK],
        MAX_NAME_WIDTH
    );
    state->nameCursor.x = 0;
    state->nameCursor.y = 0;
}

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
	output.window = SDL_CreateWindow("Little Thief", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 384, SDL_WINDOW_SHOWN);
	if(output.window == NULL) {
		printf(SDL_GetError());
        return output;
	}
    output.windowSurface = SDL_GetWindowSurface(output.window);
    output.drawSurface = SDL_CreateRGBSurface(0, 256, 512, 32, 0, 0, 0, 0);
    
    SDL_FillRect(
        output.drawSurface, 
        NULL, 
        SDL_MapRGB(output.drawSurface->format, 0, 0, 0)
    );

    SDL_BlitScaled(output.drawSurface, NULL, output.windowSurface, NULL);

    SDL_UpdateWindowSurface(output.window);

	SDL_ShowWindow(output.window);
    
    output.cursor = (TextCursor){ 0, 0, CURSOR_BASEX, CURSOR_BASEY, CURSOR_WIDTH };
    output.textState.textSpeed = 2;
    output.textState.wait = true;

    output.nameCursor = (TextCursor){ 
		0, 0, NAME_BASEX, NAME_BASEY, 256
	};


    return output;
}

void gameExit(GameState state) {
    SDL_DestroyWindow(state.window);
    SDL_RWclose(state.textState.script.file);
    SDL_FreeSurface(state.textState.textFont.atlasSurface);
    SDL_FreeSurface(state.drawSurface);
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

void consumeLine(GameState* state) {
    SDL_FillRect(
        state->drawSurface, 
        &(const SDL_Rect){ NAME_BASEX, NAME_BASEY, 256, CURSOR_HEIGHT},
        SDL_MapRGBA(state->drawSurface->format, 0, 0, 0, 0)
    );
    digestName(state);
    state->textState.read = readChar(state->textState.script);
    state->cursor.x = 0;
    state->cursor.y = 0;
    SDL_FillRect(
        state->drawSurface, 
        &(const SDL_Rect){ CURSOR_BASEX, CURSOR_BASEY, CURSOR_WIDTH + 8, CURSOR_HEIGHT},
        SDL_MapRGBA(state->drawSurface->format, 0, 0, 0, 0)
    );
}

static void keyHandle(SDL_Scancode key, GameState* state) {
    switch(key) {
        case SDL_SCANCODE_Z:
            if(state->textState.read == SCRIPT_EOL) {
                consumeLine(state);
            }
            break;
        case SDL_SCANCODE_X:
            while(state->textState.read > SCRIPT_EOF) {
                cursorWriteChar(&(state->cursor), state->textState.textFont, state->drawSurface, state->textState.read);
                state->textState.read = readChar(state->textState.script);
            }
    } 
}