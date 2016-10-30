#include "g_pipes.h"
#include "g_vars.h"

namespace g_postroundscreen{

	double starttime = 0.0;

	void Init(){
		starttime = CurTime();
		//LOG STATS
	}

	void Stop(){

	}

	void Draw(){
		char* text;
		if(getVar("win") == 1.00)
			text = "You Won!!";
		else
			text = "You Lost.";
		drawText(text,GetWidth()/2,GetHeight()/2,32.0f,color());
	}

	void Key(char key, bool down, int x, int y){
		if(down && CurTime() - starttime > 1.0)
			ChangeState(GAME_MENU);
	}

	void MouseButton(int button, bool down, int x, int y){
		Key(' ',down,x,y);
	}
}