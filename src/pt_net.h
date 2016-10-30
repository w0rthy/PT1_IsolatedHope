#pragma once

#define MAX_CONNECTIONS 16

void InitNetworkLib();

unsigned int CreateSocket(char* name);
unsigned int GetSocket(char* name);
bool ConnectSocket(unsigned int sock, char* ip, char* port);

unsigned int GetDefSocket();
void SetDefSocket(unsigned int sock);

void SendData(unsigned int sock, char* data, int len);
void SendData(unsigned int sock, char* data);

void Net_HookRecFunc(unsigned int sock, void(*hook)(char*));