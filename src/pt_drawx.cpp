/*
	Planar Tech 1 Extended Draw Library
*/
#include "pt_main.h"
#include "pt_drawx.h"

//draws a rectangle that is scaled to screen size
void drawRectScaled(int x, int y, int w, int h, color col){
	drawRect(ScaleToX(x),ScaleToY(y),ScaleToX(w),ScaleToY(h),col);
}

//draws a rectangle object
void drawRectObj(Rectangle rect, color col){
	if(rect.scaled)
		drawRectScaled(rect.x,rect.y,rect.w,rect.h,col);
	else
		drawRect(rect.x,rect.y,rect.w,rect.h,col);
}

//draw text that is scaled to screen size
void drawTextScaled(char* text, int x, int y, float w, float h, color col){
	drawText(text,ScaleToX(x),ScaleToY(y),ScaleToX(w),ScaleToY(h),col);
}