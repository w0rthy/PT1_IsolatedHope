#include "pt_io.h"

using namespace std;

//reads a compressed integer from 'str'
int readCmpInt(istream* str){
	unsigned int a = 0;
	char len;
	len = str->get();
	if(len == 0)
		return 0;
	unsigned char tmp;
	while(len>0){
		tmp = str->get();
		a=(a<<8)+tmp;
		len--;
	}
	return (int)a;
}

//Writes a compressed integer (num) to 'str'
void writeCmpInt(ostream* str, int num){
	if(num==0){str->put(0);return;}
	char len = (char)(ceil(log((double)num)/log(2.0)/8.0));
	str->put(len);
	int tmp = num;
	while(len>0){
		str->put((char)((tmp>>8*(len-1))&0xFF));
		len--;
	}
}

//Reads a compressed floating point from 'str'
double readCmpFlt(istream* str){
	double tmp = (double)readCmpInt(str);
	char len = str->get();
	if(len == 0)
		return tmp;
	int pows = -1;
	unsigned char c = 0;
	while(len>0){
		c = str->get();
		for(int i = 0; i < 8; i++){
			if((c&(1<<i))>0){
				tmp+=pow(2.0,pows);
			}
			pows--;
		}
		len--;
	}
	return tmp;
}

//Writes a compressed floating point to 'str'. maximum precision of 64 bytes
void writeCmpFlt(ostream* str, double num){
	if(num==0){str->put(0);str->put(0);return;}
	writeCmpInt(str,(int)num);
	double rem = num - (double)(int)num;
	int pows = -1;
	unsigned char stuff[64];
	int b;
	for(b = 0; rem > 0 && b < 64; b++){
		stuff[b] = 0;
		for(int i = 0; i < 8; i++){
			double a = pow(2.0,pows);
			if(a<=rem){
				rem-=a;
				stuff[b]=stuff[b]|(1<<i);
			}
			pows--;
		}
	}
	str->put((char)b);
	for(int i = 0; i < b; i++)
		str->put(stuff[i]);
}

//Reads a string from 'str'
char* readString(istream* str){
	char len = str->get();
	char* tmp = new char[len+1];
	for(int i = 0; i < len; i++){
		tmp[i] = str->get();
	}
	tmp[len] = '\0';

	return tmp;
}

//Writes string 's' to stream 'str'
void writeString(ostream* str, char* s){
	char len = strlen(s);
	str->put(len);
	for(int i = 0; i < len; i++)
		str->put(s[i]);
}