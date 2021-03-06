#ifndef HERO_H
#define HERO_H
#include "baseobj.h"
#include "LTexture.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "particle.h"

#include <iostream>
using namespace std;

class Hero:public BaseObj	//SDL_Rect Box
{
	private:
		LTexture image;
		int xVel, yVel;
		SDL_Rect boundary;
		vector<Particle*> particles;
	public:
		void init(int x, int y, SDL_Renderer* rendertarget);
		~Hero();
		//movement
		void move_up();
		void move_down();
		void move_right();
		void move_left();
		
		void update();
		void draw(SDL_Renderer * rendertarget);
};

void Hero::init(int x, int y, SDL_Renderer* rendertarget){
	box.x = x;
	box.y = y;
	box.w = 50;
	box.h = 40;
	xVel = yVel = 10;
	//limit movement
	boundary.w = 670;
	boundary.h = 200;
	boundary.x = 15;
	boundary.y = 380;
	//sprite
	image.load_image(rendertarget, "img/Hero.png");
	//loading particles
	for(int i=0; i<400; ++i){
		particles.push_back(new Particle(	box.x+box.w/2 + rand() % 6 - 3,
											box.y+box.h + rand() % 6 - 3,
											rand() % 10 + (float)rand()/(float)RAND_MAX - 5,
											rand() % 10 + (float)rand()/(float)RAND_MAX + 10,
											100+ rand() % 200));
	}
	cout << particles.size() << endl;
}

Hero::~Hero(){
	image.free();
	free_particles(particles);
}

void Hero::move_up(){
	if(box.y > boundary.y) box.y -= yVel;
	else box.y = boundary.y; 
}
void Hero::move_down(){ 
	if(box.y + box.h < boundary.y + boundary.h) box.y += yVel;
	else box.y = boundary.y + boundary.h - box.h; 
}
void Hero::move_right(){ 
	if(box.x + box.w < boundary.x + boundary.w) box.x += xVel;
	else box.x = boundary.x + boundary.w - box.w;
}
void Hero::move_left(){ 
	if(box.x > boundary.x) box.x -= xVel;
	else box.x = boundary.x;
} 

void Hero::update(){
	update_particles(particles, box.x+box.w/2, box.y+box.h);
}

void Hero::draw(SDL_Renderer * rendertarget){
	//boundary
	SDL_SetRenderDrawColor(rendertarget, 255, 255, 0, 255);
	SDL_RenderDrawRect(rendertarget, & boundary);
	SDL_RenderDrawRect(rendertarget, &box);
	//draw particles
	draw_particles(particles, rendertarget);
	//sprite
	SDL_Rect temp = { 0, 0, box.w, box.h };
	image.draw(rendertarget, box.x, box.y, &temp);
}

#endif
