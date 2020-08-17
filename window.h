#pragma once

#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "visualStructs.h"

class Window {
public:
	Window(const std::string &title, int width, int height);
	~Window();

	virtual void pollEvents(SDL_Event &event);
	void clear() const;

	inline bool isClosed() const { return _closed; }

	void drawRect(int w, int h, int x, int y, int r, int g, int b, int a);
	void drawRect(Rect r);
	void drawScore(int score, int highScore);

private:
	bool init();

private:
	std::string _title;
	SDL_Window *_windowSDL = nullptr;

protected:
	SDL_Renderer *_renderer = nullptr;
	TTF_Font *_font = nullptr;
	TTF_Font *_fontSmaller = nullptr;
	bool _closed = false;
	int _width = 800;
	int _height = 600;
};
