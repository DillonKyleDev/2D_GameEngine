#include "Game.h"

Game* gameInstance = nullptr;

int main(int argc, char* argv[])
{
	// Setup the framerate variables
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;
	
	// Here we create a new Game class instance called gameInstance
	gameInstance = new Game();
	// We then call our init() function on our instance
	gameInstance->init("2D Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);

	// Now while that gameInstance is running
	while (gameInstance->running())
	{
		// Get current ticks since SDL was initialized
		frameStart = SDL_GetTicks();

		// Handle any user input
		gameInstance->handleEvents();

		// Update all objects (positions, etc)
		gameInstance->update();

		// Render changes to the display
		gameInstance->render();

		// See how many ticks there have been total in this frame
		// by subtracting how many ticks were at the start by how many
		// ticks there are after executing all the game loop functions this frame
		frameTime = SDL_GetTicks() - frameStart;

		// Then, if frameTime is less than our desired frame rate, wait
		//// until it's not
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	gameInstance->clean();

	return 0;
}