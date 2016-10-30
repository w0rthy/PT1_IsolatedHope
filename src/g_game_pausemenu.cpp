#include "g_game_pausemenu.h"
#include "pt_draw.h"

namespace GAME_PAUSEMENU{
	void Draw(){
		drawText("Paused",200,50,40.0f,color());
		drawCircle(256,256,20,color());
	}
	void MouseButton(int button, bool down, int x, int y){

	}
}