#include "ent_list.h"

linkedEnt::linkedEnt(){
	nxt = nullptr;
	prev = nullptr;
	val = nullptr;
}

linkedEntList::linkedEntList(){
	node = nullptr;
}

linkedEntList::~linkedEntList(){
	linkedEnt* tmp = node;
	while(node != nullptr){
		node = node->nxt;
		delete tmp;
		tmp = node;
	}
}

void linkedEntList::add(Entity* ent){
	linkedEnt* tmp = node;

	if(ent == nullptr)
		return;

	if(tmp == nullptr){
		node = new linkedEnt();
		node->val = ent;
		return;
	}
	while(tmp->nxt != nullptr)
		tmp = tmp->nxt;
	tmp->nxt = new linkedEnt();
	tmp->nxt->prev = tmp;
	tmp->nxt->val = ent;
}

void linkedEntList::del(Entity* ent){
	linkedEnt* tmp = node;
	while(tmp != nullptr && tmp->val != ent)
		tmp = tmp->nxt;
	if(tmp == nullptr)
		return;
	if(node == tmp){
		if(node->nxt == nullptr)
			node = nullptr;
		else
			node = node->nxt;
	}
		if(tmp->prev != nullptr)
			tmp->prev->nxt = tmp->nxt;
		if(tmp->nxt != nullptr)
			tmp->nxt->prev = tmp->prev;
	delete tmp;
}

linkedEntList* ent_list = nullptr;
linkedEntList* ent_lists = nullptr;
int ent_listslen = 0;

void constructEntLists(MapData* dat){
	if (ent_list != nullptr)
		delete ent_list;

	ent_list = new linkedEntList();

	if (ent_lists != nullptr)
		delete[] ent_lists;
	
	ent_lists = new linkedEntList[dat->numZones]();
	ent_listslen = dat->numZones;

	//for(int i = 0; i < dat->numZones; i++)
		//ent_lists[i] = new linkedEntList();
}