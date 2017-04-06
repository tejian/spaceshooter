#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

SDL_Texture * load_texture(const char * imgName, SDL_Renderer * rendertarget){
	SDL_Surface * temp = IMG_Load(imgName);
	SDL_Texture * image = SDL_CreateTextureFromSurface(rendertarget, temp);
	SDL_FreeSurface(temp);
	return image;
};

bool check_collision(const SDL_Rect& lhs, const SDL_Rect& rhs){
			if(lhs.x > rhs.x + rhs.w )	return 0;
			if(lhs.x + lhs.w < rhs.x) return 0;
			if(lhs.y > rhs.y + rhs.h )	return 0;
			if(lhs.y + lhs.h < rhs.y) return 0;
			return 1;
}

void load_from_file(vector<int>& a, const char* c){
	ifstream in(c);
	string b;
	if(in.is_open()){
		while(!in.eof()){
			in >> b;
			a.push_back(stoi(b));
		}
	}
	in.close();
}

#endif
