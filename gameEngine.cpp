#include "gameEngine.h"
#include <time.h>
#include <iostream>

GameEngine::GameEngine(Window &window) :
	Window(window)
{

}

void GameEngine::pollEvents(SDL_Event &event) 
{
}

void GameEngine::gameTiming() {
	while (((double)clock() - (double)_lastFrame) / ((double)CLOCKS_PER_SEC / (double)_fps) < 1.0) {}
	_lastFrame = clock();
}

void GameEngine::gameLogic() {

}

void GameEngine::gameLoop() {

	while (!isClosed()) {

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			pollEvents(event);
		}

		gameLogic();
		clear();
		gameTiming();
	}
}

void GameEngine::gameFrame() {
	gameLogic();
	clear();
}