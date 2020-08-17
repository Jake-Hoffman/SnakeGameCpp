#include "snakeGameEngine.h"
#include <ctime>
#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"
#include <fstream>

SnakeEngine::SnakeEngine(Window &window) :
	GameEngine(window)
{
	srand(time(0));
	_fps = 20;
	_dirLock = false;
	_isRunning = false;
}

void SnakeEngine::snakeInit() {

	const int startingPieces = 4;

	for (int xx = 0; xx < startingPieces; xx++) {
		_rects.push_back(createSnakePiece(400 + 1, 200 + 10 * xx + 1));
	}
	_dir = UP;

	setAppleLoc();
	getHighScore();
	gameFrame();

	if (!_isRunning) {
		_isRunning = true;
		gameLoop();
	}
}

void SnakeEngine::setAppleLoc() {
	_appleLocation[0] = (rand() % _width) / 10 * 10 + 1;
	_appleLocation[1] = (rand() % _height) / 10 * 10 + 1;

	for (Rect r : _rects) {
		if (r.xPos == _appleLocation[0] && r.yPos == _appleLocation[1]) {
			setAppleLoc();
		}
	}
}

Rect SnakeEngine::createSnakePiece(int xPos, int yPos) {
	RGB rgb{ 255, 255, 255, 255 };
	return Rect{ 8, 8, xPos, yPos, 1, rgb };
}

void SnakeEngine::drawSnake() {
	for (Rect r : _rects) {
		drawRect(r);
	}
}

void SnakeEngine::setHighScore() {

	std::ofstream temp;
	temp.open("temp.txt");

  	if (temp.is_open()) {
		temp << std::to_string(_score);
		temp.close();
	} else {
		std::cout << "Failed to open temp file";
	}

	remove("highScore.txt");
	rename("temp.txt", "highScore.txt");
}

void SnakeEngine::getHighScore() {
	std::string score = "0";
	std::ifstream scoreFile;
	scoreFile.open("highScore.txt");

	if (scoreFile.is_open()) {
		getline(scoreFile, score);
	} else {
		std::cout << "Unable to open file" << std::endl;
	}

	_highScore = std::stoi(score);
}

void SnakeEngine::gameLogic() {
	int dx;
	int dy;
	Rect front = _rects.front();

	switch (_dir) {
	case UP:
		dx = 0;
		dy = -10;
		break;
	case DOWN:
		dx = 0;
		dy = 10;
		break;
	case LEFT:
		dx = -10;
		dy = 0;
		break;
	case RIGHT:
		dx = 10;
		dy = 0;
		break;
	default:
		dx = 0;
		dy = -10;
		break;
	}

	int newX, newY;
	newX = front.xPos + dx;
	newY = front.yPos + dy;

	bool gOver = false;

	for (Rect r : _rects) {
		if ((newX == r.xPos && newY == r.yPos)) {
			gOver = true;
		}
	}

	if (newX >= _width || newY >= _height || newX < 0 || newY < 0) {
		gOver = true;
	}

	if (newX == _appleLocation[0] && newY == _appleLocation[1]) {
		setAppleLoc();
		_score++;

	}
	else {
		_rects.erase(_rects.end() - 1);
	}

	if (!gOver) {
		_rects.insert(_rects.begin(), createSnakePiece(newX, newY));

		int highScore = (_score > _highScore) ? _score : _highScore;
		drawScore(_score, highScore);
		drawSnake();

		Rect r = createSnakePiece(_appleLocation[0], _appleLocation[1]);
		r.rgb.g = 0;
		r.rgb.b = 0;

		drawRect(r);
	}
	else {
		gameOver();
	}
	
	_dirLock = false;
}

void SnakeEngine::gameOver() {
	if (_score > _highScore) {
		setHighScore();
		getHighScore();
	}
	_rects.clear();
	_dirLock = false;
	_score = 0;
	snakeInit();
}

void SnakeEngine::pollEvents(SDL_Event &event) {
	switch (event.type) {
	
	case SDL_QUIT:
		_closed = true;
		break;

	case SDL_KEYDOWN:

		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			_closed = true;
			break;

		case SDLK_UP:
			if (_dir != DOWN && !_dirLock) {
				_dir = UP;
				_dirLock = true;
			}
			break;

		case SDLK_DOWN:
			if (_dir != UP && !_dirLock) {
				_dir = DOWN;
				_dirLock = true;
			}
			break;

		case SDLK_LEFT:
			if (_dir != RIGHT && !_dirLock) {
				_dir = LEFT;
				_dirLock = true;
			}
			break;

		case SDLK_RIGHT:
			if (_dir != LEFT && !_dirLock) {
				_dir = RIGHT;
				_dirLock = true;
			}
			break;
		}
		break;

	default:
		break;
	}
}