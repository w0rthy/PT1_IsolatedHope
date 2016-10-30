#pragma once

#define PI 3.1415926535897932384626433832795

struct Point {

	Point(){}

	Point(int x1, int y1){
		x = x1;
		y = y1;
	}
	int x, y;
};

 extern unsigned int randseed;

 extern int mousex;
 extern int mousey;

 extern inline double CurTime();
 extern inline double ElapsedTime(double time);

 extern inline int ScaleToX(int a);
 extern inline float ScaleToX(float a);
 extern inline int ScaleToY(int a);
 extern inline float ScaleToF(float a);
 extern inline int ScaleToCust(int a, float scale);
 extern inline float ScaleToCust(float a, float scale);

 extern inline float GetXScale();
 extern inline float GetYScale();

 extern inline int GetWidth();
 extern inline int GetHeight();

 extern inline float ScaleTime(int a);
 extern inline float ScaleTime(float a);
 extern inline double ScaleTime(double a);

 extern inline double AngleBetweenRad(int x1, int y1, int x2, int y2);
 extern inline double AngleBetweenDeg(int x1, int y1, int x2, int y2);
 extern inline double AngleBetweenRad(float x1, float y1, float x2, float y2);
 extern inline double AngleBetweenDeg(float x1, float y1, float x2, float y2);
 extern inline double AngleBetweenRad(double x1, double y1, double x2, double y2);
 extern inline double AngleBetweenDeg(double x1, double y1, double x2, double y2);

 extern inline float sqr(float a);
 extern inline int sqr(int a);

 extern inline int min(int a, int b);
 extern inline int max(int a, int b);
 extern inline int clamp(int a, int min, int max);

 extern inline float min(float a, float b);
 extern inline float max(float a, float b);
 extern inline float clamp(float a, float min, float max);

 extern inline double min(double a, double b);
 extern inline double max(double a, double b);
 extern inline double clamp(double a, double min, double max);

 extern inline float dist(int x1, int y1, int x2, int y2);
 extern inline float dist(Point a, Point b);

 extern inline int random();
 extern inline void impulseRandomSeed(unsigned int amt);