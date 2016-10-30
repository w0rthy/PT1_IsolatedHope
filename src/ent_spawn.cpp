#include "ent_spawn.h"
#include "g_vars.h"
#include "pt_io.h"
#include <fstream>

SpawnClass::SpawnClass(){
	waves = nullptr;
	numWaves = 0;
	curWave = 0;
	done = false;
}

void SpawnClass::Spawn(){
	if(curWave >= numWaves){
		done = true;
		return;
	}
	SpawnWave* sw = &waves[curWave];
	if(sw->time < CurTime()-getVar("startTime")){
		int spawned = 0;
		int zon = random()%map->numZones;
		while(spawned<sw->count){
				Zone* z = &map->zones[zon];
				if((sw->priority&z->flags) > 0 || sw->priority == 0){
					int x = z->x + random()%z->w;
					int y = z->y + random()%z->h;
					new Entity(sw->entity,x,y);
					spawned++;
				}
				zon++;
				if(zon >= map->numZones)
					zon = 0;
		} 
		curWave++;
		Spawn();
	}
}

SpawnWave::SpawnWave(){

}

SpawnWave::SpawnWave(EntityTemplate* e, int amt, float tim, char p){
	entity = e;
	count = amt;
	time = tim;
	priority = p;
}

void SpawnWave::SetWave(EntityTemplate* ent, int amount, float tim, char p){
	entity = ent;
	count = amount;
	time = tim;
	priority = p;
}

SpawnClass* loadSpawnClass(char* path){
	SpawnClass* tmp = new SpawnClass();
	std::ifstream ifs = std::ifstream();
	ifs.open(path,ifs.in|ifs.binary);
	int l = readCmpInt(&ifs);
	tmp->numWaves = l;
	tmp->waves = new SpawnWave[l]();
	unsigned char c;
	for(int i = 0; i < l; i++){
		SpawnWave* sw = &tmp->waves[i];
		int len = readCmpInt(&ifs);
		char* unitpath = new char[len];
		for(int j = 0; j < len; j++){
			c = ifs.get();
			unitpath[j] = c;
		}
		sw->entity = loadEntity(unitpath);
		sw->count = readCmpInt(&ifs);
		sw->time = (float)readCmpFlt(&ifs);
		sw->count = ifs.get();
	}
	ifs.close();
	return tmp;
}