#pragma once
#ifndef GameObject_h
#define GameObject_h

#include "Game.h"


class GameObject
{

public:
	GameObject(const char* textureSheet, int xPosition, int yPosition);
	~GameObject();

	void Update();
	void Render();

private:
	int xPos;
	int yPos;
	SDL_Texture* objectTexture;
	SDL_Rect sourceRectangle, destinationRectangle;
};

#endif