#include "../main.h"

CHttpClient::CHttpClient(char* unk)
{
#ifdef WIN32
	WSAData wsaData;
#endif

	memset(&(this->unkBuffer001[0]), 0, 0x7208);

	this->unkWord001 = 0;
	this->unkByte001 = 0;
	this->unkDword001 = 0;
	this->unkDword002 = 0;
	this->unkDword003 = 0;
	this->unkDword004 = 0;
	this->unkDword005 = 0;
	this->unkDword006 = 0;

	memset(&(this->unkBuffer002[0]), 0, 0x100);
	if ( unk )
	{
		this->unkDword007 = 1;
		strcpy(unkBuffer002, unk);
	}
	else
		this->unkDword007 = 0;

	this->response = 0;
	this->httpSocket = INVALID_SOCKET; // -1

#ifdef WIN32
	WSAStartup(MAKEWORD(2,2), &wsaData);
#endif
}

CHttpClient::~CHttpClient()
{
#ifdef WIN32
	closesocket(this->httpSocket);
#else
	close(this->httpSocket);
#endif

	if ( this->unkDword001 )
		free(&(this->unkDword001));
	if ( this->unkDword002 )
		free(&(this->unkDword002));
	
#ifdef WIN32
	WSACleanup();
#endif
}

