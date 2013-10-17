#include "main.h"

CConsole::CConsole ( )
{

}

CConsole::~CConsole( )
{
	this->varMap.clear();
}

extern BOOL quitProcess;
void con_exit()
{
	quitProcess = true;
}

void con_exec()
{
	char* arg = strtok(NULL, " ");
	if (arg)
	{
		char tmp[1025];
		char tmpvarname[128];
		sprintf(tmp, "%s.cfg", arg);
		FILE* f = fopen(tmp, "r");
		if (!f)
			logprintf("Unable to exec file '%s'.", tmp);

		else 
		{
			while (fgets(tmp, 1024, f))
			{
				int len = strlen(tmp);
				if (len > 0 && tmp[len-1] == '\n')
					tmp[strlen(tmp)-1] = 0;
				len = strlen(tmp);
				if (len > 0 && tmp[len-1] == '\r')
					tmp[strlen(tmp)-1] = 0;
				if (tmp[0] == 0)
					continue;

				for (size_t i=0; i<strlen(tmp)-1; i++)
				{
					if (((tmp[i] == '/') && (tmp[i+1] == '/')) || tmp[i] == '#')
					{
						tmp[i] = 0;
						break;
					}
				}
				if (strlen(tmp) > 2)
				{
					if ((tmp[0] != '/') && (tmp[1] != '/'))
						for(int i = 0; tmp[i] != '\0'; i++)
						{
							if (tmp[i] == ' ')
							{
								tmpvarname[i] = '\0';
								break;
							}

							tmpvarname[i] = tmp[i];
						}
						if (__Console->FindVar(tmpvarname))
						{
							__Console->Execute(tmp);
						}
				}
			}
			fclose(f);
		}
	} 
	else 
	{
		logprintf("Usage:");
		logprintf("  exec <filename>");
	}
}

// Open SA:MP
void con_scriptdebug()
{
	char* arg = strtok(NULL, " ");
	if (arg)
	{
		bool activate = atoi(arg) != 0;
		bScriptDebug = activate;
		if(activate) logprintf("Script debugging activated.");
		else logprintf("Script debugging deactivated.");
	}
}


void con_echo()
{
	char* arg = strtok( NULL, " " );
	if( arg )
	{
		logprintf( "%s", arg );
	}
}

void con_kick()
{
	char* arg = strtok( NULL, " " );
	if( arg )
	{
		_PlayerID playerID = ( _PlayerID )atol( arg );
		if( __NetGame->playerPool->GetSlotState( playerID ) )
		{
			in_addr addr;
			addr.s_addr = __NetGame->getRakInterface()->GetPlayerIDFromIndex( playerID ).binaryAddress;
			logprintf( "%s < %d - %s> has been kicked.", __NetGame->playerPool->getPlayerNick( playerID ), playerID, inet_ntoa( addr ) );
			__NetGame->KickPlayer( playerID );
		}
	}
}

void con_ban()
{
	char* arg = strtok(NULL, " ");
	if (arg)
	{
		_PlayerID playerID = atoi(arg);
		if (__NetGame->playerPool->GetSlotState(playerID))
		{
			PlayerID Player = __NetGame->rakServerInterface->GetPlayerIDFromIndex(playerID);
			in_addr in;
			in.s_addr = Player.binaryAddress;
			logprintf("%s <#%d - %s> has been banned.", __NetGame->playerPool->getPlayerNick(playerID), playerID, inet_ntoa(in));
			__NetGame->AddBan(__NetGame->playerPool->getPlayerNick(playerID), inet_ntoa(in), "CONSOLE BAN");
			__NetGame->KickPlayer(playerID);
		}
	}
}

bool IsStrIp(char* szIn);
bool IsStrIp(char* szIn)
{
	char* part;
	char tmp[16];
	memcpy(&tmp, szIn, 16);
	int parts = 0;
	part = strtok(szIn, ".");
	while (part != NULL)
	{
		parts++;
		if (part != "*")
		{
			if (atoi(part) < 0 || atoi(part) > 255) return false;
		}
		part = strtok(NULL, ".");
	}
	if (parts != 4) return false;
	memcpy(szIn, &tmp, 16);
	return true;
}

void con_banip()
{
	char* arg = strtok(NULL, " ");
	printf("arg: %s\n", arg);
	if (arg && IsStrIp(arg))
	{
		logprintf("IP %s has been banned.", arg);
		__NetGame->AddBan("NONE", arg, "IP BAN");
	}
}

void con_unbanip()
{
	char* arg = strtok(NULL, " ");
	if (arg && IsStrIp(arg))
	{
		__NetGame->RemoveBan(arg);
	}
}

extern BOOL isGamemodeFinished;
void con_gmx()
{	
	char* gamemode;
	gamemode = __NetGame->getNextGamemodeFile();
	if (gamemode != NULL && __NetGame->setNextGamemodeFile(gamemode))
		isGamemodeFinished = TRUE;
}

void con_changemode()
{
	char* arg = strtok(NULL, "");
	if (arg)
	{
		if(__NetGame->setNextGamemodeFile(arg))
			isGamemodeFinished = TRUE;
	}
}

void con_varlist()
{
	__Console->PrintVarList();
}

void con_say() 
{
	char* arg = strtok(NULL, "");
	char msg[255];
	if (arg) 
	{
		sprintf(msg, "* Admin: %.230s", arg);
		__NetGame->SendClientMessageToAll(0x2587CEAA, msg);
	}
}

void con_reloadbans() 
{
	__NetGame->LoadBanList();
}

void LoadServerLog();
void con_reloadlog() 
{
	LoadServerLog();
}

void con_players() 
{
	if (__NetGame->rakServerInterface->GetConnectedPlayers() == 0) return;

	logprintf("ID\tName\tPing\tIP");

	for(_PlayerID i = 0; i < MAX_PLAYERS; i++)
	{
		if ( __NetGame->playerPool->GetSlotState(i) == TRUE)
		{
			PlayerID Player = __NetGame->rakServerInterface->GetPlayerIDFromIndex(i);
			in_addr in;
			in.s_addr = Player.binaryAddress;

			logprintf("%d\t%s\t%d\t%s", i, __NetGame->playerPool->getPlayerNick(i), __NetGame->rakServerInterface->GetLastPing( Player ), inet_ntoa(in));
		}
	}
}

void con_gravity()
{
	char* arg = strtok(NULL, " ");
	if (arg)
		__NetGame->setGravity((float)atof(arg));
}

void con_weather()
{
	char* arg = strtok(NULL, " ");
	if (arg)
		__NetGame->setWeather(atoi(arg));
}

void con_loadfs()
{
	_PlayerID Temp = RconUser;
	RconUser = INVALID_PLAYER_ID;

	char* arg = strtok(NULL, "");
	if (arg)
	{
		if(!__NetGame->filterscriptsManager->LoadFilterScript(arg))
		{
			RconUser = Temp;
			logprintf("  Filter script '%s.amx' load failed.", arg);
		}
		else
		{
			RconUser = Temp;
			logprintf("  Filterscript '%s.amx' loaded.", arg);			
		}
	}
}

void con_reloadfs()
{
	_PlayerID Temp = RconUser;

	RconUser = INVALID_PLAYER_ID;
	char* arg = strtok(NULL, "");
	if (arg)
	{
		if(__NetGame->filterscriptsManager->UnloadFilterScript(arg))
		{
			RconUser = Temp;
			logprintf("  Filter script '%s.amx' unloaded.", arg);
		}
		else
		{
			RconUser = Temp;
			logprintf("  Filter script '%s.amx' unload failed.", arg);
		}

		RconUser = INVALID_PLAYER_ID;
		if(!__NetGame->filterscriptsManager->LoadFilterScript(arg))
		{
			RconUser = Temp;
			logprintf("  Filter script '%s.amx' load failed'.", arg);
		}
		else
		{
			RconUser = Temp;
			logprintf("  Filterscript '%s.amx' loaded.", arg);
		}
	}
}

void con_unloadfs()
{
	_PlayerID Temp = RconUser;
	RconUser = INVALID_PLAYER_ID;

	char* arg = strtok(NULL, "");
	if (arg)
	{
		if(__NetGame->filterscriptsManager->UnloadFilterScript(arg))
		{
			RconUser = Temp;
			logprintf("  Filterscript '%s.amx' unloaded.", arg);
		}
		else
		{
			RconUser = Temp;
			logprintf("  Filter script '%s.amx' unload failed.", arg);
		}
	}
}

void con_cmdlist();

struct ConsoleCommand_s
{
	char		cmdName[255];
	uint32_t	cmdFlags;
	void		(*CmdFunc)();
} ConsoleCommands[] = 
{
	{"echo",		0,	con_echo},
	{"exec",		0,	con_exec},
	{"cmdlist",		0,	con_cmdlist},
//	{"scriptdebug", 0,  con_scriptdebug}, // Open SA:MP
	{"varlist",		0,	con_varlist},
	{"exit",		0,	con_exit},
	{"kick",		0,	con_kick},
	{"ban",			0,	con_ban},
	{"gmx",			0,	con_gmx},
	{"changemode",	0,	con_changemode},
	{"say",			0,	con_say},
	{"reloadbans",	0,	con_reloadbans},
	{"reloadlog",	0,	con_reloadlog},
	{"players",		0,	con_players},
	{"banip",		0,	con_banip},
	{"unbanip",		0,	con_unbanip},
	{"gravity",		0,	con_gravity},
	{"weather",		0,	con_weather},
	{"loadfs",		0,	con_loadfs},
	{"unloadfs",	0,	con_unloadfs},
	{"reloadfs",	0,	con_reloadfs},
};

void con_cmdlist()
{
	logprintf("Console Commands:");
	for (int i=0; i < ARRAY_SIZE(ConsoleCommands); i++)
	{
		logprintf("  %s%s", ConsoleCommands[i].cmdName, (ConsoleCommands[i].cmdFlags & 1)?" (DEBUG)":"");
	}
	logprintf("");
}


consoleVarStruct* CConsole::FindVar(char* pVarName)
{	
	std::map<std::string, consoleVarStruct*>::iterator itor;
	itor = varMap.find(pVarName);
	if (itor != varMap.end())
	{
		return itor->second;
	}
	return NULL;
}

bool CConsole::RemoveVar( char* pVarName )
{
	std::map<std::string, consoleVarStruct*>::iterator itor;
	itor = varMap.find(pVarName);
	

	
	if (itor != varMap.end())
	{
		if( itor->second->varFlags & CONSOLE_VARFLAG_READONLY || itor->second->varFlags & CONSOLE_VARFLAG_UNREMOVABLE )
			return false;
		varMap.erase( itor );
		return true;
	}
	return false;
}


char* CConsole::GetStringVar(char* pVarName)
{
	consoleVarStruct* ConVar = FindVar(pVarName);
	if (ConVar != NULL)
	{
		if (ConVar->varType == CONSOLE_VARTYPE_STRING) // string
			return (char*)ConVar->varValue;
	}
	return NULL;
}

void CConsole::SetStringVar(char* pVarName, char* pString)
{
	char varName[100];
	strcpy(varName, pVarName);
	consoleVarStruct* ConVar = FindVar(varName);
	if (ConVar != NULL)
	{
		if (ConVar->varType == CONSOLE_VARTYPE_STRING)
		{
			if (ConVar->varValue != NULL)
				delete [] ConVar->varValue;

			char* str = new char[strlen(pString)+1];
			strcpy(str, pString);
			ConVar->varValue = str;
		}
	}
}

bool CConsole::GetBoolVar(char* pVarName)
{
	consoleVarStruct* ConVar = FindVar(pVarName);
	if (ConVar != NULL)
	{
		if (ConVar->varType == CONSOLE_VARTYPE_BOOL)
			return *(bool*)ConVar->varValue;
	}
	return true;
	return false;
}

int CConsole::GetIntVar(char* pVarName)
{
	consoleVarStruct* ConVar = FindVar(pVarName);
	if (ConVar != NULL)
	{
		if (ConVar->varType == CONSOLE_VARTYPE_INT)
			return *(int*)ConVar->varValue;
	}
	return 0;
}

// #define _USE_BITSTREAMS

void CConsole::SendRules(char* queryData, SOCKET socket, const sockaddr_in* to, int tolen)
{
	const char* varName;
	char varValue[1024];

	std::map<std::string, consoleVarStruct*>::iterator itor;

	uint16_t svrRuleCount = 0;
	for (itor = varMap.begin(); itor != varMap.end(); itor++)
		if (itor->second->varFlags & CONSOLE_VARFLAG_RULE)
			svrRuleCount++;

	uint16_t rulesLen = 13 + (svrRuleCount * 62);

#ifndef _USE_BITSTREAMS
	char* dataBuf = new char[rulesLen];
	char* dataPtr = dataBuf;
	
	memcpy(dataBuf, queryData, 11);
	dataBuf += 11;
#else
	RakNet::BitStream rules;
	
	rules.Write((char*)queryData, 11);
	rules.Write(svrRuleCount);
#endif
#ifndef _USE_BITSTREAMS
	memcpy(dataBuf, &svrRuleCount, sizeof(uint16_t));
	dataBuf += sizeof(uint16_t);
#endif

	uint8_t varNameLen;

	for (itor = varMap.begin(); itor != varMap.end(); itor++)
	{
		if (itor->second->varFlags & 4)
		{
			varName = itor->first.c_str();
			switch (itor->second->varType)
			{
				case CONSOLE_VARTYPE_FLOAT:
					sprintf(varValue, "%f", *(float*)itor->second->varValue);
					break;
				case CONSOLE_VARTYPE_INT:
					sprintf(varValue, "%d", *(int*)itor->second->varValue);
					break;
				case CONSOLE_VARTYPE_BOOL:
					sprintf(varValue, "%d", *(bool*)itor->second->varValue);
					break;
				case CONSOLE_VARTYPE_STRING:
					strcpy(varValue, (char*)itor->second->varValue);
					break;
			}

			varNameLen = strlen(varName);
#ifdef _USE_BITSTREAMS
			rules.Write(varNameLen);
			rules.Write(varName, varNameLen);
#else
			memcpy(dataBuf, &varNameLen, sizeof(uint8_t));
			dataBuf += sizeof(uint8_t);
			memcpy(dataBuf, varName, varNameLen);
			dataBuf += varNameLen;
#endif
			varNameLen = strlen(varValue);
#ifdef _USE_BITSTREAMS
			rules.Write(varNameLen);
			rules.Write(varValue, varNameLen);
#else
			memcpy(dataBuf, &varNameLen, sizeof(uint8_t));
			dataBuf += sizeof(uint8_t);

			memcpy(dataBuf, varValue, varNameLen);
			dataBuf += varNameLen;
#endif
		}
	}
#ifdef _USE_BITSTREAMS
	sendto(socket, (char*)rules.GetData(), rules.GetNumberOfBytesUsed(), 0, (sockaddr*)to, tolen);
#else
	sendto(socket, dataPtr, (int)(dataBuf - dataPtr), 0, (sockaddr*)to, tolen);
	delete [] dataPtr;
#endif
}

void CConsole::AddVar(char* pVarName, uint32_t VarType, uint32_t VarFlags, void* VarPtr,
						   varFuncType VarChangeFunc)
{
	if (FindVar(pVarName) != NULL)
	{
		logprintf("Unable to add console variable '%s'. Already exists.", pVarName);
		return;
	}

	consoleVarStruct* ConVar = new consoleVarStruct;
	ConVar->varType = VarType;
	ConVar->varFlags = VarFlags;
	ConVar->varValue = VarPtr;
	ConVar->varFunc = VarChangeFunc;

	if (VarChangeFunc)
		ConVar->varFunc();

	varMap.insert(std::pair<std::string, consoleVarStruct*>(pVarName, ConVar));
}

char* CConsole::AddStringVar(char* pVarName, uint32_t VarFlags, char* pInitStr,
								 varFuncType VarChangeFunc)
{
	char* str;
	if (!pInitStr)
	{
		str = new char[1];
		str[0] = 0;
	} 
	else 
	{
		str = new char[strlen(pInitStr)+1];
		strcpy(str, pInitStr);
	}
	AddVar(pVarName, CONSOLE_VARTYPE_STRING, VarFlags, (void*)str, VarChangeFunc);
	return str;
}

char* strrtrim(char* str)
{
	for (int i=strlen(str)-1; i>=0; i--)
	{
		if ((str[i] == ' ') || (str[i] == '\t'))
		{
			str[i] = 0;
		} else {
			break;
		}
	}
	return str;
}

void CConsole::Execute(char* command)
{
	if (command == NULL) return;
	
	char cmdBuf[255];
	strncpy(cmdBuf, command, 255);
	char* cmd = strtok(cmdBuf, " ");

	for (int i=0; i < ARRAY_SIZE(ConsoleCommands); i++)
	{
		if (stricmp(cmd, ConsoleCommands[i].cmdName) == 0)
		{
			if (ConsoleCommands[i].cmdFlags & 1)
			{
				#ifndef _DEBUG
					logprintf("Unable to execute command '%s'. Debug mode required.", ConsoleCommands[i].cmdName);
					return;
				#endif
			}

			ConsoleCommands[i].CmdFunc();
			return;
		}
	}

	consoleVarStruct* ConVar = FindVar(cmd);
	if (ConVar != NULL)
	{
		bool readonly = (ConVar->varFlags & 2) == 2;
		if (ConVar->varFlags & 1)
		{
			#ifndef _DEBUG
				logprintf("Unable to access variable '%s'. Debug mode required.", cmd);
				return;
			#endif
		}
		bool bChangedVar = false;
		char* arg = strtok(NULL, " ");
		switch (ConVar->varType)
		{
			case CONSOLE_VARTYPE_FLOAT:
				if ((arg) && (!readonly))
				{
					*(float*)ConVar->varValue = (float)atof(arg);
					bChangedVar = true;
				} else {
					logprintf("%s = %f  (float%s)", cmd, *(float*)ConVar->varValue, readonly?", read-only":"");
				}
				break;
			case CONSOLE_VARTYPE_INT:
				if ((arg) && (!readonly))
				{
					*(int*)ConVar->varValue = atoi(arg);
					bChangedVar = true;
				} else {
					logprintf("%s = %d  (int%s)", cmd, *(int*)ConVar->varValue, readonly?", read-only":"");
				}
				break;
			case CONSOLE_VARTYPE_BOOL:
				if ((arg) && (!readonly))
				{
					*(bool*)ConVar->varValue = (bool)(atoi(arg) != 0);
					bChangedVar = true;
				} else {
					logprintf("%s = %d  (bool%s)", cmd, *(bool*)ConVar->varValue, readonly?", read-only":"");
				}
				break;
			case CONSOLE_VARTYPE_STRING:
				if ((arg) && (!readonly))
				{
					if (ConVar->varValue != NULL)
						delete [] ConVar->varValue;

					char* str;
					char* ext = strtok(NULL, "");
					if (ext)
					{
						str = (char*)malloc(strlen(arg)+strlen(ext)+2);
						strcpy(str, arg);
						strcat(str, " ");
						strrtrim(ext);
						strcat(str, ext);
					} else {
						str = (char*)malloc(strlen(arg)+1);
						strcpy(str, arg);
					}
					if (strlen(str) > 1023) str[1022] = 0;
					ConVar->varValue = str;
					bChangedVar = true;
				} else {
					logprintf("%s = \"%s\"  (string%s)", cmd, (char*)ConVar->varValue, readonly?", read-only":"");
				}
				break;
		}
		if (bChangedVar)
		{
			if (ConVar->varFunc)
			{
				ConVar->varFunc();
			}
		}
		return;
	}

	if (!__NetGame) return;

	if (!__NetGame->filterscriptsManager->OnRconCommand(command))
	{
		if (__NetGame->gamemodeManager)
		{
			if (!__NetGame->gamemodeManager->OnRconCommand(command))
			{
					logprintf("Unknown command or variable:\n  %s", cmd);
			}
		}
	}
}

void CConsole::SetIntVar(char* pVarName, int intValue)
{
	consoleVarStruct* ConVar = FindVar(pVarName);
	if (ConVar != NULL)
	{
		if (ConVar->varType == CONSOLE_VARTYPE_INT)
			*(int*)ConVar->varValue = intValue;
	}
}

void CConsole::SetBoolVar(char* pVarName, bool boolValue)
{
	consoleVarStruct* ConVar = FindVar(pVarName);
	if (ConVar != NULL)
	{
		if (ConVar->varType == CONSOLE_VARTYPE_BOOL)
			*(bool*)ConVar->varValue = boolValue;
	}
}

float CConsole::GetFloatVar(char* pVarName)
{
	consoleVarStruct* ConVar = FindVar(pVarName);
	if (ConVar != NULL)
	{
		if (ConVar->varType == CONSOLE_VARTYPE_FLOAT)
			return *(float*)ConVar->varValue;
	}
	return 0.0f;
}

void CConsole::SetFloatVar(char* pVarName, float floatValue)
{
	consoleVarStruct* ConVar = FindVar(pVarName);
	if (ConVar != NULL)
	{
		if (ConVar->varType == CONSOLE_VARTYPE_FLOAT)
			*(float*)ConVar->varValue = floatValue;
	}
}

void CConsole::ModifyVarFlags(char* pVarName, uint32_t VarFlags)
{
	consoleVarStruct* ConVar = FindVar(pVarName);
	if (ConVar != NULL)
		ConVar->varFlags = VarFlags;
}

void CConsole::PrintVarList()
{
	char val[1034];
	logprintf("Console Variables:");
	std::map<std::string, consoleVarStruct*>::iterator itor;
	for (itor = varMap.begin(); itor != varMap.end(); itor++)
	{
		val[0] = 0;
		switch (itor->second->varType)
		{
			case CONSOLE_VARTYPE_FLOAT:
				sprintf(val, "%f  (float)", *(float*)itor->second->varValue);
				break;
			case CONSOLE_VARTYPE_INT:
				sprintf(val, "%d  (int)", *(int*)itor->second->varValue);
				break;
			case CONSOLE_VARTYPE_BOOL:
				sprintf(val, "%d  (bool)", *(bool*)itor->second->varValue);
				break;
			case CONSOLE_VARTYPE_STRING:
				sprintf(val, "\"%s\"  (string)", (char*)itor->second->varValue);
				break;
		}
		const char* VarName = itor->first.c_str();
		logprintf("  %s\t%s= %s%s%s%s", VarName, (strlen(VarName)<6)?"\t":"", val,
			(itor->second->varFlags & CONSOLE_VARFLAG_READONLY)?" (read-only)":"",
			(itor->second->varFlags & CONSOLE_VARFLAG_DEBUG)?" (debug)":"",
			(itor->second->varFlags & CONSOLE_VARFLAG_RULE)?" (rule)":"");
	}
	logprintf("");
}

