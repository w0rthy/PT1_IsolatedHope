#pragma once

#define MAX_TEXTURES 512

void InitTextureSystem();
unsigned int GetNextTextureID();
unsigned int GetTextureID(char* path);
unsigned int loadTexture(char* path);
void unloadTexture(char* path);
void unloadTexture(unsigned int index);
void unloadAllTextures();