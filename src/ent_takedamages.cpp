#include "ent_methods.h"

namespace ENT_TAKEDAMAGES {
	float (*list[2])(Entity*,Entity*,float);
	void SetUpList(){
		list[0] = nullptr;
		list[1] = &Default;
	}

	float Default(Entity* ent, Entity* attacker, float amt){
		float tmp = amt*(1-sqr(ent->armor)/(sqr(ent->armor)+1000));
		ent->hp -= tmp;
		attacker->DealsDamage(ent,tmp);
		if(ent->hp <= 0){
			attacker->KillsEnt(ent);
			ent->Death(attacker);
		}
		return tmp;
	}
}