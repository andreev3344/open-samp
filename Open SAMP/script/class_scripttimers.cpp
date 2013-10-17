#include "../main.h"

CScriptTimers::CScriptTimers ( )
{
	timerCount = 0;
}

CScriptTimers::~CScriptTimers( )
{
	for (std::map<uint32_t, timerData*>::iterator it = timersMap.begin(); it != timersMap.end(); it++)
	{
		FreeTimerMemory(it->second);
		delete it->second;
		it->second = NULL;
	}
	timersMap.clear();
}

void CScriptTimers::FreeTimerMemory(timerData* _timer)
{
	if (_timer->timerParams)
	{
		free(_timer->timerParams);
		_timer->timerParams = NULL;
	}
}

uint32_t CScriptTimers::New(char* _scriptName, uint32_t _interval, uint32_t _repeat, AMX* pAMX)
{
	timerCount++;

	timerData* _timer = new timerData;

	strncpy(_timer->funcName, _scriptName, 255);
	_timer->totalTime = _interval;
	_timer->remainingTime = _interval;
	_timer->timerRepeat = _repeat;
	_timer->paramCount = 0;
	_timer->timerKilled = false;
	_timer->timerAMX = pAMX;
	_timer->timerParams = NULL;
	timersMap.insert(std::pair<uint32_t, timerData*>(timerCount, _timer));
	return timerCount;
}

cell* get_amxaddr(AMX *amx, cell amx_addr)
{
	return (cell *)(amx->base + (int)(((AMX_HEADER *)amx->base)->dat + amx_addr));
}

uint32_t CScriptTimers::NewEx(char* _scriptName, uint32_t _interval, uint32_t _repeat, cell* _params, AMX* pAMX)
{
	timerCount++;

	timerData* _timer = new timerData;

	strncpy(_timer->funcName, _scriptName, 255);
	_timer->totalTime = _interval;
	_timer->remainingTime = _interval;
	_timer->timerRepeat = _repeat;
	_timer->timerKilled = 0;
	_timer->timerAMX = pAMX;
	
	cell amx_addr[256];
	
	char* szParamList;
	amx_StrParam(pAMX, _params[4], szParamList);
	int j, numstr, iOff = 5;
	if (szParamList == NULL) j = 0;
	else j = strlen(szParamList);
	numstr = 0;
	while (j)
	{
		j--;
		cell *paddr = NULL;
		if (*(szParamList + j) == 'a')
		{
			int numcells = *get_amxaddr(pAMX, _params[j + iOff + 1]);
			if (amx_Allot(pAMX, numcells, &amx_addr[numstr], &paddr) == AMX_ERR_NONE)
			{
				memcpy(paddr, get_amxaddr(pAMX, _params[j + iOff]), numcells * sizeof (cell));
				numstr++;
			}
		}
		else if (*(szParamList + j) == 's')
		{
			char* szParamText;
			amx_StrParam(pAMX, _params[j + iOff], szParamText);
			if (szParamText != NULL && strlen(szParamText) > 0)
			{
				int numcells = strlen(szParamText) + 1;
				if (amx_Allot(pAMX, numcells, &amx_addr[numstr], &paddr) == AMX_ERR_NONE)
				{
					amx_SetString(paddr, szParamText, 0, 0, UNLIMITED);
					numstr++;
				}
			}
			else
			{
				*szParamText = 1;
				*(szParamText + 1) = 0;
				if (amx_Allot(pAMX, 1, &amx_addr[numstr], &paddr) == AMX_ERR_NONE)
				{
					amx_SetString(paddr, szParamText, 0, 0, UNLIMITED);
					numstr++;
				}
			}
		}
		else
		{
			amx_addr[numstr] = *get_amxaddr(pAMX, _params[j + iOff]);
			numstr++;
		}
	}
	void* mem = NULL;
	if (numstr)
	{
		mem = malloc(numstr * sizeof (cell));
		memcpy(mem, &amx_addr, numstr * sizeof (cell));
		_timer->timerParams = mem;
	}
	else
	{
		_timer->timerParams = NULL;
	}
	_timer->paramCount = numstr;
	
	timersMap.insert(std::pair<uint32_t, timerData*>(timerCount, _timer));
	return timerCount;
}

void CScriptTimers::Delete(uint32_t timerId)
{
	std::map<uint32_t, timerData*>::iterator it;
	it = timersMap.find(timerId);
	if (it != timersMap.end())
	{
		FreeTimerMemory(it->second);
		delete it->second;
		it->second = NULL;
		timersMap.erase(it);
	}
}

void CScriptTimers::Kill(uint32_t timerId)
{
	std::map<uint32_t, timerData*>::iterator it;
	it = timersMap.find(timerId);
	if (it != timersMap.end())
	{
		it->second->remainingTime = 0;
		it->second->timerKilled = 1;
		it->second->timerRepeat = 0;
	}
}

void CScriptTimers::Process(uint32_t time)
{
	for (std::map<uint32_t, timerData*>::iterator it = timersMap.begin(); it != timersMap.end(); it++)
	{
		it->second->remainingTime -= time;
		if (it->second->remainingTime <= 0)
		{
			std::map<uint32_t, timerData*>::iterator _it = ++it; it--;
			if (!it->second->timerKilled)
			{
				if (__NetGame->gamemodeManager)
				{
					int idx;
					AMX* amx = it->second->timerAMX;
					if (amx && !amx_FindPublic(amx, it->second->funcName, &idx))
					{
						cell ret;
						int count = it->second->paramCount;
						int i = 0;
						if (count > 0)
						{
							cell* pars = (cell*)it->second->timerParams;
							while (i < count)
							{
								amx_Push(amx, pars[i]);
								i++;
							}
						}
						amx_Exec(amx, &ret, idx);
					}
				}
			}
	
			if (it->second->timerRepeat)
			{
				it->second->remainingTime = it->second->totalTime;
			}
			else
			{
				FreeTimerMemory(it->second);
				Delete(it->first);
			}
			it = _it;
		}
		if (it == timersMap.end()) break;
	}
}

void CScriptTimers::DeleteForMode(AMX* pAMX)
{
	bool bRestart = false;
	std::map<uint32_t, timerData*>::iterator itor;
	for (itor = this->timersMap.begin(); itor != this->timersMap.end(); bRestart?(itor=this->timersMap.begin()):(itor++))
	{
		bRestart = false;
		if (itor->second->timerAMX == pAMX)
		{
			this->FreeTimerMemory(itor->second);

			delete itor->second;
			itor->second = NULL;

			this->timersMap.erase(itor);
			
			bRestart = true;
		}
	}
}
