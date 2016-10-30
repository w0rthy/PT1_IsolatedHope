#pragma once

#include "pt_draw.h"

struct Rectangle {
	int x;
	int y;
	int w;
	int h;
	bool scaled;

	Rectangle(){
		x = 0;
		y = 0;
		w = 0;
		h = 0;
		scaled = false;
	}

	Rectangle(int x1, int y1, int w1, int h1){
		x = x1;
		y = y1;
		w = w1;
		h = h1;
		scaled = false;
	}
	Rectangle(int x1, int y1, int w1, int h1, bool scale){
		x = x1;
		y = y1;
		w = w1;
		h = h1;
		scaled = scale;
	}
};

void drawRectScaled(int x, int y, int w, int h, color col);
void drawRectObj(Rectangle rect, color col);

void drawTextScaled(char* text, int x, int y, float w, float h, color col);