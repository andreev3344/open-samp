#ifndef __CSCRIPTTIMERS_H__
#define __CSCRIPTTIMERS_H__

#ifndef _STANDALONE
#include "../../SDK/amx/amx.h"
#include "../../SDK/plugincommon.h"
#endif

#include <map>

struct timerData
{
	char funcName[255];
	int totalTime;
	int remainingTime;
	int timerRepeat;
	int timerKilled;
	AMX* timerAMX;
	int paramCount;
	void* timerParams;
};

class CScriptTimers
{
#pragma pack(1)
public:

	std::map<uint32_t, timerData*> timersMap;
	uint32_t timerCount;

	void Process(uint32_t time);
	uint32_t New(char* _scriptName, uint32_t _interval, uint32_t _repeat, AMX* pAMX);
	uint32_t NewEx(char* _scriptName, uint32_t _interval, uint32_t _repeat, cell* _params, AMX* pAMX);
	void Delete(uint32_t timerId);
	void FreeTimerMemory(timerData* _timer);
	void Kill(uint32_t timerId);
	void DeleteForMode(AMX* pAMX);

	CScriptTimers();
	~CScriptTimers();

};

#endif