#include "g_pipes.h"

namespace g_menu {
	int* mdx = 0;
	int* mdy = 0;
	int* hovered = 0;
	float* dragged = 0;

	CollisionMap* colmap;

	void Init(){
		colmap = new CollisionMap();
		colmap->AddRect(Rectangle(192,288,256,64,true));
		colmap->AddRect(Rectangle(192,384,256,64,true));
		colmap->AddRect(Rectangle(192,480,256,64,true));

		mdx = new int(0);
		mdy = new int(0);
		hovered = new int(-1);
		dragged = new float(0);
	}

	void Draw(){
		ui_drawfps();

		//drawTexRect(0,0,1024,1024,getTextureID("input2.jpg")
		
		//TITLE BOX
		drawOutlineRect(
			ScaleToX(128),
			ScaleToY(64),
			ScaleToX(384),
			ScaleToY(128),
			color(0,0,0.33f+abs(sinf(CurTime())/3)));
		drawText(
			"Isolated Hope",
			ScaleToX(160),
			ScaleToY(96),
			ScaleToX(38.0f),
			ScaleToY(50.0f),
			color(1.0f,1.0f,1.0f,0.33f+abs(sinf(CurTime())/3)));

		//PLAY BUTTON
		drawRect(
			ScaleToX(192),
			ScaleToY(288),
			ScaleToX(256),
			ScaleToY(64),
			color((0.33f + *dragged) * (*hovered==0) ,0,0.33f+abs(sinf((CurTime()-0.25f))/3)));
		drawOutlineRect(
			ScaleToX(192),
			ScaleToY(288),
			ScaleToX(256),
			ScaleToY(64),
			color());
		drawText(
			"Play",
			ScaleToX(280),
			ScaleToY(304),
			ScaleToX(30.0f),
			ScaleToY(25.0f),
			color(0.0f,0.0f,0.0f));

		//OPTIONS BUTTON
		drawRect(
			ScaleToX(192),
			ScaleToY(384),
			ScaleToX(256),
			ScaleToY(64),
			color((0.33f + *dragged) * (*hovered==1),0,0.33f+abs(sinf((CurTime()-0.5f))/3)));
		drawOutlineRect(
			ScaleToX(192),
			ScaleToY(384),
			ScaleToX(256),
			ScaleToY(64),
			color());
		drawText(
			"Options",
			ScaleToX(256),
			ScaleToY(400),
			ScaleToX(30.0f),
			ScaleToY(25.0f),
			color(0.0f,0.0f,0.0f));

		//QUIT BUTTON
		drawRect(
			ScaleToX(192),
			ScaleToY(480),
			ScaleToX(256),
			ScaleToY(64),
			color((0.33f + *dragged) * (*hovered==2),0,0.33f+abs(sinf((CurTime()-0.75f))/3)));
		drawOutlineRect(
			ScaleToX(192),
			ScaleToY(480),
			ScaleToX(256),
			ScaleToY(64),
			color());
		drawText(
			"Quit",
			ScaleToX(280),
			ScaleToY(496),
			ScaleToX(30.0f),
			ScaleToY(25.0f),
			color(0.0f,0.0f,0.0f));

	}

	void Stop(){
		delete colmap;
		delete mdx;
		delete mdy;
		delete hovered;
		delete dragged;
	}

	void Key(char key, bool down, int x, int y){

	}

	void MouseMotion(int x, int y, bool drag){
		*hovered = colmap->CheckCol(x,y);
		*dragged = drag*0.25f;
	}

	void LocalMouseClick(int button, int x, int y){
		int tmp = colmap->CheckCol(x,y);
		//PLAY BUTTON
		if(tmp == 0)
			ChangeState(GAME_MODESELECT);
		//OPTIONS BUTTON
		else if(tmp == 1)
			ChangeState(GAME_OPTIONS);
		//QUIT BUTTON
		else if(tmp == 2)
			EXITPROGRAM();
	}

	void MouseButton(int button, bool down, int x, int y){
		*dragged = down*0.25f;
		if(down){
			*mdx = x;
			*mdy = y;
		}
		else{
			//if(*mdx==x && *mdy==y)
				LocalMouseClick(button,x,y);
		}
	}
}