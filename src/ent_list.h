#pragma once

#include "ent_main.h"
#include "g_maps.h"

class linkedEnt {
public:
	linkedEnt();

	Entity* val;
	linkedEnt* nxt;
	linkedEnt* prev;
};

class linkedEntList {
public:
	linkedEnt* node;

	linkedEntList();
	~linkedEntList();

	void add(Entity* ent);
	void del(Entity* ent);
};

extern linkedEntList* ent_list;
extern linkedEntList* ent_lists;
extern int ent_listslen;
void constructEntLists(MapData* dat);