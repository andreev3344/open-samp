#ifndef __CPLAYER_H__
#define __CPLAYER_H__



class CPlayer // size 0x1AF8
{
#pragma pack( 1 )
public:

	tVector		position;			// + 0x000	- 0x08
	float		health;				// + 0x000C - 12
	float		armour;				// + 0x0010	- 16
	uint32_t	unknown0014;		// + 0x0014
	uint32_t	unknown001C;		// + 0x001C
	uint32_t	unknown0018;		// + 0x0018
	uint32_t	unknown0020;		// + 0x0020
	float		facingAngle;		// + 0x0024
	BOOL		allowedToTeleport;	// + 0x0028 - 40
	uint32_t	unknown002C;		// + 0x002C
	uint32_t	unknown0030;		// + 0x0030
	uint32_t	unknown0034;		// + 0x0034
	uint32_t	unknown0038;		// + 0x0038
	uint16_t	myPlayerID;			// + 0x003C
	uint32_t	unknown003E;		// + 0x003E

	uint16_t	leftRightKeysOnfoot;// + 0x0042
	uint16_t	updownKeysOnfoot;	// + 0x0044
	uint16_t	keysOnfoot;			// + 0x0046

	uint8_t		specialAction;		// + 0x0067


	uint16_t	surfingVehicleID;	// + 0x0080	- 128
	uint16_t	animationIndex;		// + 0x0082

	uint16_t	leftRightKeysOnVehicle;	// + 0x008C
	uint16_t	updownKeysOnVehicle;	// + 0x008A
	uint16_t	keysOnVehicle;			// + 0x0088

	tVector		cameraFrontVector;	// + 0x00DE	- 0xE6
	tVector		cameraPosition;


	uint8_t		weaponState;		// + 0x00FA - 250

	uint16_t	leftRightKeysOnSpectating;	// + 0x00FC
	uint16_t	updownKeysOnSpectating;		// + 0x00FE
	uint16_t	keysOnSpectating;			// + 0x0100

	uint8_t		unknown0183[5][44];	// + 0x0183

	uint16_t	unknown0273;		// + 0x0273
	uint32_t	unknown0275;		// + 0x0275
	uint32_t	unknown0279;		// + 0x0279

	uint32_t	unknown0281;		// + 0x0281
	uint8_t		playerState;		// + 0x0281	- 641
	tVector		checkpointPosition;	// + 0x0282 - 0x28A
	float		checkpointSize;		// + 0x028E
	BOOL		isInCheckpoint;		// + 0x0292

	tVector		raceCheckpointPos;	// + 0x0296 - 0x29E
	tVector		nextraceCheckpointPos;// + 0x02A2 - 2AA
	uint8_t		raceCheckpointType;	// + 0x02AE
	float		raceCheckpointSize;	// + 0x02AF
	BOOL		isInRaceCheckpoint;	// + 0x02B3

	uint32_t	unknown02B7;		// + 0x02B7
	uint8_t		unknown02BB[500];	// + 0x02BB
	uint8_t		unknown04AF[2000];	// + 0x04AF
	uint8_t		unknown0C7F[400];	// + 0x0C7F
	uint8_t		unknown0E0F[1024];	// + 0x0E0F
	uint8_t		unknown120F[2048];	// + 0x120F

	uint32_t	unknown1A0F;		// + 0x1A0F
	uint32_t	unknown1A13;		// + 0x1A13
	uint32_t	unknown1A17;		// + 0x1A17
	uint32_t	unknown1A1B;		// + 0x1A1B


	uint32_t	unknown1A23;		// + 0x1A23
	uint32_t	unknown1A27;		// + 0x1A27
	uint32_t	unknown1A37;		// + 0x1A37
	uint32_t	unknown1A3B;		// + 0x1A3B
	uint32_t	unknown1A3F;		// + 0x1A3F
	uint32_t	unknown1A43;		// + 0x1A43
	uint32_t	unknown1A47;		// + 0x1A47
	uint16_t	unknown1A4B;		// + 0x1A4B
	uint32_t	unknown1A4D;		// + 0x1A4D

	struct							// + 0x1A51
	{
		uint8_t		team;
		uint32_t	skin;
		uint8_t		unkown1A56[39];
	};


	uint16_t	unknown1A7D;		// + 0x1A7D
	uint32_t	unknown1A7F;		// + 0x1A7F
	uint8_t		wantedLevel;		// + 0x1A83 - 6787
	uint8_t		fightingStyle;		// + 0x1A84	- 6788

	uint16_t	currentVehicleID;	// + 0x1A86	- 6790
	uint32_t	nickNameColor;		// + 0x1A88
	BOOL		showCheckpoint;		// + 0x1A8C
	BOOL		showRaceCheckpoint;	// + 0x1A90
	uint32_t	currentInterior;	// + 0x1A94	- 6804
	uint16_t	ammoInSlot[ 12 ];	// + 0x1A98	- 6808
	uint8_t		weaponInSlot[ 12 ]; // + 0x1ACC	- 6860
	uint8_t		unknown1AD9;		// + 0x1AD9
	uint8_t		time;				// + 0x1ADA
	float		gameTime;		// + 0x1ADB
	uint8_t		spectateType;		// + 0x1ADF	- 6879
	uint32_t	spectateID;			// + 0x1AE0
	uint32_t	unknown1AE4;		// + 0x1AE4
	uint32_t	unknown1AE8;		// + 0x1AE8
	uint32_t	unknown1AEC;		// + 0x1AEC

	void*		playerVarsClass;	// + 0x1AF4


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