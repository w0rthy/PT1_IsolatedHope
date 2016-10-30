#pragma once
#include "ent_main.h"

void SetUpLists();

namespace ENT_DRAWS {
	void SetUpList();
	void (*list[])(Entity*,float,float,int,int);
	void Default(Entity* ent, float, float, int, int);
}

namespace ENT_THINKS {
	void SetUpList();
	void (*list[])(Entity*);
	void DefaultEnemy(Entity* ent);
	void DefaultTower(Entity* ent);
	void DefaultBuilder(Entity* ent);
}

namespace ENT_ATTACKS {
	void SetUpList();
	void (*list[])(Entity*,Entity*);
	void Default(Entity* ent, Entity* target);
}

namespace ENT_TAKEDAMAGES {
	void SetUpList();
	float (*list[])(Entity*,Entity*,float);
	float Default(Entity* ent, Entity* attacker, float amt);
}

namespace ENT_TAKEHEALS {
	void SetUpList();
	void (*list[])(Entity*,Entity*,float);
}

namespace ENT_DEATHS {
	void SetUpList();
	void (*list[])(Entity*,Entity*);
}

namespace ENT_DEALDAMAGES {
	void SetUpList();
	void (*list[])(Entity*,Entity*,float);
}

namespace ENT_KILLENTS {
	void SetUpList();
	void (*list[])(Entity*,Entity*);
}