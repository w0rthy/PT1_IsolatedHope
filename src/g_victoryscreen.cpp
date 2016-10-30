#include "g_pipes.h"

namespace g_victoryscreen{

	void Init(){
		//LOG STATS
	}

	void Stop(){

	}

	void Draw(){
		drawText("You Won!!",GetWidth()/2,GetHeight()/2,32.0f,color());
	}

	void Key(char key, bool down, int x, int y){
		if(down)
			ChangeState(GAME_MENU);
	}
}