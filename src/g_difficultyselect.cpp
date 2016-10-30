#include "g_pipes.h"
#include "g_vars.h"

namespace g_difficultyselect {
	CollisionMap* colmap;
	Rectangle* diffnormal;
	Rectangle* diffhard;
	Rectangle* diffmad;
	Rectangle* diffinsane;
	Rectangle* diffnohope;
	Rectangle* backbtn;

	void Init(){
		colmap = new CollisionMap();

		diffnormal = new Rectangle(64,16,640-128,64,true);
		diffhard = new Rectangle(64,32+64,640-128,64,true);
		diffmad = new Rectangle(64,32+16+128,640-128,64,true);
		diffinsane = new Rectangle(64,64+128+64,640-128,64,true);
		diffnohope = new Rectangle(64,80+256,640-128,64,true);

		backbtn = new Rectangle(0,576,128,64,true);

		colmap->AddRect(*backbtn);
		colmap->AddRect(*diffnormal);
		colmap->AddRect(*diffhard);
		colmap->AddRect(*diffmad);
		colmap->AddRect(*diffinsane);
		colmap->AddRect(*diffnohope);
	}

	void Draw(){
		ui_drawfps();

		//NORMAL
		drawRectObj(*diffnormal,color(0,1.0f,0));
		drawTextScaled("Normal",256,16+14,33.0f,33.0f,color(0.0f,0,0));
		//HARD
		drawRectObj(*diffhard,color(0,0.33f,0));
		drawTextScaled("Hard",256+16,32+64+14,33.0f,33.0f,color(0.0f,0,0));
		//MAD
		drawRectObj(*diffmad,color(1.0f,0,0));
		drawTextScaled("Mad",256+24,48+128+14,33.0f,33.0f,color(0.0f,0,0));
		//INSANE
		drawRectObj(*diffinsane,color(0.25f,0,0));
		drawTextScaled("Insane",256,64+128+14+64,33.0f,33.0f,color(0.0f,0,0));
		//NO HOPE
		drawRectObj(*diffnohope,color(0.2f,0,0.2f));
		drawTextScaled("No Hope",256-32,80+128+14+128,33.0f,33.0f,color(0.0f,0,0));

		drawRectObj(*backbtn,color(0,0,1.0f));
		drawTextScaled("Back",16,600,30.0f,20.0f,color());
	}

	void Stop(){
		delete colmap;
		delete diffnormal;
		delete diffhard;
		delete diffmad;
		delete diffinsane;
		delete diffnohope;
		delete backbtn;
	}

	void MouseMotion(int x, int y, bool drag){

	}

	void MouseButton(int button, bool down, int x, int y){
		int tmp = colmap->CheckCol(x,y);

		if(!down)
			if(tmp!=-1){
				if(tmp==0){
					ChangeState(GAME_MODESELECT);
				}
				else{
					setVar("diff",(double)tmp);
					if(tmp == 1){ //NORMAL
						setVar("hpmul",1.0);
						setVar("dmgmul",1.0);
						setVar("spdmul",1.0);
					}else if(tmp == 2){ //HARD
						setVar("hpmul",1.25);
						setVar("dmgmul",1.25);
						setVar("spdmul",1.25);
					}else if(tmp == 3){ //MAD
						setVar("hpmul",1.5);
						setVar("dmgmul",1.5);
						setVar("spdmul",1.5);
					}else if(tmp == 4){ //INSANE
						setVar("hpmul",2.0);
						setVar("dmgmul",2.0);
						setVar("spdmul",2.0);
					}else { //NO HOPE
						setVar("hpmul",3.0);
						setVar("dmgmul",3.0);
						setVar("spdmul",3.0);
					}
					ChangeState(GAME_MODE_CLASSIC);
				}
			}
	}
}