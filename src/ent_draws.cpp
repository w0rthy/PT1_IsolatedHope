#include "ent_methods.h"

namespace ENT_DRAWS{
	void (*list[2])(Entity*,float,float,int,int);
	void SetUpList(){
		list[0] = nullptr;
		list[1] = &Default;
	}

	void Default(Entity* ent, float scalex, float scaley, int panx, int pany){
		double bs = (scalex+scaley)/2.0;

		if(ent->activetex == -1)
			ent->activetex = ent->tex.base;

		if(ent->activetex != -1){
			color col = ent->col;
			if(!ent->active)
				col = color(col.r,col.g,col.b,ent->hp/ent->hpmax*0.5f+0.5f);

			drawTexRectRotated((int)ScaleToCust(ent->x-ent->w/2,scalex)-panx,
				(int)ScaleToCust(ent->y-ent->h/2,scaley)-pany,
				ScaleToCust(ent->w,bs),
				ScaleToCust(ent->h,bs),
				ent->activetex,
				ent->ang,
				col);
		}

		ProjectileList* pl = ent->atk.projlist;
		while(pl != nullptr){
			Projectile p = pl->val;
			if(p.inf->tex == -1){
				pl = pl->nxt;
				continue;
			}
			drawTexRectRotated((int)ScaleToCust(p.x-p.inf->w/2,scalex)-panx,
			(int)ScaleToCust(p.y-p.inf->h/2,scaley)-pany,
			ScaleToCust(p.inf->w,bs),
			ScaleToCust(p.inf->h,bs),
			p.inf->tex,
			p.ang,
			p.inf->col);

			pl = pl->nxt;
		}

		if(!ent->enemy){
			double hpamt = ent->hp/ent->hpmax;
			if(hpamt < 1.0){
				drawRect(ScaleToCust(ent->x-20,scalex)-panx,ScaleToCust(ent->y-25,scaley)-pany,ScaleToCust(40,scalex),ScaleToCust(10,scaley),color(0.0f,0.0f,0.0f));
				drawRect(ScaleToCust(ent->x-20,scalex)-panx,ScaleToCust(ent->y-25,scaley)-pany,ScaleToCust((int)(40*hpamt),scalex),ScaleToCust(10,scaley),color(0.0f,1.0f,0.0f));
			}
		}
	}
}