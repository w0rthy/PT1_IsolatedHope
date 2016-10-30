#include "g_pipes.h"

unsigned int enginesplash = 0;
double time = 0.0;

namespace g_intro{
	void Init(){
		enginesplash = loadTexture("splash.png");
		time = CurTime();
	}

	void Draw(){
		ui_drawfps();
		double et = ElapsedTime(time);

		drawTexRect(0,0,GetWidth(),GetHeight(),enginesplash,color(1.0f,1.0f,1.0f,(float)et/3.0f-0.1f));

		if(et >= 5.0)
			ChangeState(GAME_MENU);
	}

	void Stop(){
		unloadTexture(enginesplash);
	}
}