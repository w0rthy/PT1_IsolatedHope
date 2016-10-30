#pragma once
#include "ent_main.h"

class SpawnWave {
public:

	SpawnWave();
	SpawnWave(EntityTemplate* ent, int amount, float time, char priority);
	void SetWave(EntityTemplate* ent, int amount, float time, char priority);
	EntityTemplate* entity;
	int count;
	float time;
	char priority;
};

class SpawnClass {
public:

	SpawnClass();
	SpawnWave* waves;
	int numWaves;

	int curWave;
	bool done;

	void Spawn();
};

SpawnClass* loadSpawnClass(char* file);