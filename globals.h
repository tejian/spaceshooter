#ifndef GLOBALS_H
#define GLOBALS_H

#include "SDL2/SDL.h"
//----------gamestate enums--------------
enum GameStates{
	STATE_NULL,
	STATE_LEVEL1,
	STATE_EXIT
};
//---------basescene class-----------------
class GameState{
	public:
		virtual void handle_events() = 0;
		virtual void update() = 0;
		virtual void draw() = 0;
		virtual ~GameState(){};
};
//------------GLOBALS-----------------
const int WINDOW_WIDTH = 700;
const int WINDOW_HEIGHT = 600;
const int FPS = 30;

SDL_Window * gWindow = NULL;

GameState * gCurrentState = NULL;
int gStateID = STATE_NULL;
int gNextState = STATE_NULL;
#endif
