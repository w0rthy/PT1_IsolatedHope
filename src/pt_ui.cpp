/*
	Planar Tech 1 User Interface Utility Library
*/

#include "pt_main.h"
#include "pt_ui.h"
#include "pt_drawx.h"

//A set of rectangles used for detecting ui elements at a given point
CollisionMap::CollisionMap(){
	nxtindex = 0;
}

void CollisionMap::AddRect(Rectangle r){
	rects[nxtindex] = r;
	nxtindex++;
}

char CollisionMap::CheckCol(int x, int y){
	for(int i = 0; i < nxtindex; i++){
		Rectangle t = rects[i];
		if(t.scaled){
			if(x>ScaleToX(t.x) && x<ScaleToX(t.x+t.w) && y>ScaleToY(t.y) && y<ScaleToY(t.y+t.h))
				return i;
		}
		else
			if(x>t.x && x < t.x+t.w && y>t.y && y<t.y+t.h)
				return i;
	}
	return -1;
}

//draws fps on top left corner
void ui_drawfps(){
	if(fps==0) return;
	char* fpstxt = (char*)malloc(7+(int)log10(fps));
	sprintf_s(fpstxt,7+(int)log10(fps),"fps:%i",fps);
	drawText(fpstxt,0,0,10.0f,10.0f,color());
	free(fpstxt);
}