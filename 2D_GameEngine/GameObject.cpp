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
	sourceRectangle.h = 20;
	sourceRectangle.w = 20;
	sourceRectangle.x = 0;
	sourceRectangle.y = 0;
	destinationRectangle.x = xPos;
	destinationRectangle.y = yPos;
	destinationRectangle.w = sourceRectangle.w;
	destinationRectangle.h = sourceRectangle.h;
}

void GameObject::Render()
{
	//std::cout << xPos << "  " << yPos << std::endl;
	SDL_RenderCopy(Game::renderer, objectTexture, &sourceRectangle, &destinationRectangle);
}