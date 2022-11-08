#include "Game.h"
#include "GameObject.h"
#include "PerlinNoiseGenerator.h"

GameObject* player;
const char* playerFilePath;
GameObject* clipboardObject;
const char* clipboardFilePath;
SDL_Renderer* Game::renderer = nullptr;

// Perlin Noise
PerlinNoiseGenerator* noise1D;
PerlinNoiseGenerator* noise2D;

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
void Game::init(const char* title, int xpos, int ypos, bool fullscreen)
{
	playerFilePath = "assets/Alien_Robot.png";
	clipboardFilePath = "assets/Clipboard.png";

	// Set screen dimensions to our Game Instance so it can be used elsewhere

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
		window = SDL_CreateWindow(title, xpos, ypos, Game::width, Game::height, flags);
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
			std::cout << "Renderer created..." << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	player = new GameObject(playerFilePath, 50, 50);
	clipboardObject = new GameObject(clipboardFilePath, 200, 200);

	// Perlin noise business
	//noise1D = new PerlinNoiseGenerator();
	//noise1D->Draw1DNoise();
	noise2D = new PerlinNoiseGenerator();
	noise2D->Draw2DNoise();

	for (int i = 0; i < Game::width / noise2D->divider * Game::height / noise2D->divider; i++)
	{
		noise2D->objectArray2D[i]->Update();
	}
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

		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode)
			{
			case 89:
				std::cout << "Pressed 1" << std::endl;
				break;

			case 90:
				std::cout << "Pressed 2" << std::endl;
				break;

			case 91:
				std::cout << "Pressed 3" << std::endl;
				break;

			case 92:
				std::cout << "Pressed 4" << std::endl;
				noise2D->Draw2DNoise();

				for (int i = 0; i < Game::width / noise2D->divider * Game::height / noise2D->divider; i++)
				{
					noise2D->objectArray2D[i]->Update();
				}
				break;
			}
			break;

		case SDL_MOUSEMOTION:

			break;
		default:
			break;
		}
	}
}

void Game::update()
{
	// Call the Update function of our gameObjects
	//player->Update();
	//clipboardObject->Update();
	//for (int i = 0; i < 256; i++)
	//{
	//	noise1D->objectArray1D[i]->Update();
	//}
}

void Game::render()
{
	// Clear the renderer of what's already on it
	SDL_RenderClear(renderer);
	
	// Call the Render functions of gameObjects
	//player->Render();
	//clipboardObject->Render();

	//for (int i = 0; i < 256; i++)
	//{
	//	noise1D->objectArray1D[i]->Render();
	//}

	for (int i = 0; i < Game::width / noise2D->divider * Game::height / noise2D->divider; i++)
	{
		noise2D->objectArray2D[i]->Render();
	}



	// Add new stuff to the renderer
	SDL_RenderPresent(renderer);
	//std::cout << "Delaying 20000" << std::endl;
	//SDL_Delay(20000);
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
