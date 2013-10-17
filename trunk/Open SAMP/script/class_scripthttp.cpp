#include "../main.h"

#ifndef WIN32
#include <pthread.h>
#endif

CScriptHttp::CScriptHttp()
{
	for(uint8_t i = 0; i < 200; i++)
	{
		memset(&(this->workers[i]), 0x0, sizeof(httpWorkers));
		
		this->workers[i].unkdword = 0;
		this->workers[i].type = 0;
	}
}

CScriptHttp::~CScriptHttp()
{

}

void SendHttpRequest(CHttpClient* pHttpClient, uint32_t type, char* url, char* data, char* site)
{
}

int StartHttpRequest(CHttpClient* pHttpClient, uint32_t type, char* url, char* data, char* site)
{

	return pHttpClient->response;
}

#ifndef WIN32
void* httpThread(void* param)
#else
void httpThread(void* param)
#endif
{
	httpWorkers* httpWorker = (httpWorkers*)param;

	if(httpWorker)
	{
		if(httpWorker->httpClient)
		{
			if ( __NetGame )
				httpWorker->lastTick = __NetGame->GetTime();

			CHttpClient* pHttpClient = httpWorker->httpClient;
			uint32_t type = httpWorker->type;

			httpWorker->responseCode = 2;

			StartHttpRequest(pHttpClient, type, httpWorker->url, httpWorker->data, "sa-mp.com");

			httpWorker->responseCode = 3;
			httpWorker->unkdword = 0;

		}
	}
#ifndef WIN32
	pthread_exit(NULL);
#endif
}

int CScriptHttp::Start(uint32_t threadID, uint32_t type, char* url, char* data, char* unk, uint32_t hasCallback, AMX* pAMX, char* callback)
{
	uint8_t idx = 0;
	for(idx = 0; idx <= 200; idx++)
	{
		if(idx == 200) return 0;
		if(!this->workers[idx].httpClient) break;
	}

	this->workers[idx].responseCode = 1;
	this->workers[idx].threadId = threadID;
	this->workers[idx].type = type;

	if(url[0] == NULL) return 0;

	if(strlen(url) > 0)
	{
		strncpy(this->workers[idx].url, url, 0x800);
		if(data)
			strncpy(this->workers[idx].data, data, 0x2000);

		this->workers[idx].unk_noCallback = hasCallback;
		this->workers[idx].httpAMX = pAMX;

		if(callback[0] == NULL)
			this->workers[idx].amxCallback = NULL;
		else
			strcpy(this->workers[idx].amxCallback, callback);

		this->workers[idx].httpClient = new CHttpClient(unk);

#ifdef WIN32
		HANDLE hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)httpThread, (LPVOID)&(this->workers[idx]), 0, (LPDWORD)&threadID);
		if(!hThread)
			CloseHandle(hThread);
#else
		pthread_t hThread;
		pthread_create(&hThread, NULL, httpThread, &(this->workers[idx]));
#endif
	}

	return 0;
}

void CScriptHttp::Process()
{
	int amxIdx;
	cell ret = 0;

	for(uint8_t i = 0; i < 200; i++)
	{
		if(this->workers[i].responseCode == 3)
		{
			if(!this->workers[i].unk_noCallback)
			{
				if(this->workers[i].httpAMX)
				{
					if (!amx_FindPublic(this->workers[i].httpAMX, this->workers[i].amxCallback, &amxIdx) )
					{
						cell amx_addr, *phys_addr;
						cell response;
						if(this->workers[i].httpClient->response)
						{
							amx_PushString(this->workers[i].httpAMX, &amx_addr, &phys_addr, "\0", 0, 0);
							response = this->workers[i].httpClient->response;
						}
						else
						{
							amx_PushString(this->workers[i].httpAMX, &amx_addr, &phys_addr, this->workers[i].data, 0, 0);
							response = this->workers[i].httpClient->unkDword005;
						}

						amx_Push(this->workers[i].httpAMX, response);
						amx_Push(this->workers[i].httpAMX, this->workers[i].threadId);
						amx_Exec(this->workers[i].httpAMX, &ret, amxIdx);
						amx_Release(this->workers[i].httpAMX, amx_addr);
					}
				}
			}
			//
			if(this->workers[i].httpClient)
				SAFE_DELETE(this->workers[i].httpClient);
			
			memset(&(this->workers[i]), 0, 0x2848);
			this->workers[i].unkdword = 0;
			this->workers[i].type = 0;

		}
	}
}
