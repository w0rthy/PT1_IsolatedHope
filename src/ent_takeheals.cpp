#include "ent_methods.h"

namespace ENT_TAKEHEALS{
	void (*list[1])(Entity*,Entity*,float);
	void SetUpList(){
		list[0] = nullptr;
	}
}