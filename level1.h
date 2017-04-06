#ifndef LEVEL1_H
#define LEVEL1_H

#include "globals.h"		//for global vars and gamestate base class
#include "functions.h"		//for check_collision and load_texture
#include "enemy.h"     		//for enemy class
#include "hero.h"		//hero class
#include "bullet.h"		//bullet class
#include "LTexture.h"

#include "SDL2/SDL.h"	
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include <iostream>
#include <vector>
#include <stdlib.h> //rand
using namespace std;

class Level1 : public GameState{
	private:
		SDL_Renderer * rendertarget;
		//background
		SDL_Texture * bgImage[2];
		SDL_Rect bgRect;
		int bgTime;
		//enemy object
		vector<Enemy*> bug;
		//hero
		Hero player;
		bool direction[4];
		//bullets
		vector<Bullet*> heroBullet;
		//score
		int points;
		LTexture score;
		TTF_Font* font;
	public:
		Level1();
		~Level1();
		void handle_events();
		void update();
		void draw();
};

Level1::Level1(){
	TTF_Init();
	
	rendertarget = SDL_CreateRenderer(gWindow, 2, SDL_RENDERER_ACCELERATED);
	//background
	bgImage[0] = load_texture("img/sky1.png", rendertarget);
	bgImage[1] = load_texture("img/sky2.png", rendertarget);
	bgRect.x = 0;
	bgRect.y = 1200;
	bgRect.w = WINDOW_WIDTH;
	bgRect.h = WINDOW_HEIGHT;
	int bgTime = 0;
	//player
	player.init(320, 500, rendertarget);
	direction[0] = direction[1] = direction[2] = direction[3] = 0;
	//loading enemies
	vector<int> enemyInfo;
	load_from_file(enemyInfo, "level1-enemy.map");
	//enemyposition will be of 10 columns and 40 rows
	int z = 0;
	for(int i=0;i<10;++i){ 
		for(int y=0;y<35;++y){
			if(enemyInfo[z] != 0)bug.push_back(new Enemy(	i*(40 + 30) + 15 ,
															-y*(40 + 15) + 10,
															1.5, enemyInfo[z]));
			++z;
		}
	}
	//score
	points = 0;
	font = TTF_OpenFont("consola.ttf", 20);
	
}

Level1::~Level1(){
	cout << "destroyed elements of level1" << endl;
	free_enemies(bug);
	free_bullets(heroBullet);
	SDL_DestroyTexture(bgImage[0]);
	SDL_DestroyTexture(bgImage[1]);
	SDL_DestroyRenderer(rendertarget);
	score.free();
	TTF_CloseFont(font);
	TTF_Quit();
}

void Level1::handle_events(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT) gNextState = STATE_EXIT;
		else if(event.type == SDL_MOUSEBUTTONDOWN and event.button.button == SDL_BUTTON_LEFT){
			bug.push_back(new Enemy(event.button.x, event.button.y, 1.5, 2));			
		}
		if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.sym == SDLK_UP)	direction[0] = 1;
			if(event.key.keysym.sym == SDLK_DOWN)	direction[1] = 1;
			if(event.key.keysym.sym == SDLK_LEFT)	direction[2] = 1;
			if(event.key.keysym.sym == SDLK_RIGHT)	direction[3] = 1;
			if(event.key.keysym.sym == SDLK_SPACE)  heroBullet.push_back(new Bullet(player.get_x() + player.get_width() / 2,
																				player.get_y(),
																				0, 
																				-20,
																				rendertarget));
		}
		if(event.type == SDL_KEYUP){
			if(event.key.keysym.sym == SDLK_UP)		direction[0] = 0;
			if(event.key.keysym.sym == SDLK_DOWN)	direction[1] = 0;
			if(event.key.keysym.sym == SDLK_LEFT)	direction[2] = 0;
			if(event.key.keysym.sym == SDLK_RIGHT)	direction[3] = 0;
		}
	}
	
}
void bullet_enemy_coll(vector<Bullet*>& a, vector<Enemy*>& b, int& points); //do when bulets colllide enemies
void Level1::update(){
	//moving background infinitely
	bgRect.y -= 1.5; 
	if(bgRect.y == 0) bgRect.y = 1200;
	++bgTime;
	if(bgTime > 15) bgTime = 0;
	//for player movement
	if(direction[0]) player.move_up();
	if(direction[1]) player.move_down();
	if(direction[2]) player.move_left();
	if(direction[3]) player.move_right();
	player.update();
	//update enemy and herobullet
	bullet_enemy_coll(heroBullet, bug, points);
	//score
	string tScore = "score : " + to_string(points * 5);
	SDL_Color tColor = {255, 200, 100, 255};
	score.write_text(rendertarget, tScore.c_str(), tColor, font);
}

void Level1::draw(){
	SDL_RenderClear(rendertarget);
	//for bg animation
	if( bgTime < 8 ) SDL_RenderCopy(rendertarget, bgImage[0], &bgRect, NULL);
	else SDL_RenderCopy(rendertarget, bgImage[1], &bgRect, NULL);
	//draw objects
	draw_enemies(rendertarget, bug);
	draw_bullets(rendertarget, heroBullet);
	player.draw(rendertarget);
	score.draw(rendertarget, 20, 20);
	SDL_RenderPresent(rendertarget);
}
//-----------------some functions we gonna use ------------------------------
void bullet_enemy_coll(vector<Bullet*>& bullet, vector<Enemy*>& enemy, int& points){
	update_enemies(enemy);
	for(int i = 0; i < bullet.size(); ++i){
		bullet[i]->update();
		//check if its in view
		if(bullet[i]->get_y() + bullet[i]->get_height() < 0 or bullet[i]->get_y() > WINDOW_HEIGHT){
			delete bullet[i];
			bullet.erase(bullet.begin() + i);
			--i;
			break;
		}
		for (int j = 0; j < enemy.size(); ++j){
			//check contack
			if(check_collision(bullet[i]->get_rect(), enemy[j]->get_rect())){
				//erase bullet and postion index
				delete bullet[i];
				bullet.erase(bullet.begin() + i);
				--i;
				//reduce enemy hp and remove if dead
				enemy[j]->got_hit();
				if(enemy[j]->is_dead()) {
					delete enemy[j];
					enemy.erase(enemy.begin() + j);
					++points;
				}
				//break out of enemy loop
				break;
			}
		}
	}
}
#endif
