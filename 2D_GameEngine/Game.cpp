#include "Game.h"
#include "GameObject.h"



GameObject* player;
const char* playerFilePath = "assets/Alien_Robot.png";
GameObject* clipboardObject;
const char* clipboardFilePath = "assets/Clipboard.png";

SDL_Renderer* Game::renderer = nullptr;

// Game constructor
Game::Game()
{
	isRunning = false;
}

// Game destructor
Game::~Game()
{

}

// We made an init function to "start" the Game class
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	std::cout << "In init" << std::endl;

	int flags = 0;
	// If the fullscreen parameter in the call to init above is true,
	// make the flags == fullscreen to pass into SDL_CreateWindow()
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialized..." << std::endl;
		// Create window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		// Check window was created successfully
		if (window)
		{
			std::cout << "Window created..." << std::endl;
		}

		// Create the renderer
		renderer = SDL_CreateRenderer(window, -1, 0);
		// Check renderer was created successfully
		if (renderer)
		{
			// Set the render color (to white in this case)
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Window created..." << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	player = new GameObject(playerFilePath, 50, 50);
	clipboardObject = new GameObject(clipboardFilePath, 200, 200);
}

void Game::handleEvents()
{
	// Create an SDL_Event and Poll the event
	SDL_Event event;

	// While there are events in the que, SDL_PollEvent() will return 1
	// When there are no events left in the que, SDL_PollEvent() returns 0;
	// So while there are still events in the que, we poll them one at a time and check them
	while (SDL_PollEvent(&event))
	{
		// Check what type of event it is
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_MOUSEMOTION:
			std::cout << event.motion.x << " - " << event.motion.y << std::endl;
			break;
		default:
			break;
		}
	}
}

void Game::update()
{
	// Call the Update function of our gameObjects
	player->Update();
	clipboardObject->Update();
}

void Game::render()
{
	// Clear the renderer of what's already on it
	SDL_RenderClear(renderer);
	
	// Call the Render functions of gameObjects
	player->Render();
	clipboardObject->Render();

	// Add new stuff to the renderer
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	// Destroy the window and renderer and then quit on clean();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned..." << std::endl;
}

bool Game::running() { return isRunning; }
