/*
	Planar Tech 1 Keyboard Input Handler
*/

#include "pt_main.h"

bool keys[UCHAR_MAX];

//Sets the Key's State to 'state'
//Up = false Down = true
void SetKeyState(unsigned char key, bool state){
	keys[key] = state;
}

//Sets the Key's State to Held Down
void SetKeyDown(unsigned char key){
	SetKeyState(key,true);
}

//Sets the Key's State to Up
void SetKeyUp(unsigned char key){
	SetKeyState(key,false);
}

//Gets the State of the Requested Key
bool GetKey(unsigned char key){
	return keys[key];
}