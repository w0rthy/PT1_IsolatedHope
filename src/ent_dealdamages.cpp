#include "ent_methods.h"

namespace ENT_DEALDAMAGES {
	void (*list[1])(Entity*,Entity*,float);
	void SetUpList(){
		list[0] = nullptr;
	}
}