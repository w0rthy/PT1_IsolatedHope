#pragma once

#include <cstdlib>

struct Connection;

struct Zone {
	int x,y,w,h;
	unsigned char flags;
	Connection* connections;
	unsigned char numConnections;

	Zone(){}

	Zone(int X, int Y, int W, int H, unsigned char FLAGS){
		x = X;
		y = Y;
		w = W;
		h = H;
		flags = FLAGS;
		connections = nullptr;
	}

	~Zone(){
		if(connections!=nullptr)
			free(connections);
	}
};

struct Connection {
	bool vert;
	Zone* con1, *con2;

	Connection(){}

	Connection(Zone* z1, Zone* z2, bool vertical){
		vert = vertical;
		con1 = z1;
		con2 = z2;
	}
};

struct MapData {
	Zone* zones;
	unsigned char numZones;
	char* imgPath;
	int width;
	int height;
	unsigned char flags;
};

MapData* LoadMap(char* path);

extern MapData* map;