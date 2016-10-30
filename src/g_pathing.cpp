#include "g_pathing.h"
#include "pt_error.h"

#include "pt_util.h"
#include <algorithm>

Path** paths;
int pathsLen;

LinkedPath* inst_smallestpath = nullptr;

//creates hash set for computed paths and preps values
void setPathingMapData(){
	pathsLen = map->numZones*map->numZones;
	paths = new Path*[pathsLen];
	for(int i = 0; i < pathsLen; i++)
		paths[i] = nullptr;
}

//Clears all pathing data and computed paths from hash set
void clearPathingMapData(){
	for(int i = 0; i < pathsLen; i++)
		if(paths[i] != nullptr)
			freePath(paths[i]);
	delete[] paths;
	map = nullptr;
}

//Returns whether point is in a zone or not
bool pointInBounds(int x, int y){
	return pointCurZone(x,y) != nullptr;
}
bool pointInBounds(int x, int y, Zone* z){
	if(z->x <= x && z->y <= y && z->x+z->w >= x && z->y+z->h >= y)
		return true;
	return false;
}

//Finds the zone located at the point (x,y)
Zone* pointCurZone(int x, int y){
	for(int i = 0; i < map->numZones; i++){
		Zone* z = &map->zones[i];
		if(z->x <= x && z->y <= y && z->x+z->w >= x && z->y+z->h >= y)
			return z;
	}
	return nullptr;
}

Zone* pointCurZone(float x, float y){
	return pointCurZone((int)x,(int)y);
}

//Gets the index of the Zone* z
int ZoneIndex(Zone* z){
	if(z==nullptr)
		return -1;
	return (int)(z-map->zones);
}

//Creates a Path* from 'start' to 'dest'
Path* constructPath(Zone* start, Zone* dest){
	Path* p = new Path();
	p->start = start;
	p->end = dest;
	
	LinkedPath* lp = new LinkedPath();
	lp->len = 0;
	lp->dist = 0.0f;
	lp->prev = nullptr;
	lp->z = dest;
	inst_smallestpath = nullptr;
	lp = findShortestPath(lp,start,Point(start->x+start->w/2,start->y+start->h/2));
	p->dist = lp->dist;
	p->path = finalizePath(lp,&p->pathlen);

	return p;
}

//Cleans path 'clean' such that it won't interfere with 'a'
void findShortestPathCleaner(LinkedPath* a, LinkedPath* clean){
	LinkedPath* tmp = clean;
	LinkedPath* deltmp = clean;
	LinkedPath* atmp = a;
	while(tmp != nullptr){
		while(atmp != nullptr){
			if(atmp==tmp)
				goto stop;
			atmp = atmp->prev;
		}
		deltmp = tmp;
		tmp = tmp->prev;
		delete deltmp;
		atmp = a;
	}
	stop:;
	/*
	int b = 0;

	LinkedPath* atmp = a;
	LinkedPath* cleantmp = clean;

	while(cleantmp->len > atmp->len)
		cleantmp = cleantmp->prev;

	while(atmp->prev != nullptr){
		if(atmp->z != cleantmp->z)
			b = atmp->len;
		atmp = atmp->prev;
		cleantmp = cleantmp->prev;
	}

	atmp = clean;
	cleantmp = clean->prev;
	while(cleantmp->len > b){
		delete atmp;
		atmp = cleantmp;
		cleantmp  = cleantmp->prev;
	}
	delete atmp;
	delete cleantmp;*/
}

//Returns shortest path to dest as a linked list
LinkedPath* findShortestPath(LinkedPath* lp, Zone* dest, Point p){
	if(lp->z == dest){
		if(inst_smallestpath==nullptr){
			inst_smallestpath = lp;
			return lp;
		}
		else if(lp->dist < inst_smallestpath->dist){
			findShortestPathCleaner(lp,inst_smallestpath);
			inst_smallestpath = lp;
			return lp;
		}
		else
			return nullptr;
	}
	else if(lp->len >= map->numZones || (inst_smallestpath != nullptr && lp->len >= inst_smallestpath->len)){
		return nullptr;
	}

	int c = 0;
	LinkedPath* lt;
	LinkedPath* l;
	Point nxtp;
	for(int i = 0; i < lp->z->numConnections; i++){
		lt = lp;
		while(lt->len>0){
			if(lt->z == lp->z->connections[i].con2){
				c++;
				goto stop;
			}
			lt = lt->prev;
		}
		l = new LinkedPath();
		l->prev = lp;
		l->len = lp->len+1;
		nxtp = getHeadingFromPointCon(p,&lp->z->connections[i]);
		l->dist = lp->dist + dist(p,nxtp);
		l->z = lp->z->connections[i].con2;
		if(l->z != lp->z){
			if(findShortestPath(l,dest,nxtp)==nullptr){
				delete l;
				c++;
			}
		}
		stop:;
	}

	if(lp->z->numConnections==c)
		return nullptr;

	return inst_smallestpath;
}

//Converts a LinkedPath* to a Connection** for use in a Path
Connection** finalizePath(LinkedPath* p, int* pathlen){
	*pathlen = p->len;
	LinkedPath* ptmp = p;
	//Connection** path = (Connection**)malloc(sizeof(Connection*)*(p->len-1));
	Connection** path = new Connection*[p->len];
	for(int i = 0; i < p->len; i++){
		for(int j = 0; j < ptmp->z->numConnections; j++){
			if(ptmp->z->connections[j].con2 == ptmp->prev->z){
				path[i] = &ptmp->z->connections[j];
				break;
			}
		}
		ptmp = ptmp->prev;
	}

	LinkedPath* atmp = p;
	ptmp = p->prev;
	while(ptmp->prev != nullptr){
		delete atmp;
		atmp = ptmp;
		ptmp = ptmp->prev;
	}
	delete atmp;
	delete ptmp;

	return path;
}

//returns index for the path hash set
int getPathHash(Zone* start, Zone* dest){
	int st = (int)(start-map->zones);
	int dt = (int)(dest-map->zones);
	return (st*map->numZones+dt);
}

//returns path from start to dest from path hash set or constructs a new one if one doesn't exist
Path* getPath(Zone* start, Zone* dest){
	if (start == dest)
		return nullptr;

	int hash = getPathHash(start,dest);
		if(paths[hash] == nullptr){
			Path* p = constructPath(start,dest);
			paths[hash] = p;
			return p;
		}

	return paths[hash];
	//REPORTERROR("RAN OUT OF COMPLETED PATH SPACE", pathsLen); useless in new hash set implementation
}

//frees a path pointer and all its resources
void freePath(Path* p){
	//free(p->path);
	delete[] p->path;
	delete p;
}

//Returns point closest to
Point getHeadingFromPointCon(Point pos, Connection* c){
	Point v;
	if(c->vert){
		if(c->con1->x > c->con2->x)
			v.x = c->con1->x;
		else
			v.x = c->con2->x;
		if(c->con1->x+c->con1->w < c->con2->x+c->con2->w)
			v.x = clamp(pos.x,v.x,c->con1->x+c->con1->w);
		else
			v.x = clamp(pos.x,v.x,c->con2->x+c->con2->w);
		if(c->con1->y == c->con2->y+c->con2->h)
			v.y = c->con1->y;
		else
			v.y = c->con2->y;
	}
	else{
		if(c->con1->y > c->con2->y)
			v.y = c->con1->y;
		else
			v.y = c->con2->y;
		if(c->con1->y+c->con1->h < c->con2->y+c->con2->h)
			v.y = clamp(pos.y,v.y,c->con1->y+c->con1->h);
		else
			v.y = clamp(pos.y,v.y,c->con2->y+c->con2->h);
		if(c->con1->x == c->con2->x+c->con2->w)
			v.x = c->con1->x;
		else
			v.x = c->con2->x;
	}

	return v;
}

//Returns the next point the entity should move to along the path

//Point getNextPoint(Path* p, Point to, int con){
	//if(con < p->pathlen-1)
		//return getHeadingFromPointCon(getHeadingFromPointCon(to,p->path[con+1]),p->path[con]);
	//else if(con == p->pathlen-1)
		//return getHeadingFromPointCon(to,p->path[con]);
	//return to;
//}

Point getNextPoint(Path* p, Point to, int con){
	Point tmp = to;
	int at = p->pathlen-1;
	while(at>=con){
		tmp = getHeadingFromPointCon(tmp,p->path[at]);
		at--;
	}
	return tmp;
}