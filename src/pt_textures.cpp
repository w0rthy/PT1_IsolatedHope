/*
	Planar Tech 1 Texture Loading/Unloading System
*/
#include "precmp.h"

#include "pt_main.h"
#include "pt_textures.h"

char* textures[MAX_TEXTURES+1];

//Sets All Indices to Unused State
void InitTextureSystem(){
	for(int i = 1; i < MAX_TEXTURES+1; i++)
		textures[i] = "\0";
}

//Get Next Unused Texture Index
unsigned int GetNextTextureID(){
	for(int i = 1; i < MAX_TEXTURES+1; i++)
		if(textures[i][0]=='\0')
			return i;
	return 1;
}

//Returns the Index for the Path of the Specified Image
unsigned int GetTextureID(char* path){
	for(int i = 1; i < MAX_TEXTURES+1; i++)
		if(textures[i] == path)
			return i;
	return 0;
}

//Loads the Image from the Given Path or Returns Index if Already Loaded
unsigned int loadTexture(char* path){
	unsigned int index = GetTextureID(path);
	if (GetTextureID(path) > 0)
		return index;
	index = GetNextTextureID();
	textures[index] = path;
	return SOIL_load_OGL_texture(path,SOIL_LOAD_AUTO,index,SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA );
}

//Sets Index as Empty But Leaves Image Loaded Until Overriden
void unloadTexture(char* path){
	unsigned int index = GetTextureID(path);
	unloadTexture(index);
}
void unloadTexture(unsigned int index){
	if(index > 0)
		textures[index] = "\0";
	SOIL_load_OGL_texture("emptytexture.png",SOIL_LOAD_AUTO,index,SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA );
}

//Unload all textures that have been loaded
void unloadAllTextures(){
	for(unsigned int i = 1; i < MAX_TEXTURES; i++)
		if(textures[i]!= "\0")
			unloadTexture(i);
}