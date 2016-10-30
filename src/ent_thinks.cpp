#include "ent_methods.h"
#include "ent_list.h"
#include "pt_keyboard.h"

namespace ENT_THINKS {
	void (*list[4])(Entity*);
	void SetUpList(){
		list[0] = nullptr;
		list[1] = &DefaultEnemy;
		list[2] = &DefaultTower;
		list[3] = &DefaultBuilder;
	}
	//DEFUALT ENEMY
	void DefaultEnemy(Entity* ent) {
		if(ent->target == nullptr || ent->target->zone != ent->dest){
			ent->FindTarget();
			ent->activetex = ent->tex.base;
			return;
		}

		if(dist(ent->GetPos(),ent->target->GetPos()) <= ent->atk.range){
			ent->Attack(ent->target);
			return;
		}

		ent->FindTarget();

		//if distance between target and this is not in all attack ranges, move, else attack
		if(ent->zone != ent->dest && ent->dest >= 0 && ent->zone >= 0){
			Path* p = getPath(&map->zones[ent->zone],&map->zones[ent->dest]);
			Point po = getNextPoint(p,Point((int)ent->target->x,(int)ent->target->y),0);
			if((int)ent->x == po.x && (int)ent->y == po.y){
				int z = ZoneIndex(p->path[0]->con2);

				if(ent->zone >= 0)
					ent_lists[ent->zone].del(ent);
				if(z >= 0)
					ent_lists[z].add(ent);

				ent->zone = z;
				DefaultEnemy(ent);
				return;
			}
			double angl = AngleBetweenRad((int)ent->x,(int)ent->y,po.x,po.y);
			ent->ang = (angl*180.0/PI);
			Zone* z = &map->zones[ent->zone];
			float spd = ScaleTime(ent->speed);
			ent->SetPos(
				/*clamp(clamp((float)(ent->x+sin(angl)*spd),(float)z->x,(float)z->x+z->w),ent->x,(float)po.x),
				clamp(clamp((float)(ent->y-cos(angl)*spd),(float)z->y,(float)z->y+z->h),ent->y,(float)po.y));*/
				clamp((float)(ent->x+sin(angl)*spd),ent->x,(float)po.x),
				clamp((float)(ent->y-cos(angl)*spd),ent->y,(float)po.y));
		}
		else if(ent->zone == ent->dest && ent->target != nullptr){
			double angl = AngleBetweenRad(ent->x,ent->y,ent->target->x,ent->target->y);
			ent->ang = (angl*180.0/PI);
			Zone* z = &map->zones[ent->zone];
			float spd = ScaleTime(ent->speed);
			ent->SetPos(
				//clamp(clamp((float)(ent->x+sin(angl)*spd),(float)z->x,(float)z->x+z->w),ent->x,ent->target->x),
				//clamp(clamp((float)(ent->y-cos(angl)*spd),(float)z->y,(float)z->y+z->h),ent->y,ent->target->y));
				clamp((float)(ent->x+sin(angl)*spd),ent->x,ent->target->x),
				clamp((float)(ent->y-cos(angl)*spd),ent->y,ent->target->y));
		}

		if(ent->tex.move != -1)
			ent->activetex = (int)(CurTime()*2.0+(int)ent%3)%2 == 0 ? ent->tex.base : ent->tex.move;
		else
			ent->activetex = ent->tex.base;
	}

	//DEFAULT TOWER
	void DefaultTower(Entity* ent){
		if(ent->target == nullptr){
			ent->FindTarget();
			return;
		}

		if(dist(ent->GetPos(),ent->target->GetPos()) <= ent->atk.range){
			ent->Attack(ent->target);
			return;
		}
		ent->FindTarget();
		double angl = AngleBetweenRad(ent->x,ent->y,ent->target->x,ent->target->y);
		ent->ang = (angl*180.0/PI);
	}

	//DEFAULT BUILDER
	void DefaultBuilder(Entity* ent){
		if(ent->zone < 0)
			return;
		float tmpx = 0.0f;
		float tmpy = 0.0f;
		if(GetKey('w'))
			tmpy += -1.0f;
		if(GetKey('s'))
			tmpy += 1.0f;
		if(GetKey('a'))
			tmpx += -1.0f;
		if(GetKey('d'))
			tmpx += 1.0f;
		if(tmpx == 0.0f && tmpy == 0.0f){
			ent->activetex = ent->tex.base;
			linkedEnt* le = ent_list->node;
			Entity* etmp;
			while(le!=nullptr){
				etmp = le->val;
				if(etmp->enemy == ent->enemy && etmp != ent && dist(ent->GetPos(),etmp->GetPos()) <= ent->atk.range){
					if(etmp->hp != etmp->hpmax){
						ent->activetex = ent->tex.attack;
						ent->ang = AngleBetweenDeg(ent->x,ent->y,etmp->x,etmp->y);
						etmp->hp = min(etmp->hp+ScaleTime(etmp->hpmax*0.2f),etmp->hpmax);
						return;
					}
				}
				le = le->nxt;
			}
			return;
		}
		if(ent->tex.move != -1)
			ent->activetex = (int)(CurTime()*2.0+(int)ent%3)%2 == 0 ? ent->tex.base : ent->tex.move;
		else
			ent->activetex = ent->tex.base;

		double ang = AngleBetweenRad(ent->x,ent->y,ent->x+tmpx,ent->y+tmpy);
		ent->ang = ang*180.0/PI;
		tmpx = ent->x + ScaleTime(sin(ang)*ent->speed);
		tmpy = ent->y + ScaleTime(-cos(ang)*ent->speed);

		Zone* z = &map->zones[ent->zone];
		
		if(!pointInBounds(tmpx,tmpy,z)){
			for(int i = 0; i < z->numConnections; i++){
				if(pointInBounds(tmpx,tmpy,z->connections[i].con2)){
					ent->SetPos(tmpx,tmpy);
					ent->CalcZone();
					return;
				}
			}
			ent->SetPos(clamp(tmpx,(float)z->x,(float)(z->x+z->w)),clamp(tmpy,(float)z->y,(float)(z->y+z->h)));
		}else
			ent->SetPos(tmpx,tmpy);
	}
}