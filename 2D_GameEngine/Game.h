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

	void init(const char* title, int xpos, int ypos, bool fullscreen);
	void handleEvents();
	void update();
	bool running();
	void render();
	void clean();

	static const int width = 1200;
	static const int height = 1200;

	// Static renderer so that we can just grab it from the Game:: class
	static SDL_Renderer* renderer;
	

private:
	bool isRunning;
	SDL_Window* window;
	int windowWidth;
	int windowHeight;
};

#endif /* Game_h */