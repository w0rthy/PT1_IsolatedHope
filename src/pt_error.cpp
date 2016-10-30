#include "pt_error.h"
#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;

void REPORTERROR(char* msg){
	printf("ERROR: %s\n",msg);
	ofstream ofs;
	ofs.open("errorlog.txt",ios::out | ios::app);
	ofs<<msg<<"\n\n";
	ofs.close();
}

void REPORTERROR(char* msg, int data1){
	int size = strlen(msg)+(int)ceil(log10(max(data1,1)+1))+3;
	char* tmp = (char*)malloc(size);
	sprintf_s(tmp,size,"%s, %i", msg, data1);
	REPORTERROR(tmp);
	free(tmp);
}

void REPORTERROR(char* msg, int data1, int data2){
	int size = strlen(msg)+(int)ceil(log10(max(data1,1)+1))+(int)ceil(log10(max(data2,1)+1))+4;
	char* tmp = (char*)malloc(size);
	sprintf_s(tmp,size,"%s, %i %i", msg, data1, data2);
	REPORTERROR(tmp);
	free(tmp);
}