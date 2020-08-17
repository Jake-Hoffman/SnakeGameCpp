#include "window.h"
#include "snakeGameEngine.h"
#include <iostream>
#include <vector>
#include "SDL.h"

int main(int argc, char *argv[])
{
	Window window("Snake", 800, 600);

	SnakeEngine snakeEngine(window);
	snakeEngine.snakeInit();

	return 0;
}

