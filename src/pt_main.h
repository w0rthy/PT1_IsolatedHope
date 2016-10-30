#pragma once

#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<limits>
#include<string>
#include<map>
#include<process.h>
#include "pt_util.h"

extern int TICKRATE;
extern long ticks;
extern long lastTicks;

extern int DEVWIDTH;
extern int DEVHEIGHT;

extern int Width;
extern int Height;

extern int fps;

extern double FRAMETIME;

void EXITPROGRAM();

void INITIALIZEGAME();