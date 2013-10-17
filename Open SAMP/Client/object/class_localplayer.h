#ifndef __CLASS_LOCALPLAYER_H__
#define __CLASS_LOCALPLAYER_H__



#define FUNC_CLOCALPLAYER_SPAWN					0x34B0
#define FUNC_CLOCALPLAYER_TOGGLESPECTATING		0x39B0
#define FUNC_CLOCALPLAYER_SPECTATEPLAYERID		0x3A60
#define FUNC_CLOCALPLAYER_SPECTATEVEHICLEID		0x3A10
//#define FUNC_CLOCALPLAYER_GETCOLORASRGBA		0x3730
//#define FUNC_CLOCALPLAYER_GETCOLORASARGB		0x3750
#define FUNC_CLOCALPLAYER_SETCOLOR				0x3710


enum ENUM_SPACTATE_TYPE
{
	SPECTATE_TYPE_PLAYER = 1,
	SPECTATE_TYPE_VEHICLE
};


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

typedef struct AIM_SYNC_t // size 0x1F
{
#pragma pack( 1 )

	uint8_t		cameraMode;				// + 0x0000
	tVector		cameraFrontVector;		// + 0x0001
	tVector		cameraPosition;			// + 0x000D
	float		aimZaxis;				// + 0x0019
	uint8_t		weaponState;			// + 0x001D
	uint8_t		unknown001E;			// + 0x0001E
} AIM_SYNC;

typedef struct SPECTATING_SYNC_t		// size 0x12
{
#pragma pack( 1 )
	uint16_t	leftRightKeysOnSpectating;				// + 0x0000
	uint16_t	updownKeysOnSpectating;					// + 0x0002
	uint16_t	keysOnSpectating;						// + 0x0004
	tVector		position;								// + 0x0006
} SPECTATING_SYNC;

typedef struct TRAILER_SYNC_t // size 0x32
{
#pragma pack( 1 )

	_VehicleID trailerID;		// + 0x0000
	tVector	roll;				// + 0x0002
	tVector direction;			// + 0x000E
	tVector position;			// + 0x001A
	tVector velocity;			// + 0x0026
} TRAILER_SYNC;

typedef struct UNOCCUPIED_SYNC_t // size 0x43
{
#pragma pack( 1 )

	_VehicleID vehicleID;		// + 0x0000
	uint8_t passengerSlot;		// + 0x0002
	tVector roll;				// + 0x0003
	tVector direction;			// + 0x000F
	tVector position;			// + 0x001B
	tVector velocity;			// + 0x0027
	tVector turnVelocity;		// + 0x0033
	float health;				// + 0x003F
} UNOCCUPIED_SYNC;

class CLocalPlayer
{
#pragma pack( 1 )

public:
	CLocalPlayer()	// Ne doivent pas servir normalement.
	{				//
	}				//
	~CLocalPlayer()	//
	{				//
	}				//
			

	void RequestClass( uint32_t classid );
	void RequestSpawn();
	void SetSpawnInfo( tSPAWNS* spawnInfo );
	void Spawn( );
	void Say( const char* message );
	void ToggleSpectating( BOOL toggle );

	BOOL isSpectating( );
	uint32_t getSpectatingID( );
	void spectatePlayerID( _PlayerID playerID );
	void spectateVehicleID( _VehicleID vehicleID );
	
	uint32_t getColorAsARGB();
	uint32_t getColorAsRGBA();
	void setColor( uint32_t color );
private:

	_VehicleID			currentVehicleID;		// + 0x0000
	_VehicleID			lastVehicleID;			// + 0x0002
	BOOL				bIsActive;				// + 0x0004
	BOOL				bIsWatsed;				// + 0x0008
	CPlayerPed*			sampActor;				// + 0x000C
	ON_FOOT_SYNC		onFootSyncData;			// + 0x0010
	IN_VEHICLE_SYNC		inVehicleSyncData;		// + 0x0054
	PASSENGER_SYNC		passengerSyncData;		// + 0x0093
	AIM_SYNC			aimSyncData;			// + 0x00AB
	TRAILER_SYNC		trailerSyncData;		// + 0x00CA
	uint32_t			currentAnimationIndex;	// + 0x00FC


	tSPAWNS				customSpawnInfo;		// + 0x0233
	BOOL				hasCustomSpawn;			// + 0x0261


	BOOL				bIsSpectating;			// + 0x0271
	uint8_t				playerTeam;				// + 0x0275
	
	uint8_t				spectateMode;			// + 0x02F8
	uint8_t				spectateType;			// + 0x02F9			// 1 - spectating a player, 2 - spactating a vehicle
	uint32_t			spectatingID;			// + 0x02FA
	BOOL				unknown02FE;			// + 0x02FE

	uint32_t			displayZoneNameTicks;	// + 0x0312

};



#endif