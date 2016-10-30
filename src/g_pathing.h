#pragma once

#include "pt_util.h"
#include "g_maps.h"

struct Path {
	Zone* start;
	Zone* end;
	Connection** path;
	int pathlen;
	float dist;
};

struct LinkedPath {
	int len;
	float dist;
	Zone* z;
	LinkedPath* prev;
};

void setPathingMapData();

void clearPathingMapData();

bool pointInBounds(int x, int y);
bool pointInBounds(int x, int y, Zone* z);

Zone* pointCurZone(int x, int y);
Zone* pointCurZone(float x, float y);

int ZoneIndex(Zone* z);

Path* constructPath(Zone* start, Zone* dest);

LinkedPath* findShortestPath(LinkedPath* lp, Zone* dest, Point p);

Connection** finalizePath(LinkedPath* p, int* pathlen);

void freePath(Path* p);

Path* getPath(Zone* start, Zone* dest);

Point getHeadingFromPointCon(Point pos, Connection* c);

Point getNextPoint(Path* p, Point to, int con);