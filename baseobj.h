#ifndef BASEOBJ_H
#define BASEOBJ_H

#include "SDL2/SDL.h"
class BaseObj{
	public:
		int get_width() const { return box.h; } 
		int get_height() const { return box.w; }
		int get_x() const { return box.x; }
		int get_y() const { return box.y; }
		SDL_Rect get_rect(){ return box; };
	protected:
		SDL_Rect box;
		bool check_collision(const SDL_Rect& lhs, const SDL_Rect& rhs){
			if(lhs.x > rhs.x + rhs.w )	return 0;
			if(lhs.x + lhs.w < rhs.x) return 0;
			if(lhs.y > rhs.y + rhs.h )	return 0;
			if(lhs.y + lhs.h < rhs.y) return 0;
			return 1;
		}
};

#endif