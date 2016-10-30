#include "ent_methods.h"

namespace ENT_KILLENTS {
	void (*list[1])(Entity*,Entity*);
	void SetUpList(){
		list[0] = nullptr;
	}
}