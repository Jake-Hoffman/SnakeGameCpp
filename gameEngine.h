#pragma once

#include "window.h"

class GameEngine : public Window {
public:
	GameEngine(Window &window);
	
protected:
	virtual void pollEvents(SDL_Event &event);
	void gameTiming();
	virtual void gameLogic();
	void gameLoop();
	void gameFrame();

protected: 
	int _fps;
	double _lastFrame;
};
