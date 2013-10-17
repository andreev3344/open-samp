#ifndef __CPVAR_H__
#define __CPVAR_H__

#define MAX_PVARS		800
#define MAX_PVAR_NAME	40

// PVar enumeration
#define PLAYER_VARTYPE_NONE			0
#define PLAYER_VARTYPE_INT			1
#define PLAYER_VARTYPE_STRING		2
#define PLAYER_VARTYPE_FLOAT		3

typedef struct PVAR_DATA_t
{
#pragma pack( 1 )
	char		pVarName[MAX_PVAR_NAME + 1];
	BOOL		isReadOnly;
	uint32_t	pVarType;
	int			intValue;
	float		floatValue;
	char*		stringValue;
} PVAR_DATA;

class CPlayerVar
{
#pragma pack( 1 )
public:

	PVAR_DATA	pVars[MAX_PVARS];
    BOOL		isPVarActive[MAX_PVARS];
	uint32_t	upperIndex;

	CPlayerVar();
	~CPlayerVar();

	int			AddVar(char* varName);
	int			DeleteVar(char* varName);

	int			SetIntVar(char* varName, int varValue, BOOL readOnly = 0);
	int			SetStringVar(char* varName, char* varString, BOOL readOnly = 0);
	int			SetFloatVar(char* varName, float varValue, BOOL readOnly = 0);

	int			GetIntVar(char* varName);
	char*		GetStringVar(char* varName);
	float		GetFloatVar(char* varName);

	int			GetVarType(char* varName);
	char*		GetVarNameFromID(int pVarID);

	int			FindVarID(char* varName);
	void		UpdateUpperID();
};

#endif