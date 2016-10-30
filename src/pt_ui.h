#pragma once

#include "pt_drawx.h"

class CollisionMap {
public:
	CollisionMap();
	Rectangle rects[32];
	char CheckCol(int, int);
	void AddRect(Rectangle r);
private:
	char nxtindex;
};

void ui_drawfps();