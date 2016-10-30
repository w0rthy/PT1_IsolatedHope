#pragma once

#define MAX_SOUNDS 128

unsigned int loadSound(char* path);
unsigned int GetSoundIndex(char* path);
void unLoadSound(char* path);
void unLoadSound(unsigned int index);

void AUD_PlaySound(unsigned int index);
void AUD_PlaySound(char* path);