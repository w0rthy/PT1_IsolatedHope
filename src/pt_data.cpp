/*
	Planar Tech 1 Data Transmutations Library
	Main use to write all data to byte sized files
	DEPRECATED
*/
#include "pt_main.h"

char* ShortToChar(short* ptr, size_t length){
	char* tmp = (char*)malloc(sizeof(char)*(length*2+1));
	for(unsigned int i = 0; i < length; i++){
		tmp[i*2] = (char)(ptr[i]>>8);
		tmp[i*2+1] = (char)ptr[i];
	}
	tmp[length*2] = '\0';
	return tmp;
}
short* CharToShort(char* ptr, size_t* placeLength){
	size_t len = strlen(ptr);
	short* tmp = (short*)calloc(sizeof(short),len/2);
	for(unsigned int i = 0; i < len; i++){
		tmp[i/2] += (short)ptr[i];
		if(i%2 == 0)
			tmp[i/2] = tmp[i/2]<<8;
	}
	*placeLength = (size_t)(len/2);
	return tmp;
}