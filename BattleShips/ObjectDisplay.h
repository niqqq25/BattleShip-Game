#pragma once
#include "Game.h"

class ObjectDisplay {

public:
	static SDL_Texture *texture(const char *pname);
	static void ImageDisplay(SDL_Texture* texture, SDL_Rect DestR);

private:
};

