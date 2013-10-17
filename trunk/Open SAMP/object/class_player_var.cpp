#include "../main.h"

void stringToUpper(char* str)
{
	for(unsigned int i = 0; i < strlen(str); ++i)
        str[i] = (str[i] <= 'z' && str[i] >= 'a') ? str[i] - ('a'-'A') : str[i];
}

CPlayerVar::CPlayerVar()
{
	for(int i=0; i < MAX_PVARS; i++) 
	{
		memset(&pVars[i], NULL, sizeof(PVAR_DATA));
		isPVarActive[i] = 0;
	}

	upperIndex = 0;

}

CPlayerVar::~CPlayerVar()
{
	for(int i=0; i < MAX_PVARS; i++)
	{
		if(isPVarActive[i] && pVars[i].stringValue)
			delete [] pVars[i].stringValue;
		isPVarActive[i] = 0;
	}
}

int CPlayerVar::AddVar(char* varName)
{
	int newSlot = 0;

	for(int i=0; i < MAX_PVARS; i++) 
	{
		if(!isPVarActive[i]) break;
		newSlot++;
	}

	if(newSlot >= MAX_PVARS) return -1;
	if(strlen(varName) > MAX_PVAR_NAME) return -1;
		
	stringToUpper(varName);

	strcpy(pVars[newSlot].pVarName, varName);
    pVars[newSlot].isReadOnly = 0;
	pVars[newSlot].pVarType = PLAYER_VARTYPE_NONE;
	isPVarActive[newSlot] = 1;

	this->UpdateUpperID();

	return newSlot;
}

void CPlayerVar::UpdateUpperID()
{
	uint32_t curSlots=0;

	for(int i=0; i < MAX_PVARS; i++) 
		if(isPVarActive[i]) curSlots = i;

	upperIndex = curSlots + 1;
}

int CPlayerVar::FindVarID(char* varName)
{
	stringToUpper(varName);

	for(uint32_t i=0; i < upperIndex; i++) 
	{
		if(isPVarActive[i]) 
			if(!strcmp(varName, pVars[i].pVarName)) return i;
	}
    return -1;
}

int CPlayerVar::SetIntVar(char* varName, int varValue, BOOL readOnly)
{
    int curSlot = this->FindVarID(varName);
	if(curSlot < 0) {
		curSlot = this->AddVar(varName);
		if(curSlot < 0) return 0;
	}

	if(!readOnly && pVars[curSlot].isReadOnly) return 0;
    if(readOnly) pVars[curSlot].isReadOnly = 1;
    
    pVars[curSlot].pVarType = PLAYER_VARTYPE_INT;
	pVars[curSlot].intValue = varValue;

	return 1;
}

int CPlayerVar::SetStringVar(char* varName, char* varString, BOOL readOnly)
{
	int curSlot = this->FindVarID(varName);
	if(curSlot < 0) {
		curSlot = this->AddVar(varName);
		if(curSlot < 0) return 0;
	}

	if(!readOnly && pVars[curSlot].isReadOnly) return 0;
    if(readOnly) pVars[curSlot].isReadOnly = 1;

    pVars[curSlot].pVarType = PLAYER_VARTYPE_STRING;

	if(pVars[curSlot].stringValue) delete [] pVars[curSlot].stringValue;

	pVars[curSlot].stringValue = new char[strlen(varString) + 1];
    strcpy(pVars[curSlot].stringValue, varString);

	return 1;
}

int CPlayerVar::SetFloatVar(char* varName, float varValue, BOOL readOnly)
{
	int curSlot = this->FindVarID(varName);
	if(curSlot < 0) {
		curSlot = this->AddVar(varName);
		if(curSlot < 0) return 0;
	}

	if(!readOnly && pVars[curSlot].isReadOnly) return 0;
    if(readOnly) pVars[curSlot].isReadOnly = 1;
    
    pVars[curSlot].pVarType = PLAYER_VARTYPE_FLOAT;
	pVars[curSlot].floatValue = varValue;

	return 1;
}

int CPlayerVar::GetIntVar(char* varName)
{
	int curSlot = this->FindVarID(varName);

    if(curSlot < 0) return 0;
	if(pVars[curSlot].pVarType != PLAYER_VARTYPE_INT) return 0;

    return pVars[curSlot].intValue;
}

char* CPlayerVar::GetStringVar(char* varName)
{
    int curSlot = this->FindVarID(varName);

    if(curSlot < 0) return 0;
	if(pVars[curSlot].pVarType != PLAYER_VARTYPE_STRING) return 0;

    return pVars[curSlot].stringValue;
}

float CPlayerVar::GetFloatVar(char* varName)
{
    int curSlot = this->FindVarID(varName);  

    if(curSlot < 0) return 0;
	if(pVars[curSlot].pVarType != PLAYER_VARTYPE_FLOAT) return 0.0;

    return pVars[curSlot].floatValue;
}

int CPlayerVar::DeleteVar(char* varName)
{
	int curSlot = this->FindVarID(varName);    
    
	if(curSlot < 0) return 0;

	if(pVars[curSlot].stringValue) delete [] pVars[curSlot].stringValue;

	memset(&pVars[curSlot], NULL, sizeof(PVAR_DATA));
	isPVarActive[curSlot] = FALSE;

	UpdateUpperID();

	return 1;
}

int	CPlayerVar::GetVarType(char* varName)
{
	int curSlot = this->FindVarID(varName);    
    if(curSlot < 0) return PLAYER_VARTYPE_NONE;

    return pVars[curSlot].pVarType;    
}

char* CPlayerVar::GetVarNameFromID(int pVarID)
{
	if(pVarID < 0 || pVarID >= MAX_PVARS) return 0;
	if(!isPVarActive[pVarID]) return 0;

    return pVars[pVarID].pVarName;  
}