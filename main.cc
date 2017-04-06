#include "globals.h"
#include "level1.h"

#include "SDL2/SDL.h"
#include <iostream>

using namespace std;
//---------------------------------------
void change_state(){
	if (gNextState != STATE_NULL){
		delete gCurrentState;
		switch(gNextState){
			case STATE_EXIT:
				break;
			case STATE_LEVEL1:
				gCurrentState = new Level1();
				break;
		}
		gStateID = gNextState;
		gNextState = STATE_NULL;
	}
}
//---------------------------------------
int main(int argc, char * args[]){
	SDL_Init(SDL_INIT_EVERYTHING);
	gWindow = SDL_CreateWindow("Space Invaders",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				WINDOW_WIDTH,
				WINDOW_HEIGHT,
				0);
	//loading first state
	gCurrentState = new Level1();
	gStateID = STATE_LEVEL1;
	//for fps
	Uint32 clkstart;
	//main loop
	while(gStateID != STATE_EXIT){
		clkstart = SDL_GetTicks();
		
		gCurrentState -> handle_events();
		
		gCurrentState -> update();
		
		gCurrentState -> draw();
		
		//change state if needed
		change_state();
		
		//maintain steady fps
		if( SDL_GetTicks() - clkstart < 1000 / FPS ){
            SDL_Delay( ( 1000 / FPS ) - ( SDL_GetTicks() - clkstart ) );
        }
	}
	//clean up
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}