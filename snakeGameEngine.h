#pragma once

#include "gameEngine.h"
#include "visualStructs.h"
#include <vector>

class SnakeEngine : public GameEngine {
public:
	SnakeEngine(Window &window);
	void snakeInit();

private:
	virtual void pollEvents(SDL_Event &event);
	void gameLogic();
	void drawSnake();
	void setHighScore();
	void getHighScore();
	void setAppleLoc();
	void gameOver();

	Rect createSnakePiece(int, int);

	enum DIRECTION {
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

private:
	DIRECTION _dir;
	bool _dirLock;
	bool _isRunning;
	int _score = 0;
	int _highScore = 0;
	int _oldHighScore;
	int _appleLocation[2];
	std::vector<Rect> _rects;
};