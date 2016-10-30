#include "pt_io.h"
#include "g_maps.h"
#include "g_pathing.h"
#include <iostream>
#include <fstream>

using namespace std;

MapData* map;

struct TempConnection {

	TempConnection(){

	}

	TempConnection(int C1, int C2, bool Vert){
		c1 = C1;
		c2 = C2;
		vert = Vert;
	}

	int c1;
	int c2;
	bool vert;
};

Connection assembleTmpConnection(MapData* dat, TempConnection t){
	Connection c = Connection(&dat->zones[t.c1],&dat->zones[t.c2],t.vert);
	return c;
}

MapData* LoadMap(char* path){
	unsigned char tmp = 0;
	MapData* dat = new MapData();
	ifstream ifs;
	ifs.open(path, ifstream::in | ifstream::binary);

	//IMAGE PATH
	int len = 0;
	do{
		tmp = ifs.get();
		len++;
	}
	while(tmp!=0);
	dat->imgPath = (char*)malloc(len);
	ifs.seekg(0);
	for(int i = 0; i < len-1; i++){
		tmp = ifs.get();
		dat->imgPath[i] = tmp;
	}dat->imgPath[len-1] = '\0';
	tmp = ifs.get();
	
	//WIDTH AND HEIGHT
	dat->width = readCmpInt(&ifs);
	dat->height = readCmpInt(&ifs);

	//FLAG BYTE
	dat->flags = ifs.get();

	//ZONES
	tmp = ifs.get();
	dat->numZones = tmp;
	//dat->zones = (Zone*)malloc(sizeof(Zone)*tmp);
	dat->zones = new Zone[tmp];
	unsigned char temp;

	TempConnection** tempcons = new TempConnection*[tmp];

	for(int i = 0; i < tmp; i++){
		//POS(X,Y) DIMENSIONS(W,H) AND FLAGS
		int x = readCmpInt(&ifs);
		int y = readCmpInt(&ifs);
		int w = readCmpInt(&ifs);
		int h = readCmpInt(&ifs);
		temp = ifs.get();
		dat->zones[i] = Zone(x,y,w,h,temp);

		//CONNECTIONS
		temp = ifs.get();
		dat->zones[i].numConnections = temp;
		//dat->zones[i].connections = (Connection*)malloc(sizeof(Connection)*temp);
		dat->zones[i].connections = new Connection[temp];
		tempcons[i] = new TempConnection[temp];
		for(int j = 0; j < temp; j++){
			unsigned char c2;
			c2 = ifs.get();
			unsigned char vert;
			vert = ifs.get();
			tempcons[i][j] = TempConnection(i,c2,(vert&1)==1);
		}
	}
	//ASSIMILATE CONNECTIONS
	for(int i = 0; i < dat->numZones; i++){
		for (int j = 0; j < dat->zones[i].numConnections; j++){
			dat->zones[i].connections[j] = assembleTmpConnection(dat, tempcons[i][j]);
		}
		delete tempcons[i];
	}
	delete tempcons;

	ifs.close();
	return dat;
}

void DeleteMap(MapData* map){

}