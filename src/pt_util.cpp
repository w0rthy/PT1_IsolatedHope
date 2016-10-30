/*
	Planar Tech 1 Utility Library
*/

#include "pt_main.h"

unsigned int randseed = 0;

int mousex = 0;
int mousey = 0;

inline double ElapsedTime(double time){
	return CurTime() - time;
}

inline int ScaleToX(int a){
	return (int)(a*GetXScale());
}
inline float ScaleToX(float a){
	return a*GetXScale();
}

inline int ScaleToY(int a){
	return (int)(a*GetYScale());
}

inline float ScaleToY(float a){
	return a*GetYScale();
}

inline int ScaleToCust(int a, float scale){
	return (int)(a*scale);
}

inline float ScaleToCust(float a, float scale){
	return a*scale;
}

inline float GetXScale(){
	return (float)GetWidth()/DEVWIDTH;
}

inline float GetYScale(){
	return (float)GetHeight()/DEVHEIGHT;
}

inline int GetWidth(){
	return Width;
}

inline int GetHeight(){
	return Height;
}

inline float ScaleTime(int a){
	return a*(float)FRAMETIME;
}

inline float ScaleTime(float a){
	return a*(float)FRAMETIME;
}

inline double ScaleTime(double a){
	return a*(double)FRAMETIME;
}

inline double AngleBetweenRad(int x1, int y1, int x2, int y2){
	return atan2((double)(y2-y1),(double)(x2-x1)) + PI/2.0;
}

inline double AngleBetweenDeg(int x1, int y1, int x2, int y2){
	return AngleBetweenRad(x1,y1,x2,y2)*180/PI;
}

inline double AngleBetweenRad(float x1, float y1, float x2, float y2){
	return atan2((double)(y2-y1),(double)(x2-x1)) + PI/2.0;
}

inline double AngleBetweenDeg(float x1, float y1, float x2, float y2){
	return AngleBetweenRad(x1,y1,x2,y2)*180/PI;
}

inline double AngleBetweenRad(double x1, double y1, double x2, double y2){
	return atan2((double)(y2-y1),(double)(x2-x1)) + PI/2.0;
}

inline double AngleBetweenDeg(double x1, double y1, double x2, double y2){
	return AngleBetweenRad(x1,y1,x2,y2)*180/PI;
}

inline float sqr(float a){
	return a*a;
}

inline int sqr(int a){
	return a*a;
}

inline int min(int a, int b){
	return (a < b ? a : b);
}

inline int max(int a, int b){
	return (a > b ? a : b);
}

inline int clamp(int a, int mi, int ma){
	int minn = mi;
	int maxx = ma;
	if(mi > ma){
		minn = ma;
		maxx = mi;
	}
	return min(max(a,minn),maxx);
}

inline float min(float a, float b){
	return (a <= b ? a : b);
}

inline float max(float a, float b){
	return (a >= b ? a : b);
}

inline float clamp(float a, float mi, float ma){
	float minn = mi;
	float maxx = ma;
	if(mi > ma){
		minn = ma;
		maxx = mi;
	}
	return min(max(a,minn),maxx);
}

inline double min(double a, double b){
	return (a <= b ? a : b);
}

inline double max(double a, double b){
	return (a >= b ? a : b);
}

inline double clamp(double a, double mi, double ma){
	double minn = mi;
	double maxx = ma;
	if(mi > ma){
		minn = ma;
		maxx = mi;
	}
	return min(max(a,minn),maxx);
}

inline float dist(int x1, int y1, int x2, int y2){
	return (float)sqrt(sqr(x2-x1)+sqr(y2-y1));
}

inline float dist(Point a, Point b){
	return dist(a.x,a.y,b.x,b.y);
}

inline int random(){
	srand(randseed);
	impulseRandomSeed(3+randseed/10+(int)CurTime()%60);
	return rand();
}

inline void impulseRandomSeed(unsigned int a){
	randseed = (randseed+a)%INT_MAX;
}