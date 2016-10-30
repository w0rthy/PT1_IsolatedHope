/*
	Planar Tech 1 Audio Engine
*/

#include "pt_main.h"
#include "pt_audio.h"

#include <cstdio>
#include <Windows.h>

char* sounds[MAX_SOUNDS+1];
WAVEFORMATEX* rawsounds[MAX_SOUNDS+1];

WAVEFORMATEX* loadFileWAV(char* path){
	return new WAVEFORMATEX;
}

unsigned int GetNextSoundIndex(){
	for(int i = 1; i < MAX_SOUNDS; i++)
		if(rawsounds[i] == nullptr)
			return i;
	return 0;
}

unsigned int loadSound(char* path){
	unsigned int index = GetSoundIndex(path);
	if(index > 0)
		return index;
	index = GetNextSoundIndex();
	sounds[index] = path;
	rawsounds[index] = loadFileWAV(path);
	return index;
}

unsigned int GetSoundIndex(char* path){
	for(int i = 1; i < MAX_SOUNDS; i++)
		if(strcmp(sounds[i],path)==0)
			return i;
	return 0;
}

void unLoadSound(char* path){
	unLoadSound(GetSoundIndex(path));
}
void unLoadSound(unsigned int index){
	sounds[index] = "\0";
	delete rawsounds[index];
	rawsounds[index] = nullptr;
}

void AUD_PlaySound(unsigned int index){

}
void AUD_PlaySound(char* path){
	PlaySound(path,NULL,SND_ASYNC);
}