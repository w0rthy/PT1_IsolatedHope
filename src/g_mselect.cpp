#include "g_pipes.h"

namespace g_mselect {
	CollisionMap* colmap;
	Rectangle* classicbtn;
	Rectangle* backbtn;

	void Init(){
		colmap = new CollisionMap();

		classicbtn = new Rectangle(192,64,256,256,true);
		backbtn = new Rectangle(0,576,128,64,true);

		colmap->AddRect(*classicbtn);
		colmap->AddRect(*backbtn);
	}

	void Draw(){
		ui_drawfps();

		drawRectObj(*classicbtn,color(0,0.75f,0.33f));
		drawTextScaled("Default",256,256,50.0f,50.0f,color());

		drawRectObj(*backbtn,color(0,0,1.0f));
		drawTextScaled("Back",16,600,30.0f,20.0f,color());
	}

	void Stop(){
		delete colmap;
		delete classicbtn;
		delete backbtn;
	}

	void MouseMotion(int x, int y, bool drag){

	}

	void MouseButton(int button, bool down, int x, int y){
		int tmp = colmap->CheckCol(x,y);

		if(!down)
			if(tmp==0)
				ChangeState(GAME_DIFF_SELECT);
			else if(tmp==1)
				ChangeState(GAME_MENU);
	}
}