#include "ent_spawnclasses.h"
#include "ent_enemies.h"

namespace SPAWNCLASSES {
	SpawnClass testclass = SpawnClass();
	void SetUpSpawnClasses(){
		testclass.curWave = 0;
		testclass.done = false;
		testclass.numWaves = 3;
		testclass.waves = new SpawnWave[3];
		testclass.waves[0].count = 5;
		testclass.waves[0].entity = &ENTS_ENEMIES::mouse;
		testclass.waves[0].priority = 0;
		testclass.waves[0].time = 20.0f;
		
		testclass.waves[1].count = 10;
		testclass.waves[1].entity = &ENTS_ENEMIES::mouse;
		testclass.waves[1].priority = 0;
		testclass.waves[1].time = 25.0f;

		testclass.waves[2].count = 30;
		testclass.waves[2].entity = &ENTS_ENEMIES::mouse;
		testclass.waves[2].priority = 0;
		testclass.waves[2].time = 40.0f;
	}
	
	void CleanUpSpawnClasses(){
		delete[] testclass.waves;
		testclass.waves = nullptr;
	}
}