#include "ent_methods.h"

namespace ENT_DEATHS {
	void (*list[1])(Entity*,Entity*);
	void SetUpList(){
		list[0] = nullptr;
	}
}