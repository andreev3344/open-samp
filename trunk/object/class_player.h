#ifndef __CPLAYER_H__
#define __CPLAYER_H__


typedef struct SPAWNS_t // size 0x2E
{
#pragma pack( 1 )
	uint8_t		Team;
	int			Skin;
	uint8_t		unk;
	float		posX;
	float		posY;
	float		posZ;
	float		zAngle;
	int			weapons[ 3 ];
	int			ammo[ 3 ];
} tSPAWNS;


class CPlayer // size 0x1AF8
{
#pragma pack( 1 )
public:

	tVector		position;								// + 0x000	- 0x08
	float		health;									// + 0x000C - 12
	float		armour;									// + 0x0010	- 16
	uint32_t	unknown0014;							// + 0x0014	- 20
	uint32_t	unknown0018;							// + 0x0018	- 24
	uint32_t	unknown001C;							// + 0x001C	- 28
	uint32_t	unknown0020;							// + 0x0020 - 32
	float		facingAngle;							// + 0x0024 - 36
	BOOL		allowedToTeleport;						// + 0x0028 - 40
	tVector		velocity;								// + 0x002C - 44
	uint32_t	unknown0038;							// + 0x0038 - 56
	uint16_t	myPlayerID;								// + 0x003C - 60
	uint32_t	unknown003E;							// + 0x003E - 62
	uint16_t	leftRightKeysOnfoot;					// + 0x0042 - 66
	uint16_t	updownKeysOnfoot;						// + 0x0044 - 68
	uint16_t	keysOnfoot;								// + 0x0046 - 70

	uint8_t		unknown0048[0x67-0x46];					// + 0x0048 - 72	

	uint8_t		specialAction;							// + 0x0067
	
	uint8_t		unknown0068[0x80-0x67];					// + 0x0068

	uint16_t	surfingVehicleID;						// + 0x0080	- 128
	uint16_t	animationIndex;							// + 0x0082
	uint8_t		unknown0084[0x8C-0x82];					// + 0x0084
	uint16_t	leftRightKeysOnVehicle;					// + 0x008C
	uint16_t	updownKeysOnVehicle;					// + 0x008A
	uint16_t	keysOnVehicle;							// + 0x0088

	uint8_t		unknown008A[0xDE-0x88];					// + 0x008A

	tVector		cameraFrontVector;						// + 0x00DE	- 0xE6
	tVector		cameraPosition;							// + 0x00EA - 0xF2

	uint8_t		unknown00F6[0xFA-0xF2];					// + 0x00F6

	uint8_t		weaponState;							// + 0x00FA - 250

	uint16_t	leftRightKeysOnSpectating;				// + 0x00FC
	uint16_t	updownKeysOnSpectating;					// + 0x00FE
	uint16_t	keysOnSpectating;						// + 0x0100

	uint8_t		unknown0102[0x183-0x100];				// + 0x0102

	uint8_t		unknown0183[5][44];						// + 0x0183 -> 0x025F

	uint8_t		unknown0260[0x273-0x25F];				// + 0x0260

	uint16_t	unknown0273;							// + 0x0273
	uint32_t	unknown0275;							// + 0x0275
	uint32_t	unknown0279;							// + 0x0279

	uint8_t		unknown027D[0x281-0x279];				// + 0x027D						

	uint8_t		playerState;							// + 0x0281	- 641
	tVector		checkpointPosition;						// + 0x0282 - 0x28A
	float		checkpointSize;							// + 0x028E
	BOOL		isInCheckpoint;							// + 0x0292
	tVector		raceCheckpointPos;						// + 0x0296 - 0x29E
	tVector		nextraceCheckpointPos;					// + 0x02A2 - 2AA
	uint8_t		raceCheckpointType;						// + 0x02AE
	float		raceCheckpointSize;						// + 0x02AF
	BOOL		isInRaceCheckpoint;						// + 0x02B3

	uint32_t	unknown02B7;							// + 0x02B7
	bool		isPlayerStreamedIn[MAX_PLAYERS];		// + 0x02BB
	bool		isVehicleStreamedIn[2000];				// + 0x04AF
	uint8_t		unknown0C7F[400];						// + 0x0C7F
	uint8_t		unknown0E0F[1024];						// + 0x0E0F
	uint8_t		unknown120F[2048];						// + 0x120F

	uint32_t	unknown1A0F;							// + 0x1A0F
	uint32_t	unknown1A13;							// + 0x1A13
	uint32_t	unknown1A17;							// + 0x1A17
	uint32_t	unknown1A1B;							// + 0x1A1B

	uint8_t		unknown1A1F[0x1A23-0x1A1B];				// + 0x1A1F

	uint32_t	unknown1A23;							// + 0x1A23
	uint32_t	unknown1A27;							// + 0x1A27
	uint32_t	unknown1A37;							// + 0x1A37
	uint32_t	unknown1A3B;							// + 0x1A3B
	uint32_t	unknown1A3F;							// + 0x1A3F
	uint32_t	unknown1A43;							// + 0x1A43
	uint32_t	unknown1A47;							// + 0x1A47
	uint16_t	unknown1A4B;							// + 0x1A4B
	uint32_t	unknown1A4D;							// + 0x1A4D


	tSPAWNS		customSpawn;							// + 0x1A51
	/*struct												// + 0x1A51
	{
		uint8_t		team;
		uint32_t	skin;
		uint8_t		unkown1A56[39];
	};*/


	BOOL		hasCustomSpawn;							// + 0x1A7F
	uint8_t		wantedLevel;							// + 0x1A83 - 6787
	uint8_t		fightingStyle;							// + 0x1A84	- 6788
	uint8_t		currentSeatinVehicle;					// + 0x1A85
	uint16_t	currentVehicleID;						// + 0x1A86	- 6790
	uint32_t	nickNameColor;							// + 0x1A88
	BOOL		bshowCheckpoint;						// + 0x1A8C
	BOOL		bshowRaceCheckpoint;					// + 0x1A90
	uint32_t	currentInterior;						// + 0x1A94	- 6804
	uint16_t	ammoInSlot[ 13 ];						// + 0x1A98	- 6808

	uint8_t		unknown1B7C[0x1ACC-0x1A98];				// + 0x1B7C

	uint8_t		weaponInSlot[ 13 ];						// + 0x1ACC	- 6860
	uint8_t		unknown1AD9;							// + 0x1AD9
	uint8_t		time;									// + 0x1ADA
	float		gameTime;								// + 0x1ADB
	uint8_t		spectateType;							// + 0x1ADF	- 6879
	uint32_t	spectateID;								// + 0x1AE0
	uint32_t	unknown1AE4;							// + 0x1AE4
	uint32_t	unknown1AE8;							// + 0x1AE8
	uint32_t	unknown1AEC;							// + 0x1AEC

	uint8_t		unknown1AF0[0x1AF4-0x1AEC];				// + 0x1AF0

	void*		playerVarsClass;						// + 0x1AF4


	void setRaceCheckpoint( uint8_t type, tVector position, tVector next_position, float size );
	void showRaceCheckpoint( bool show );

	void setCheckpoint( tVector position, float size );
	void showCheckpoint( bool show );


	uint16_t getCurrentVehicleID( );

	tVector* getCameraPosition( );
	tVector* getCameraFrontVector( );
	tVector* getPosition( );

	float getFacingAngle( );
	uint8_t getState( );

	

	float getHealth( );


	CPlayer( );
	~CPlayer( );
private:


};




#endif