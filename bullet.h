#ifndef BULLET_H
#define BULLET_H

#include "baseobj.h"
#include  "LTexture.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <vector>

class Bullet:public BaseObj{
	private:
		LTexture image;
		int xVel, yVel;
	public:
		Bullet(int x, int y, int xVel, int yVel, SDL_Renderer* rendertarget);
		void init(int x, int y, int xVel, int yVel,  SDL_Renderer* rendertarget);
		~Bullet();
		void update();
		void draw(SDL_Renderer * rendertarget);
};

Bullet::Bullet(int x, int y, int xVel, int yVel, SDL_Renderer* rendertarget){
	box.x = x;
	box.y = y;
	box.w = 10;
	box.h = 20;
	this -> xVel = xVel;
	this -> yVel = yVel;
	image.load_image(rendertarget, "img/hBullet.png");
}

void Bullet::init(int x, int y, int xVel, int yVel, SDL_Renderer* rendertarget){
	box.w = 10;
	box.h = 20;
	box.x = x - box.w / 2 ;
	box.y = y;
	this -> xVel = xVel;
	this -> yVel = yVel;
	image.load_image(rendertarget, "img/hBullet.png");
}

Bullet::~Bullet(){
	image.free();
}
void Bullet::update(){
	box.x += xVel;
	box.y += yVel;
}
void Bullet::draw(SDL_Renderer * rendertarget){
	SDL_RenderDrawRect(rendertarget, &box);	
	image.draw(rendertarget, box.x, box.y);
}
//---------some bullet functions-----------------------
void draw_bullets(SDL_Renderer * rendertarget, vector<Bullet*>& a){
	for(int i = 0; i < a.size(); ++i){
		a[i]->draw(rendertarget);
	}
}
void update_bullets(vector<Bullet*>& a){
	for(int i = 0; i < a.size(); ++i){
		a[i]->update();
	}
}
void free_bullets(vector<Bullet*>& a){
	for(int i = 0; i < a.size(); ++i) delete a[i];
	a.clear();
}
#endif
