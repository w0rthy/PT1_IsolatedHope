#pragma once

#include "pt_textures.h"

class color {
public:
	color::color();
	color::color(float r, float g, float b);
	color::color(double r, double g, double b);
	color::color(float r, float g, float b, float a);
	color::color(double r, double g, double b, double a);
	float r;
	float g;
	float b;
	float a;
};

unsigned int loadTexture(char* path);
unsigned int loadTexture(char* path, unsigned int index);

void drawLine(int x1, int y1, int x2, int y2, color col);

void drawRect(int x, int y, int w, int h, color col);

void drawOutlineRect(int x, int y, int w, int h, color col);

void drawCircle(int x, int y, int radius, color col);
void drawTrigPoly(int x, int y, int radius, float sides, color col);

void drawTexRect(int x, int y, int w, int h, unsigned int texture);
void drawTexRect(int x, int y, int w, int h, unsigned int texture, color col);
void drawTexRectPortion(int x, int y, int w, int h, float imgx, float imgy, float imgw, float imgh, unsigned int tex);
void drawTexRectRotated(int x, int y, int w, int h, unsigned int texture, double angle);
void drawTexRectRotated(int x, int y, int w, int h, unsigned int texture, double angle,color col);

void drawText(char* text, int x, int y, float sizex, float sizey, color col);
void drawText(char* text, int x, int y, float size, color col);