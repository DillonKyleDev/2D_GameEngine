#include "TextureManager.h"
#include "Game.h"


SDL_Texture* TextureManager::LoadTexture(const char* filePath, SDL_Renderer* ren)
{
	// In order to load a texture we need a surface. 
	// But we need delete the surface afterward or we'll potentially get a memory leak
	SDL_Surface* tempSurface = IMG_Load(filePath);
	// Now we can turn that surface into a texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, tempSurface);
	// And then we free up that surface in memory because we don't need it anymore
	SDL_FreeSurface(tempSurface);

	return texture;
}