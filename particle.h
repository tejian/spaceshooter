#ifndef PARTICLES_H
#define PARTICLES_H

#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include <stdlib.h>	//srand, rand
#include <time.h> 	//time
using namespace std;
//--------------------------------------------------------------------
class Particle{
    private:
        float x, y, xVel, yVel;
        float endTime;    
    public:
        Particle(float x, float y, float xVel, float yVel,int life){
            this->x = x;
            this->y = y;
            this->xVel = xVel;
            this->yVel = yVel;
            endTime = SDL_GetTicks() + life;
        }
        void init(float x, float y, float xVel, float yVel,int life){
            this->x = x;
            this->y = y;
            this->xVel = xVel;
            this->yVel = yVel;
            endTime = SDL_GetTicks() + life;
        }
        void update(){
            x += xVel;
            y += yVel;
        }
        void draw(SDL_Renderer* rendertarget){
            SDL_SetRenderDrawColor(rendertarget, 255, 255, 255, 255);
            SDL_RenderDrawPoint(rendertarget, x, y);
        }
             
        bool is_dead(){
            return (SDL_GetTicks() > endTime);
        }
};
void draw_particles(vector<Particle*>& a, SDL_Renderer * rendertarget){
    for(int i = 0; i < a.size(); ++i) a[i]->draw(rendertarget);
}
void update_particles(vector<Particle*>& a, int x = 250, int y = 250){
    for(int i = 0; i < a.size(); ++i){
        a[i]->update();
        if(a[i]->is_dead()){
            a[i]->init(	x + rand() % 6 - 3,
						y + rand() % 6 - 3,
						rand() % 10 + (float)rand()/(float)RAND_MAX - 5,
						rand() % 10 + (float)rand()/(float)RAND_MAX + 10,
						100 + rand() % 200);
        }
    }
}
void free_particles(vector<Particle*>& a){
	for(int i = 0; i < a.size(); ++i) delete a[i];
} 

#endif
