#include "../main.h"



CGame::CGame( )
{

}

CGame::~CGame( )
{

}


void CGame::CreateCheckpoint( float posX, float posY, float posZ, float fSize, uint32_t color )
{
	( ( uint32_t* )( sampBaseAddr + ArrayRadarColors ) )[ CHECKPOINT_COLOR_DEFINITION*4 ] = color;

	tVector* vecPos = new tVector;
	vecPos->X = posX;
	vecPos->Y = posY;
	vecPos->Z = posZ;
	_asm
	{
		pushad
		mov ecx, this
		mov ebx, FUNC_CGAME_CREATECHECKPOINT
		add ebx, sampBaseAddr

		push fSize
		push vecPos
		call ebx

		popad
	}

	this->hasCheckpoint = TRUE;

	delete vecPos;
	vecPos = 0;
}

void CGame::CreateRaceCheckpoint( uint8_t uType, float posX, float posY, float posZ, float nextPosX, float nextPosY, float nextPosZ, float fSize, uint32_t color )
{

	*( uint16_t *)( sampBaseAddr + RACECHECKPOINT_COLOR_DEF_ADDR ) = RACECHECKPOINT_COLOR_DEFINITION;
	( ( uint32_t* )( sampBaseAddr + ArrayRadarColors ) )[ RACECHECKPOINT_COLOR_DEFINITION*4 ] = color;


	tVector* vecPos = new tVector;
	tVector* vecNextPos = new tVector;
	
	vecPos->X = posX;
	vecPos->Y = posY;
	vecPos->Z = posZ;

	vecNextPos->X = nextPosX;
	vecNextPos->Y = nextPosY;
	vecNextPos->Z = nextPosZ;
	
	_asm
	{
		pushad
		mov ecx, this
		mov ebx, FUNC_CGAME_CREATERACECHECKPOINT
		add ebx, sampBaseAddr

		push fSize
		push vecNextPos
		push vecPos
		push uType
		call ebx

		popad
	}

	this->hasRaceCheckpoint = TRUE;

	delete vecPos;
	vecPos = 0;

	delete vecNextPos;
	vecNextPos = 0;
}
