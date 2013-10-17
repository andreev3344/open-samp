#ifndef __CCONSOLE_H__
#define __CCONSOLE_H__

#include <map>
#include <string>

typedef void (*varFuncType)();

#define CONSOLE_VARTYPE_FLOAT	0 
#define CONSOLE_VARTYPE_INT		1
#define CONSOLE_VARTYPE_BOOL	2
#define CONSOLE_VARTYPE_STRING	3

#define CONSOLE_VARFLAG_DEBUG		1
#define CONSOLE_VARFLAG_READONLY	2
#define CONSOLE_VARFLAG_RULE		4
#define CONSOLE_VARFLAG_UNREMOVABLE 8

struct consoleVarStruct
{
	uint32_t varType;
	uint32_t varFlags;
	void* varValue;
	varFuncType varFunc;
};

class CConsole
{
public:

	std::map<std::string, consoleVarStruct*> varMap;

	consoleVarStruct* FindVar(char* pVarName);

	bool RemoveVar( char* pVarName );

	char* GetStringVar(char* pVarName);
	void SetStringVar(char* pVarName, char* pString);

	void AddVar(char* pVarName, uint32_t VarType, uint32_t VarFlags, void* VarPtr, varFuncType VarChangeFunc = NULL);
	char* AddStringVar(char* pVarName, uint32_t VarFlags, char* pInitStr, varFuncType VarChangeFunc = NULL);

	int GetIntVar(char* pVarName);
	void SetIntVar(char* pVarName, int intValue);

	bool GetBoolVar(char* pVarName);
	void SetBoolVar(char* pVarName, bool boolValue);

	float GetFloatVar(char* pVarName);
	void SetFloatVar(char* pVarName, float floatValue);

	void SendRules(char* queryData, SOCKET socket, const sockaddr_in* to, int tolen);
	void Execute(char* command);

	void ModifyVarFlags(char* pVarName, uint32_t VarFlags);

	void PrintVarList();

	CConsole ( );
	~CConsole( );	

};

#endif