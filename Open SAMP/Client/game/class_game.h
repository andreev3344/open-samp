#ifndef __CLASS_GAME_H__
#define __CLASS_GAME_H__


#define FUNC_CGAME_CREATECHECKPOINT			0x092A00
#define FUNC_CGAME_CREATERACECHECKPOINT		0x092D20


#define CHECKPOINT_COLOR_DEFINITION				501
#define RACECHECKPOINT_COLOR_DEFINITION			503

#define RACECHECKPOINT_COLOR_DEF_ADDR			0x92DB2

class CGame
{
#pragma pack ( 1 )
public:


	CGame( );
	~CGame( );


	void CreateCheckpoint( float posX, float posY, float posZ, float fSize, uint32_t color = 0xAA0000FF );
	void CreateRaceCheckpoint( uint8_t uType, float posX, float posY, float posZ, float nextPosX, float nextPosY, float nextPosZ, float fSize, uint32_t color = 0xAA0000FF );




private:

	uint8_t		unknown0000[0x0C];		// + 0x0000

	tVector		checkpointPos;			// + 0x000C
	float		checkpointSize;			// + 0x0018
	float		unknown001C;			// + 0x001C
	float		unknown0020;			// + 0x0020
	BOOL		hasCheckpoint;			// + 0x0024
	uint32_t	gtaCheckpointID;		// + 0x0028
	tVector		raceCheckpointPos;		// + 0x002C
	tVector		raceCheckpointNextPos;	// + 0x0038
	float		raceCheckpointSize;		// + 0x0044
	uint8_t		raceCheckpointType;		// + 0x0048
	BOOL		hasRaceCheckpoint;		// + 0x0049
	uint32_t	gtaRaceCheckpointID;	// + 0x004D

};






#endif