#pragma once

struct RGB
{
	int r;
	int g;
	int b;
	int a;
};

struct Rect
{
	int width;
	int height;
	int xPos;
	int yPos;
	int zPos;
	RGB rgb;
};