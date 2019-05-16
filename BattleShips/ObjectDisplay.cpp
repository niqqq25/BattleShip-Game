#include "ObjectDisplay.h"

SDL_Texture * ObjectDisplay::texture(const char *pname)
{
	SDL_Surface* surface = IMG_Load(pname);

	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);
	return tex;
}

void ObjectDisplay::ImageDisplay(SDL_Texture* texture, SDL_Rect DestR)
{
	SDL_RenderCopy(Game::renderer, texture, NULL, &DestR);
}