#include "g_pipes.h"

namespace g_options {
	int mdx = 0;
	int mdy = 0;

	void Init(){

	}
	
	void Draw(){
		ui_drawfps();
		drawText("Options Menu",0,67,25.0f,color());
	}

	void Stop(){

	}

	void LocalMouseClick(int x, int y){
		ChangeState(GAME_MENU);
	}

	void MouseButton(int button, bool down, int x, int y){
		if(down){
			mdx = x;
			mdy = y;
		}
		else{
			if(mdx==x && mdy==y)
				LocalMouseClick(x,y);
		}
	}
}