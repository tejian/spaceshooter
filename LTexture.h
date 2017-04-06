#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>

using namespace std;
class LTexture{
	private:
		SDL_Texture * mTexture;
		int mWidth, mHeight;
	public:
		//initialize text
		LTexture();
		//deallocate texture
		void free();
		//set alpha
		void set_alpha(Uint8 alpha);
		//get width
		int get_width();
		//get height
		int get_height();
		//destructor
		~LTexture();

		//load image from path
		bool load_image(SDL_Renderer * rendertarget, const char * path);
		//create text texture
		bool write_text(SDL_Renderer * rendertarget, const char * a, SDL_Color color, TTF_Font * font);
		//render
		void draw(SDL_Renderer * rendertarget, int x, int y, SDL_Rect * clip = NULL);
};		
//---------------------------------------------------------------------------------
LTexture::LTexture(){
	mHeight = mWidth = 0;
	mTexture = NULL;
}

LTexture::~LTexture(){ SDL_DestroyTexture(mTexture); }

void LTexture::free(){ SDL_DestroyTexture(mTexture); }

void LTexture::set_alpha(Uint8 alpha){ SDL_SetTextureAlphaMod(mTexture, alpha); }

int LTexture::get_width(){ return mWidth; }

int LTexture::get_height(){ return mHeight; }

bool LTexture::load_image(SDL_Renderer * rendertarget, const char * path){
	//delete previous textures
	SDL_DestroyTexture(mTexture);
	
	SDL_Surface * temp = IMG_Load(path);
	if(temp == NULL){
		cout << "LTexture load_image error" << endl;
		return 0;
	}
	
	mTexture = SDL_CreateTextureFromSurface(rendertarget, temp);
	if(mTexture == NULL){
		cout << "LTexture load_image error" << endl;
		SDL_FreeSurface(temp);
		return 0;
	}
	
	SDL_FreeSurface(temp);
	SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);
	return 1;
}

bool LTexture::write_text(SDL_Renderer * rendertarget, const char * a, SDL_Color color, TTF_Font * font){
	//delete previous textures
	SDL_DestroyTexture(mTexture);
	
	SDL_Surface * temp = TTF_RenderText_Solid(font, a, color);
	if(temp == NULL){
		cout << "LTexture write_text error" << endl;
		return 0;
	}
	
	mTexture = SDL_CreateTextureFromSurface(rendertarget, temp);
	if(mTexture == NULL){
		cout << "LTexture write_text error" << endl;
		SDL_FreeSurface(temp);
		return 0;
	}
	
	SDL_FreeSurface(temp);
	SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);
	return 1;
}

void LTexture::draw(SDL_Renderer * rendertarget, int x, int y, SDL_Rect * clip){
	SDL_Rect temp = { x, y, mWidth, mHeight};
	
	if(clip != NULL){
		temp.w = clip -> w;
		temp.h = clip -> h;
	}
	SDL_RenderCopy(rendertarget, mTexture, clip, &temp);
}
#endif
