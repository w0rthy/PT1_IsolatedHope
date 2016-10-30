#include "ent_methods.h"

namespace ENT_ATTACKS {
	void (*list[2])(Entity*,Entity*);
	void SetUpList(){
		list[0] = nullptr;
		list[1] = &Default;
	}

	void Default(Entity* ent, Entity* target){
				//printf("%s\n",ent->name);
		AttackInfo* atk = &ent->atk;
		//FACE TARGET
		double angle = AngleBetweenDeg(ent->x,ent->y,target->x,target->y);
		ent->ang = (float)angle;

		if(ent->tex.attack != -1)
			ent->activetex = ElapsedTime(atk->lastAtk) < atk->rate/2.0 ? ent->tex.attack : ent->tex.base;

		//READY TO ATTACK?
		float time = (float)CurTime();
		if(time - atk->lastAtk < atk->rate)
			return;
		atk->lastAtk = time;
		//ATTACK
		if(!atk->projectile){//NON PROJECTILE
			target->Damage(ent,atk->damage);
		}else{//PROJECTILE
			ProjectileList* pl = nullptr;
			ProjectileInfo* inf = &atk->proj;
			if(atk->projlist == nullptr){
				atk->projlist = new ProjectileList();
				pl = atk->projlist;
			}
			else{
				ProjectileList* lp = atk->projlist;
				while(lp->nxt != nullptr)
					lp = lp->nxt;
				lp->nxt = new ProjectileList();
				pl = lp->nxt;
				lp->nxt->prv = lp;
			}
			//SET PROJECTILE
			pl->val = Projectile(ent->x,ent->y,inf,
				angle);
			if(inf->guided)
				pl->val.target = target;
		}
	}
}