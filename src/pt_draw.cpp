/*
	Planar Tech 1 2D Draw Library
*/
#include "precmp.h"

#include "pt_main.h"
#include "pt_draw.h"

//Should have been a struct but w/e too late/lazy
color::color(){
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
	a = 1.0f;
}
color::color(float red, float green, float blue, float alpha){
	r = red;
	g = green;
	b = blue;
	a = alpha;
}
color::color(float red, float green, float blue){
	r = red;
	g = green;
	b = blue;
	a = 1.0f;
}
color::color(double red, double green, double blue, double alpha){
	r = (float)red;
	g = (float)green;
	b = (float)blue;
	a = (float)alpha;
}
color::color(double red, double green, double blue){
	r = (float)red;
	g = (float)green;
	b = (float)blue;
	a = 1.0f;
}

void setColor(color col){
	glColor4f(col.r,col.g,col.b,col.a);
}

//NON TEXTURED DRAW METHODS

void drawLine(int x1, int y1, int x2, int y2, color col){
	glBegin(GL_LINES);
		setColor(col);
		glVertex2i(x1,y1);
		glVertex2i(x2,y2);
	glEnd();
}

void drawRect(int x, int y, int w, int h, color col){
	glBegin(GL_QUADS);
		setColor(col);
		glVertex2i(x,y);
		glVertex2i(x+w,y);
		glVertex2i(x+w,y+h);
		glVertex2i(x,y+h);
	glEnd();
}

void drawOutlineRect(int x, int y, int w, int h, color col){
	glBegin(GL_LINES);
		setColor(col);
		glVertex2i(x,y);
		glVertex2i(x+w,y);
		glVertex2i(x+w,y);
		glVertex2i(x+w,y+h);
		glVertex2i(x+w,y+h);
		glVertex2i(x,y+h);
		glVertex2i(x,y+h);
		glVertex2i(x,y);
	glEnd();
}

void drawCircle(int x, int y, int radius, color col){
	drawTrigPoly(x,y,radius,180.0f,col);
}

void drawTrigPoly(int x, int y, int radius, float sides, color col){
	glBegin(GL_POLYGON);
		setColor(col);
		for(double i = 0; i < 2 * PI; i += (PI / sides)*2)
			glVertex2f(x+(float)sin(i)*radius,y+(float)cos(i)*radius);
	glEnd();
}

//TEXTURED DRAW METHODS

void drawTexRect(int x, int y, int w, int h, GLuint texture){
	drawTexRect(x,y,w,h,texture,color());
}
void drawTexRect(int x, int y, int w, int h, unsigned int texture, color col){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture);
	glBegin(GL_QUADS);
		setColor(col);
		glTexCoord2f(0,0);
		glVertex2i(x,y);
		glTexCoord2f(1,0);
		glVertex2i(x+w,y);
		glTexCoord2f(1,1);
		glVertex2i(x+w,y+h);
		glTexCoord2f(0,1);
		glVertex2i(x,y+h);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawTexRectPortion(int x, int y, int w, int h, float imgx, float imgy, float imgw, float imgh, unsigned int tex){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex);
	setColor(color(1.0f,1.0f,1.0f));
	glBegin(GL_QUADS);
		//setColor(col);
		glTexCoord2f(imgx,imgy);
		glVertex2i(x,y);
		glTexCoord2f(imgx+imgw,imgy);
		glVertex2i(x+w,y);
		glTexCoord2f(imgx+imgw,imgy+imgh);
		glVertex2i(x+w,y+h);
		glTexCoord2f(imgx,imgy+imgh);
		glVertex2i(x,y+h);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawTexRectRotated(int x, int y, int w, int h, GLuint texture, double angle){
	drawTexRectRotated(x,y,w,h,texture,angle,color());
}
void drawTexRectRotated(int x, int y, int w, int h, GLuint texture, double angle,color col){
	glPushMatrix();
	glTranslatef(x+w/2.0f,y+h/2.0f,0);
	glRotatef(angle,0,0,1);
	drawTexRect(-w/2,-h/2,w,h,texture,col);
	glPopMatrix();
}

//TEXT DRAW METHODS

void drawText(char* text, int x, int y, float sizex, float sizey, color col){
	glDisable(GL_BLEND);
	glDisable(GL_POINT_SMOOTH);

	glPushMatrix();
	glTranslatef( (float)x,(float)y+sizey, 0.0f );
	glScalef(sizex/100.0f,-sizey/100.0f,1.0f);
	setColor(col);
	for(unsigned int i = 0; i < strlen(text); i++){
		glutStrokeCharacter(GLUT_STROKE_ROMAN,text[i]);
	}
	glPopMatrix();

	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
}
void drawText(char* text, int x, int y, float size, color col){
	drawText(text,x,y,size,size,col);
}