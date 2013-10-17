#ifndef __CVEHICLE_H__
#define __CVEHICLE_H__

#define INVALID_VEHICLE_ID 0xFFFF

const uint8_t vehicleComponentTypes[194] = 
{
	0,	0,	0,	0,	1,	1,	2,	3,	5,	5,	5,	1,	1,	4,	0,	0,	0,	3,	6,	6,	6,	6,
	6,	0,	4,	7,	3,	3,	6,	6,	3,	3,	2,	2,	6,	2,	3,	6,	2,	3,	3,	3,	3,	6,
	6,	6,	6,	3,	3,	0,	0,	3,	3,	2,	2,	2,	3,	3,	0,	6,	0,	2,	3,	3,	6,	6,
	6,	2,	2,	3,	3,	3,	3,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	8,	9,
	2,	6,	3,	2,	6,	3,	3,	3,	7,	7,	7,	3,	10,	3,	3,	2,	6,	6,	3,	3,	3,	11,
	11,	1,	1,	6,	6,	10,	10,	10,	3,	3,	3,	3,	3,	10,	3,	10,	6,	6,	2,	6,	2,	2,
	6,	3,	3,	6,	6,	3,	0,	0,	11,	11,	12,	13,	12,	13,	0,	0,	11,	11,	11,	11,	10,	10,
	11,	10,	11,	10,	0,	11,	10,	11,	0,	0,	0,	10,	10,	11,	11,	10,	10,	10,	10,	10,	10,	11,
	10,	11,	11,	10,	11,	10,	10,	11,	11,	10,	11,	11,	10,	10,	10,	10,	11,	11
};

const uint8_t vehicleTypeComponent[194] = 
{
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
	255, 255, 255, 255, 255, 255, 255, 255, 160, 160, 160, 160, 160, 160, 160, 160, 162, 162, 
	162, 162, 162, 162, 162, 162, 175, 175, 175, 165, 165, 165, 165, 165, 165, 165, 165, 165, 
	165, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 159, 159, 159, 159, 159, 159, 159, 
	159, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 158, 158, 
	158, 158, 158, 158, 158, 158, 255, 255, 255, 175, 134, 134, 167, 136, 136, 136, 134, 136,
	136, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 134, 134, 134, 134, 
	134, 134, 136, 167, 167, 167, 167, 167, 176, 176, 176, 176, 160, 160, 160, 160, 255, 255, 
	255, 255, 162, 162, 162, 162, 165, 165, 165, 165, 161, 161, 161, 161, 159, 159, 159, 159, 
	159, 158, 158, 158, 158, 158, 158, 160, 160, 162, 162, 159, 175, 175, 175, 175, 134, 134, 
	134, 136, 136, 136, 136, 134, 167, 167, 167, 167, 176, 176, 176, 176
};

typedef struct VEHSPAWNS_t // size 0x24
{
#pragma pack( 1 )
	uint32_t	vehType;		// + 0x0000
	tVector		vehPos;			// + 0x0004
	float		vehRot;			// + 0x0010
	uint32_t	vehColor1;		// + 0x0014
	uint32_t	vehColor2;		// + 0x0018
	uint32_t	vehRespawnTime;	// + 0x001A
	uint32_t	vehInterior;	// + 0x001E
} tVEHSPAWNS;

typedef struct VEHMOD_INFO
{
#pragma pack( 1 )
	uint8_t vehModSlots[14];		// + 0x0000
	uint8_t vehPaintJob;			// + 0x000E
	uint32_t vehColor1;				// + 0x000F
	uint32_t vehColor2;				// + 0x0010
} VEHMOD_INFO;

typedef struct VEHPARAM_EX
{
#pragma pack ( 1 )

	uint8_t engine;
	uint8_t lights;
	uint8_t alarm;
	uint8_t doors;
	uint8_t bonnet;
	uint8_t boot;
	uint8_t objective;
} VEHPARAM_EX;

class CVehicle // 0xFE
{
#pragma pack( 1 )
public:
	tVector			vehPos;				// + 0x0000
	MATRIX4X4		vehMatrix;			// + 0x000C
	tVector			vehMoveSpeed;		// + 0x004C
	tVector			vehTurnSpeed;		// + 0x0058

	_VehicleID		vehID;				// + 0x0064
	_VehicleID		vehTrailerID;		// + 0x0066
	_PlayerID		vehLastDriverID;	// + 0x0068
	_PlayerID		vehDriverID;		// + 0x006A
	_PlayerID		vehPassengers[7];	// + 0x006C
	uint32_t		vehActive;			// + 0x007A
	uint32_t		vehWasted;			// + 0x007E
	tVEHSPAWNS		customSpawn;		// + 0x0082
	
	float			vehHealth;			// + 0x00A6
	uint32_t		vehDoorStatus;		// + 0x00AA
	uint32_t		vehPanelStatus;		// + 0x00AE
	BYTE			vehLightStatus;		// + 0x00B2
	BYTE			vehTireStatus;		// + 0x00B3

	bool			vehDead;			// + 0x00B4
	VEHMOD_INFO		vehModInfo;			// + 0x00B5
	char			vehNumberPlate[32+1];// + 0x00CC

	VEHPARAM_EX		vehParamEx;			// + 0x00ED
	//uint8_t			unk[7];				// + 0x00ED

	bool			vehDeathNotification;	// + 0x00F4
	bool			vehOccupied;			// + 0x00F5
	uint32_t		vehOccupiedTick;		// + 0x00F6
	uint32_t		vehRespawnTick;			// + 0x00FA

	uint8_t			playersParamsFlags[MAX_PLAYERS]; // + 0x00FE

	CVehicle(uint32_t model, tVector *pos, float rot, uint32_t color1, uint32_t color2, uint32_t respawnTime);
	~CVehicle();

	uint32_t IsActive() { return vehActive; };
	uint32_t IsWasted() { return vehWasted; };

	void SetID(_VehicleID VehicleID) { vehID = VehicleID; };
	tVEHSPAWNS * GetSpawnInfo() { return &customSpawn; };

	void SetParamsEx( VEHPARAM_EX* params );
	VEHPARAM_EX* GetParamsEx( );
	bool hasParamExModified();

	uint8_t GetParamsForPlayer( _PlayerID playerID );
	void SetParamsForPlayer( _PlayerID playerID, uint8_t objective, uint8_t lock );

	void SetVehicleInterior(uint32_t interior) { customSpawn.vehInterior = interior; };
	void SetDead() { vehDead = true; };
	void SetHealth(float health);
	void SetNumberPlate(char* nbplate);
	void CheckForIdleRespawn();
	void Respawn();
	uint32_t IsOccupied();

	void Process(float time);

	bool IsATrainPart();
	bool IsATrainLoco();

	void UpdatePositionForPlayer(_PlayerID playerId, float X, float Y, float Z);

	void UpdateDamage(_PlayerID attackerId, uint32_t panelDamage, uint32_t doorDamage, uint8_t lightDamage, uint8_t tireStatus);
	
	void Repair();

	bool AddVehicleComponent(_PlayerID playerId, uint16_t component);
	void RemoveVehicleComponent(_PlayerID playerId, uint16_t component);
    void SetPaintjob(_PlayerID playerId, uint8_t paintjob);
    void ChangeColor(_PlayerID playerId, uint32_t color1, uint32_t color2);
	bool HasVehicleMods();

	float GetDistanceFromPoint( float X, float Y, float Z );
	float GetSquaredDistanceFromPoint( float X, float Y, float Z );
	float GetSquaredDistance2D_FromPoint( float X, float Y );
   
	void Update(_PlayerID playerId, MATRIX4X4* matrix, float health, _VehicleID trailerID, bool occupied = true);

	void UpdateVehicleColorForPlayer( _PlayerID playerID );
	void GetVehicleColor( uint32_t &color1, uint32_t &color2 );

private:


};




#endif