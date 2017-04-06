#ifndef ENEMY_H
#define ENEMY_H

#include "baseobj.h"	//class BaseObj
#include "LTexture.h" 	//clsss LTexture(texture wrapper class)

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <iostream>
#include <vector>
using namespace std;

class Enemy:public BaseObj	//for SDL_Rect Box, check_collision nad basic get function
{
	private:
		LTexture image;
		float x, y;
		float yVel; 
		int healthPoint;
		SDL_Color color;
	public:
		Enemy(int x, int y, float yVel, int hp);
		void init(int x, int y, float yVel, int hp);
		~Enemy();
		void got_hit();
		bool is_dead();
		void update();
		void draw(SDL_Renderer * rendertarget);
};
//----------------------------------------------------------------------
Enemy::Enemy(int x, int y, float yVel, int hp){
	this->x = x;
	this->y = y;
	box.x = x;
	box.y = y;
	box.w = 40;
	box.h = 40;
	this->yVel = yVel;
	healthPoint = hp;
	if(healthPoint==1){
		color.r = 255;
		color.g = 0;
		color.b = 0;
		color.a = 255;
	}
	else if(healthPoint==2){
		color.r = 255;
		color.g = 255;
		color.b = 0;
		color.a = 255;
	}
}

void Enemy::init(int x, int y, float yVel, int hp){
	box.x = x;
	box.y = y;
	box.w = 40;
	box.h = 40;
	this->yVel = yVel;
	healthPoint = hp;
	if(healthPoint==1){
		color.r = 255;
		color.g = 0;
		color.b = 0;
		color.a = 255;
	}
	if(healthPoint==2){
		color.r = 255;
		color.g = 255;
		color.b = 0;
		color.a = 255;
	}
}

Enemy::~Enemy(){
	image.free();
}

void Enemy::got_hit() { --healthPoint; }

bool Enemy::is_dead() { return (healthPoint < 1); }

void Enemy::update(){
	y += yVel;
	box.y = y;
	
}

void Enemy::draw(SDL_Renderer * rendertarget){
	SDL_SetRenderDrawColor(rendertarget, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(rendertarget, &box);
}

//----------------some function for group of enemys------------------------
void draw_enemies(SDL_Renderer * rendertarget, vector<Enemy*>& a){
	for(int i = 0; i < a.size(); ++i) a[i]->draw(rendertarget);
}

void update_enemies(vector<Enemy*>& a){
	for(int i = 0; i < a.size(); ++i){ 
		a[i]->update();
	}
}
void free_enemies(vector<Enemy*> a){
	for(int i = 0; i < a.size(); ++i) delete a[i];
	a.clear();
}

#endif
