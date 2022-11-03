#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int xPosition, int yPosition)
{
	objectTexture = TextureManager::LoadTexture(textureSheet, Game::renderer);
	xPos = xPosition;
	yPos = yPosition;
}


GameObject::~GameObject()
{

}


void GameObject::Update()
{
	sourceRectangle.h = 32;
	sourceRectangle.w = 32;
	sourceRectangle.x = 0;
	sourceRectangle.y = 0;
	destinationRectangle.x = xPos;
	destinationRectangle.y = yPos;
	destinationRectangle.w = sourceRectangle.w * 2;
	destinationRectangle.h = sourceRectangle.h * 2;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objectTexture, &sourceRectangle, &destinationRectangle);
}