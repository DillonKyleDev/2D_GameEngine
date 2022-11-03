#pragma once
#ifndef Game_h
#define Game_h

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

// This is the Game classes .h file where we define all of it's members
class Game {
	
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	bool running();
	void render();
	void clean();

	// Static renderer so that we can just grab it from the Game:: class
	static SDL_Renderer* renderer;
	

private:
	bool isRunning;
	SDL_Window* window;
};

#endif /* Game_h */