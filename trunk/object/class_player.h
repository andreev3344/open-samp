#ifndef __CPLAYER_H__
#define __CPLAYER_H__

#define MAX_ATTACHED_OBJECT			5

#define PLAYER_STATE_NONE			0
#define PLAYER_STATE_ONFOOT			1
#define PLAYER_STATE_DRIVER			2
#define PLAYER_STATE_PASSENGER		3
#define PLAYER_STATE_WASTED			7
#define PLAYER_STATE_SPAWNED		8
#define PLAYER_STATE_SPECTATING		9

#define SYNCING_TYPE_NONE			0
#define SYNCING_TYPE_ON_FOOT		1
#define SYNCING_TYPE_DRIVER			2
#define SYNCING_TYPE_PASSENGER		3

#define SPECTATE_TYPE_NONE			0

#define RECORD_TYPE_INVEHICLE		1
#define RECORD_TYPE_ONFOOT			2

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


typedef struct AttachedObject_t // size 0x2C
{
#pragma pack( 1 )
	uint32_t	modelID;
	uint32_t	boneID;
	tVector		offset;
	tVector		rotation;
	tVector		scale;
} tAttachedObject;



typedef struct ON_FOOT_SYNC_t // size 0x44
{
#pragma pack( 1 )
	uint16_t			leftRightKeysOnfoot;					// + 0x0000
	uint16_t			updownKeysOnfoot;						// + 0x0002
	uint16_t			keysOnfoot;								// + 0x0004
	tVector				position;								// + 0x0006 -> 0x000E
	tQuaternionVector	quaterRotation;							// + 0x0012 -> 0x001E
	uint8_t				health;									// + 0x0022
	uint8_t				armour;									// + 0x0023
	uint8_t				weapon;									// + 0x0024
	uint8_t				specialAction;							// + 0x0025
	tVector				velocity;								// + 0x0026
	tVector				surfingOffsets;							// + 0x0032
	_VehicleID			surfingVehicleID;						// + 0x003E	
	uint32_t			animationIndex;							// + 0x0040
} ON_FOOT_SYNC;



typedef struct IN_VEHICLE_SYNC_t // size 0x3F
{
#pragma pack( 1 )
	uint16_t	vehicleID;								// + 0x0000
	uint16_t	leftRightKeysOnVehicle;					// + 0x0002
	uint16_t	updownKeysOnVehicle;					// + 0x0004
	uint16_t	keysOnVehicle;							// + 0x0006
	tQuaternionVector rotation;							// + 0x0008
	tVector		position;								// + 0x0018
	tVector		velocity;								// + 0x0024
	float		health;									// + 0x0030
	uint8_t		playerHealth;							// + 0x0034
	uint8_t		playerArmor;							// + 0x0035
	uint8_t		playerWeapon;							// + 0x0036
	uint8_t		sirenType;								// + 0x0037
	uint8_t		gearState;								// + 0x0038
	_VehicleID	trailerID;								// + 0x0039
	union
	{
		uint16_t	hydraReactorAngle[2];					// + 0x003B
		float		trainSpeed;								// + 0x003B
	};
} IN_VEHICLE_SYNC;


typedef struct PASSENGER_SYNC_t // size 0x18
{
#pragma pack( 1 )
	_VehicleID	vehicleID;				// + 0x0000
	uint8_t		seatID;					// + 0x0002
	uint8_t		playerWeapon;			// + 0x0003
	uint8_t		playerHealth;			// + 0x0004
	uint8_t		playerArmour;			// + 0x0005
	uint16_t	leftRightKeysPassenger;	// + 0x0006
	uint16_t	updownKeysPassenger;	// + 0x0008
	uint16_t	passengersKeys;			// + 0x000A
	tVector		position;				// + 0x000C
} PASSENGER_SYNC;

typedef struct AIM_SYNC_t // size 0x1A
{
#pragma pack( 1 )

	uint8_t		unknown0000;			// + 0x0000
	tVector		cameraFrontVector;		// + 0x0001
	tVector		cameraPosition;			// + 0x000D
	uint8_t		unknown00F6[4];			// + 0x0019
	uint8_t		weaponState;			// + 0x001D
	uint8_t		unknown001E;			// + 0x0001E
} AIM_SYNC;

typedef struct SPECTATING_SYNC_t		// size 0x12
{
	uint16_t	leftRightKeysOnSpectating;				// + 0x0000
	uint16_t	updownKeysOnSpectating;					// + 0x0002
	uint16_t	keysOnSpectating;						// + 0x0004
	tVector		position;								// + 0x0006
} SPECTATING_SYNC;

class CPlayer // size 0x1AF8
{
#pragma pack( 1 )
public:

	void Say( char* text, uint8_t len );

	void SendTime( );
	void ShowPlayerAttachedObjectToPlayer( _PlayerID toPlayerID, uint8_t objectID );

	int showForPlayer( _PlayerID playerID );
	void streamInPlayer( _PlayerID playerID );
	void streamOutPlayer( _PlayerID playerID );


	void ProcessStreaming( );
	void CheckKeysUpdate( uint16_t keys );
	void UpdatePosition( float x, float y, float z, bool forceStreamingProces );
	void ProcessOnFootSyncData( ON_FOOT_SYNC* syncData );
	void ProcessOnVehicleSyncData( IN_VEHICLE_SYNC* syncData );
	void ProcessPassengerSyncData( PASSENGER_SYNC* syncData );
//	void ProcessAimingSyncData( AIM_SYNC* syncData );
	void ProcessSpectatingSyncData( SPECTATING_SYNC* syncData );

	
//	bool isObjectStreamedIn( uint16_t objectID ); // Pour le futur streamer.
	bool isPickupStreamedIn( uint16_t pickupID );
	bool isText3DLabelStreamedIn( _Text3DID text3dID );
	bool isPlayerStreamedIn( _PlayerID playerID );
	bool isVehicleStreamedIn( _VehicleID vehicleID );



	int GetWeaponSlot( uint8_t weapon );
	uint16_t getSkillLevel( int skill );
	void setSkillLevel( int skill, uint16_t level );


	int stopNPCRecordingData( );
	int startNPCRecordingData( int recordType, char* recordname );


	void createText3DLabel( uint16_t labelID );
	void destroyText3DLabel( uint16_t labelID );

	float GetDistanceFrom3DPoint( tVector point );
	float GetDistanceFrom3DPoint( float x, float y, float z );

	float getSquaredDistanceFrom3DPoint( tVector position );
	float getSquaredDistanceFrom3DPoint( float x, float y, float z );

	float getDistanceFrom2DPoint( float x, float y );
	float getSquaredDistanceFrom2DPoint( float x, float y );

	bool isInRaceCheckpoint( );
	void setRaceCheckpoint( uint8_t type, tVector position, tVector next_position, float size );
	void showRaceCheckpoint( bool show );

	bool isInCheckpoint( );
	void setCheckpoint( tVector position, float size );
	void showCheckpoint( bool show );

	void	setMyID( _PlayerID playerID );
	uint16_t getCurrentVehicleID( );

	ON_FOOT_SYNC* getOnFootSyncData( );
	tSPAWNS* getCustomSpawn( );
	bool HasCustomSpawn( );

	tVector* getCameraPosition( );
	tVector* getCameraFrontVector( );
	tVector* getPosition( );

	void setPosition( tVector position );
	void setPosition( float x, float y, float z );
	void setPositionFindZ( float x, float y, float z );

	float getFacingAngle( );

	void setState( uint8_t state );
	uint8_t getState( );

	bool isActive( );
	bool isDriving( );
	bool isSpectating( );
	bool isOnFoot( );
	bool isPassenger( );
	bool isWasted( );
	bool isSpawned( );

	float getHealth( );
	void setHealth( float health );

	void Init( );

	CPlayer( );
	~CPlayer( );
private:

	tVector		position;								// + 0x000	- 0x08
	float		health;									// + 0x000C - 12
	float		armour;									// + 0x0010	- 16
	tQuaternionVector	quaterRotation;					// + 0x0014 -> 0x0024
	float		facingAngle;							// + 0x0024 - 36
	BOOL		allowedToTeleport;						// + 0x0028 - 40
	tVector		velocity;								// + 0x002C - 44
	CPlayerText3DLabels* playerText3DLabels;			// + 0x0038 - 56
	uint16_t	myPlayerID;								// + 0x003C - 60
	uint32_t	SyncingDataType;						// + 0x003E - 62

	ON_FOOT_SYNC	onFootSyncData;						// + 0x0042
	IN_VEHICLE_SYNC onVehicleSyncData;					// + 0x0086
	PASSENGER_SYNC	passengerSyncData;					// + 0x00C5
	AIM_SYNC		aimSyncData;						// + 0x00DD
	SPECTATING_SYNC spectatingSyncData;					// + 0x00FC

	uint8_t		unknown010E[0x183-0x10E];				// + 0x010E

//	uint8_t		unknown0183[5][44];						// + 0x0183 -> 0x025F
	tAttachedObject	attachedObject[MAX_ATTACHED_OBJECT];// + 0x0183 -> 0x025F
	BOOL		attachedObjectSlot[MAX_ATTACHED_OBJECT];// + 0x025F -> 0x273

	uint16_t	lastKeysState;							// + 0x0273
	uint32_t	unknown0275;							// + 0x0275
	uint32_t	unknown0279;							// + 0x0279

	uint8_t		unknown027D[0x281-0x27D];				// + 0x027D						

	uint8_t		playerState;							// + 0x0281	- 641
	tVector		checkpointPosition;						// + 0x0282 - 0x28A
	float		checkpointSize;							// + 0x028E
	BOOL		bIsInCheckpoint;						// + 0x0292
	tVector		raceCheckpointPos;						// + 0x0296 - 0x29E
	tVector		nextraceCheckpointPos;					// + 0x02A2 - 2AA
	uint8_t		raceCheckpointType;						// + 0x02AE
	float		raceCheckpointSize;						// + 0x02AF
	BOOL		bIsInRaceCheckpoint;					// + 0x02B3

	uint32_t	unknown02B7;							// + 0x02B7
	bool		bisPlayerStreamedIn[MAX_PLAYERS];		// + 0x02BB
	bool		bisVehicleStreamedIn[MAX_VEHICLES];		// + 0x04AF
	uint8_t		unknown0C7F[400];						// + 0x0C7F
	bool		bisText3DLabelStreamedIn[MAX_TEXT_LABELS];// + 0x0E0F
	bool		bisPickupStreamedIn[LIMIT_MAX_PICKUPS];	// + 0x120F

	uint32_t	StreamedInPlayers;						// + 0x1A0F
	uint32_t	unknown1A13;							// + 0x1A13
	uint32_t	unknown1A17;							// + 0x1A17
	uint32_t	StreamedInText3DLabelsNumber;			// + 0x1A1B

	uint8_t		unknown1A1F[0x1A23-0x1A1F];				// + 0x1A1F

	uint32_t	unknown1A23;							// + 0x1A23
	uint32_t	unknown1A27;							// + 0x1A27

	tVector		unknown1A2B;							// + 0x1A2B

	uint16_t	skillsLevel[11];						// + 0x1A37 -> 0x1A4D
	uint32_t	unknown1A4D;							// + 0x1A4D


	tSPAWNS		customSpawn;							// + 0x1A51

	BOOL		hasCustomSpawn;							// + 0x1A7F
	uint8_t		wantedLevel;							// + 0x1A83 - 6787
	uint8_t		fightingStyle;							// + 0x1A84	- 6788
	uint8_t		currentSeatinVehicle;					// + 0x1A85
	_VehicleID	currentVehicleID;						// + 0x1A86	- 6790
	uint32_t	nickNameColor;							// + 0x1A88
	BOOL		bshowCheckpoint;						// + 0x1A8C
	BOOL		bshowRaceCheckpoint;					// + 0x1A90
	uint32_t	currentInterior;						// + 0x1A94	- 6804
	uint16_t	ammoInSlot[ 13 ];						// + 0x1A98	- 6808

	uint8_t		unknown1AB2[0x1ACC-0x1AB2];				// + 0x1AB2

	uint8_t		weaponInSlot[ 13 ];						// + 0x1ACC	- 6860
	uint8_t		currentWeapon;							// + 0x1AD9
	uint8_t		time;									// + 0x1ADA
	float		gameTime;								// + 0x1ADB
	uint8_t		spectateType;							// + 0x1ADF	- 6879
	uint32_t	spectateID;								// + 0x1AE0
	uint32_t	lastStreaming;							// + 0x1AE4
	uint32_t	NPCRecordingType;						// + 0x1AE8				http://wiki.sa-mp.com/wiki/Recordingtypes
	FILE*		ioFileNPC;								// + 0x1AEC
	uint32_t	lastNPCWritingInFile;					// + 0x1AF0	

	void*		playerVarsClass;						// + 0x1AF4

};




#endif