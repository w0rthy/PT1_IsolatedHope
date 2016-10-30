#include "pt_main.h"
#include "g_pipes.h"
#include "g_maps.h"
#include "g_vars.h"
#include "g_pathing.h"
#include "ent_main.h"
#include "ent_methods.h"
#include "ent_list.h"
#include "pt_error.h"
#include "ent_allies.h"
#include "ent_enemies.h"
#include "ent_spawn.h"
#include "ent_spawnclasses.h"
#include "g_assets.h"
#include "g_game_pausemenu.h"
#include "g_resources.h"

#include "pt_io.h"

namespace g_game_classic{
	bool paused = false;
	double pausedtime = 0.0;
	unsigned int leveltex;
	Entity* selectedUnit = nullptr;
	EntityTemplate* queuedbuilding = nullptr;
	SpawnClass* spawn = nullptr;
	double stime = 0.0;
	float scalex, scaley;
	float zoom = 1.0f;
	float zoomx = 1.0f;
	float zoomy = 1.0f;
	float maxzoom = 0.1f;
	double rpanx = 0.0f, rpany = 0.0f;
	int panx = 0, pany = 0;

	int TMP;
	int TMPX,TMPY;
	int TMPNUM = 0;
	int ppath = 0;

	void Init(){
		//LOAD MAP
		map = LoadMap("map.txt");
		setPathingMapData();
		SetUpLists();
		constructEntLists(map);
		ENTS_ALLIES::ConstructTemplates();
		ENTS_ENEMIES::ConstructTemplates();
		SPAWNCLASSES::SetUpSpawnClasses();
		//IDK
		leveltex = loadTexture(map->imgPath);
		spawn = &SPAWNCLASSES::testclass;

		new Entity(&ENTS_ALLIES::builder,map->zones[1].x+8,map->zones[1].y+4);
		
		stime = CurTime();
		//printf("name %s\n",ent_list->node->val->name);

		//INIT VARIABLES
		resource1 = 0;

		setVar("startTime",CurTime());

		//DEBUG ALLY STUFF
		for(int i = 0; i < 10; i++)
			GAME_ASSETS::selectedBuildings[i] = nullptr;
		GAME_ASSETS::selectedBuildings[0] = &ENTS_ALLIES::arrowTower1;
		GAME_ASSETS::selectedBuildings[1] = &ENTS_ALLIES::basicWall1;
	}

	bool Think(){
		//zoom -= ScaleTime(0.2f);
		zoomx = zoom;
		zoomy = zoom;
		if(GetWidth() < GetHeight()){
			zoomx = zoom*((float)GetWidth()/GetHeight());
		}else
			zoomy = zoom*((float)GetHeight()/GetWidth());

		scalex = (float)GetWidth()/(map->width*zoomx);
		scaley = (float)GetHeight()/(map->height*zoomy);
		panx = rpanx*GetWidth()/zoomx;
		pany = rpany*GetHeight()/zoomy;

		//SPAWN
		spawn->Spawn();
		
		//CHECK WIN
		if(spawn->done){
			linkedEnt* le = ent_list->node;
			while(le != nullptr){
				if(le->val->enemy)
					break;
				le = le->nxt;
			}
			//WON
			if(le == nullptr){
				setVar("win",1.0);
				ChangeState(GAME_POSTROUNDSCREEN);
				return false;
			}
		}

		//CHECK LOSS
		linkedEnt* le = ent_list->node;
		while(le != nullptr){
			if(!le->val->enemy)
				break;
			le = le->nxt;
		}if(le == nullptr){
			setVar("win",0.0);
			ChangeState(GAME_POSTROUNDSCREEN);
			return false;
		}

		//ENT Thinks
		le = ent_list->node;
		while(le != nullptr){
			le->val->Think();
			le = le->nxt;
		}
		/*float max = 1.0f-zoom;
		float rt = 0.002f;*/

		//if(GetKey('w'))
		//	rpany = clamp(rpany-rt,0.0f,max);
		//if(GetKey('a'))
		//	rpanx = clamp(rpanx-rt,0.0f,max);
		//if(GetKey('d'))
		//	rpanx = clamp(rpanx+rt,0.0f,max);
		//if(GetKey('s'))
		//	rpany = clamp(rpany+rt,0.0f,max);

		return true;
	}

	void Draw(){

		if(paused){
			GAME_PAUSEMENU::Draw();
			return;
		}
		//Think
		if(!Think())
			return;

		//Draw Map
		//drawTexRect(0,0,GetWidth(),GetHeight(),leveltex);
		drawTexRectPortion(0,0,GetWidth(),GetHeight(),rpanx,rpany,zoomx,zoomy,leveltex);

		//
		for(int i = 0; i < map->numZones; i++){
			Zone* z = &map->zones[i];
			drawRect(ScaleToCust(z->x,scalex)-panx,ScaleToCust(z->y,scaley)-pany,ScaleToCust(z->w,scalex),ScaleToCust(z->h,scaley),color(1.0f,0,0));
		}

		//Draw Ents
		bool selectedEntAlive = false;
		linkedEnt* entNode = ent_list->node;
		while(entNode != nullptr){
			Entity* ent = entNode->val;
			if(ent == selectedUnit){
				selectedEntAlive = true;
				entNode = entNode->nxt;
				continue;
			}
			float rat = (float)sqrt(2)/2.0f;
			if(ent->x*scalex - ent->w*scalex*rat < panx + GetWidth() && ent->x*scalex + ent->w*scalex*rat > panx && ent->y*scaley - ent->h*scaley*rat < pany + GetHeight() && ent->y*scaley + ent->h*scaley*rat > pany)
				ent->Draw(scalex, scaley, panx, pany);
			entNode = entNode->nxt;
		}

		//if(ent_list->node != nullptr){
		//	ent_list->node->val->Think();
		//	ent_list->node->val->Draw(scalex, scaley, panx, pany);
		//}

		//if(ent_list->node->val == selectedUnit)
		//	selectedEntAlive = true;

		//Draw Constructing building
		if(queuedbuilding != nullptr){
			//BUILDABLE PLACE???
			color col = color(0.0f,1.0f,0.0f,1.0f);
			int xp = (int)(mousex*(map->width/(float)GetWidth()*zoomx)/16.0f+1)*16-(int)(rpanx*map->width)%16+rpanx*map->width;
			int yp = (int)(mousey*(map->height/(float)GetHeight()*zoomy)/16.0f+1)*16-(int)(rpany*map->height)%16+rpany*map->height;
			if(pointInBounds(xp-queuedbuilding->w/2,yp-queuedbuilding->h/2) && pointInBounds(xp+queuedbuilding->w/2,yp+queuedbuilding->h/2) && pointInBounds(xp-queuedbuilding->w/2,yp+queuedbuilding->h/2) && pointInBounds(xp+queuedbuilding->w/2,yp-queuedbuilding->h/2)){
				int z = ZoneIndex(pointCurZone(xp,yp));
				if(z >= 0){
					linkedEnt* le = ent_list->node;
					while(le != nullptr){
						float dis = dist(xp,yp,le->val->x,le->val->y);
						if(le->val->speed == 0.0f && dis<(queuedbuilding->w+queuedbuilding->h)/4.0f + (le->val->w+le->val->h)/4.0f){
							col = color(1.0f,0.0f,0.0f,1.0f);
						}
						le = le->nxt;
					}
				}else{col = color(1.0f,0.0f,0.0f,1.0f);}
			}else{col = color(1.0f,0.0f,0.0f,1.0f);}

			int rx = (int)(mousex*(map->width/(float)GetWidth()*zoomx)/16.0f)*16-(int)(rpanx*map->width)%16;
			int ry = (int)(mousey*(map->height/(float)GetHeight()*zoomy)/16.0f)*16-(int)(rpany*map->height)%16;
			drawTexRect(ScaleToCust(rx,scalex),
				ScaleToCust(ry,scaley),
				ScaleToCust(queuedbuilding->w,scalex),
				ScaleToCust(queuedbuilding->h,scaley),
				queuedbuilding->tex.base,
				col);
		}

		//Draw selected unit and info
		if(selectedEntAlive == false)
			selectedUnit = nullptr;

		if(selectedUnit != nullptr){
			//SELECTION CIRCLE
			color ccolor = selectedUnit->enemy ? color(1.0f,0,0,0.75f) : color(0,1.0f,0,0.75f);
			drawCircle((int)(selectedUnit->x*scalex)-panx,(int)(selectedUnit->y*scaley)-pany,(int)((float)selectedUnit->w*scalex*0.75f),ccolor);
			//UNIT
			selectedUnit->Draw(scalex,scaley,panx,pany);
			//BACK
			int w = GetWidth()/6*2;
			drawRect(w-2,0,w+4,GetHeight()/40+22,color(0.0f,0.0f,0.0f));

			color infocolor = selectedUnit->enemy ? color(1.0f,0,0,1.0f) : color(0,1.0f,0,1.0f);
			//NAME
			drawText(selectedUnit->name,GetWidth()/2-strlen(selectedUnit->name)*5,0,15.0f,infocolor);
			//HEALTHBAR
			drawRect(w,20,(int)(w*(selectedUnit->hp/selectedUnit->hpmax)),GetHeight()/40,infocolor);
		}
		
		//Draw UI
		int amt = GetWidth()/20;
		int padding = 5;
		drawRect(0,GetHeight()-amt-padding*2,(amt+padding)*10,amt+padding*2,color(0.33f,0.33f,0.33f,1.0f));
		for(int i = 0; i < 10; i++){
			EntityTemplate* temp = GAME_ASSETS::selectedBuildings[i];
			if(temp == nullptr)
				continue;
			drawTexRect((amt+padding)*i,GetHeight()-amt-padding,amt,amt,temp->tex.base,temp->col);
		}

		//BUILDING TOOLTIP
		if(mousey >= GetHeight()-GetWidth()/20-padding*2 && mousex <= GetWidth()/2+padding*10 && mousex >= 0){
			EntityTemplate* temp = GAME_ASSETS::selectedBuildings[mousex/(GetWidth()/20+padding)];
			if(temp != nullptr){
				int tt = strlen(temp->tooltip)*7;
				int nl = strlen(temp->name)*10;
				int w = max(tt,nl);
				drawRect(mousex,mousey-40,w,40,color(0.0f,0.0f,0.0f,0.67f));
				drawText(temp->name,mousex,mousey-35,12.0f,color());
				drawText(temp->tooltip,mousex,mousey-15,10.0f,color());
				return;
			}
		}

		amt = GetWidth()/10;
		//UPGRADE TOOLTIP
		if(selectedEntAlive && selectedUnit != nullptr && selectedUnit->active && selectedUnit->upgradeEnt != nullptr){
			drawTexRect(GetWidth()-amt,GetHeight()-amt,amt,amt,selectedUnit->upgradeEnt->tex.base,selectedUnit->upgradeEnt->col);
			if(mousey >= GetHeight()-amt && mousex >= GetWidth()-amt){
				EntityTemplate* temp = selectedUnit->upgradeEnt;
				int tt = strlen(temp->tooltip)*7;
				int nl = strlen(temp->name)*10;
				int w = max(tt,nl);
				drawRect(mousex-w,mousey-40,w,40,color(0.0f,0.0f,0.0f,0.67f));
				drawText(temp->name,mousex-w,mousey-35,12.0f,color());
				drawText(temp->tooltip,mousex-w,mousey-15,10.0f,color());
			}
		}

		//Draw FPS
		ui_drawfps();
	}

	void Stop(){
		unloadAllTextures();
		clearPathingMapData();
		SPAWNCLASSES::CleanUpSpawnClasses();
	}

	bool panning = false;
	int lastx = -1;
	int lasty = -1;
	int startx = -1;
	int starty = -1;
	void MouseMotion(int x, int y, bool drag){
		if(drag && panning){
			rpanx = clamp(rpanx - (double)(x-lastx)/GetWidth()*zoomx,0.0,1.0-zoomx);
			rpany = clamp(rpany - (double)(y-lasty)/GetHeight()*zoomy,0.0,1.0-zoomy);
			lastx = x;
			lasty = y;
		}
	}

	void MouseButton(int button, bool down, int x, int y){
		if(paused){
			GAME_PAUSEMENU::MouseButton(button,down,x,y);
			return;
		}

		if(button == 0){//LEFT MOUSE BUTTON
			if(down){
				lastx = x;
				lasty = y;
				startx = x;
				starty = y;
				panning = true;
			}else{
				panning = false;
				if(startx == x && starty == y){//CLICKED

					if(queuedbuilding != nullptr){//CONSTRUCT BUILDING
						int xp = (int)(x*(map->width/(float)GetWidth()*zoomx)/16.0f+1)*16-(int)(rpanx*map->width)%16+rpanx*map->width;
						int yp = (int)(y*(map->height/(float)GetHeight()*zoomy)/16.0f+1)*16-(int)(rpany*map->height)%16+rpany*map->height;
						if(pointInBounds(xp-queuedbuilding->w/2,yp-queuedbuilding->h/2) && pointInBounds(xp+queuedbuilding->w/2,yp+queuedbuilding->h/2) && pointInBounds(xp-queuedbuilding->w/2,yp+queuedbuilding->h/2) && pointInBounds(xp+queuedbuilding->w/2,yp-queuedbuilding->h/2)){
							int z = ZoneIndex(pointCurZone(xp,yp));
							if(z >= 0){
								linkedEnt* le = ent_list->node;
								while(le != nullptr){
									float dis = dist(xp,yp,le->val->x,le->val->y);
									if(le->val->speed == 0.0f && dis<(queuedbuilding->w+queuedbuilding->h)/4.0f + (le->val->w+le->val->h)/4.0f)
										goto skipConstructionChecking;
									le = le->nxt;
								}
								Entity* tmp = new Entity(queuedbuilding,xp,yp);
								tmp->active = false;
								tmp->hp = 0;
								queuedbuilding = nullptr;
							}
						}
					}
skipConstructionChecking:

					//UPGRADE UNIT/BUILDING
					if(y >= GetHeight()-GetWidth()/10 &&  x >= GetWidth()-GetWidth()/10){
						if(selectedUnit != nullptr && selectedUnit->active && selectedUnit->upgradeEnt != nullptr)
							UpgradeEntity(selectedUnit,selectedUnit->upgradeEnt);
					}

					//SELECT UNIT
					linkedEnt* le = ent_list->node;
					while(le != nullptr){
						Entity* ent = le->val;
						//if(x > (int)(scalex*ent->x)-panx-ent->w/2 && x < (int)(scalex*ent->x)-panx+ent->w/2
							//&& y > (int)(scaley*ent->y)-pany-ent->h/2 && y < (int)(scaley*ent->y)-pany+ent->h/2){
						if(dist(x,y,(int)(scalex*ent->x)-panx,(int)(scaley*ent->y)-pany) <= (ent->w*scalex+ent->h*scaley)/4.0f){
							selectedUnit = ent;
							break;
						}
						le = le->nxt;
					}if(le == nullptr) selectedUnit = nullptr;
				}
			}

			//SELECTED NEW BUILDING
			if(y >= GetHeight()-GetWidth()/20-10 && x <= GetWidth()/2+50){
						EntityTemplate* temp = GAME_ASSETS::selectedBuildings[x/(GetWidth()/20+5)];
						if(temp != nullptr){
							queuedbuilding = temp;
						}
					}
		}//END LEFT MOUSE BUTTON
		else if(button == 1){

		}
		else if(button == 2){
			if(queuedbuilding != nullptr)
				queuedbuilding = nullptr;
		}
	}

	void Key(char key, bool down, int x, int y){
		if(key == 'q' && down)
			if(paused == false){
				paused = true;
				pausedtime = CurTime();
			}else{
				paused = false;
				setVar("startTime",getVar("startTime")+CurTime()-pausedtime);
			}
		if(paused)
			return;

		if(key > '0' && key <= '9' && down)
			if(GAME_ASSETS::selectedBuildings[key-'1'] != nullptr)
				queuedbuilding = GAME_ASSETS::selectedBuildings[key-'1'];
		if(key == '0' && down)
			if(GAME_ASSETS::selectedBuildings[9] != nullptr)
				queuedbuilding = GAME_ASSETS::selectedBuildings[9];
	}

	void MouseWheel(bool fwd, int x, int y){
		if(paused)
			return;

		float rt = !fwd ? 1.0f : -1.0f;
		rt *= 0.03f;
		float ztmp = zoom;

		zoom = clamp(zoom+rt,maxzoom,1.0f);

		rt = zoom - ztmp;

		double max = 1.0-zoom;
		rpanx = clamp(rpanx - rt/2,0.0,max);
		rpany = clamp(rpany - rt/2,0.0,max);
	}
}