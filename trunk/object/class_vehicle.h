#ifndef __CVEHICLE_H__
#define __CVEHICLE_H__

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

typedef struct VEHSPAWNS_t // size 0x2E
{
#pragma pack( 1 )
	uint32_t	vehType;
	tVector		vehPos;
	float		vehRot;
	uint32_t	vehColor1;
	uint32_t	vehColor2;
	uint32_t	vehRespawnTime;
	uint32_t	vehInterior;
} tVEHSPAWNS;

typedef struct VEHMOD_INFO
{
#pragma pack( 1 )
	uint8_t vehModSlots[14];
	uint8_t vehPaintJob;
	uint32_t vehColor1;
	uint32_t vehColor2;
} VEHMOD_INFO;

class CVehicle // 0xFE
{
#pragma pack( 1 )
public:
	tVector			vehPos;
	MATRIX4X4		vehMatrix;
	tVector			vehMoveSpeed;
	tVector			vehTurnSpeed;

	_VehicleID		vehID;
	_VehicleID		vehTrailerID;
	_PlayerID		vehLastDriverID;
	_PlayerID		vehDriverID;
	_PlayerID		vehPassengers[7];
	uint32_t		vehActive;
	uint32_t		vehWasted;
	tVEHSPAWNS		customSpawn;
	
	float			vehHealth;
	uint32_t		vehDoorStatus;
	uint32_t		vehPanelStatus;
	BYTE			vehLightStatus;
	BYTE			vehTireStatus;

	bool			vehDead;
	VEHMOD_INFO		vehModInfo;
	char			vehNumberPlate[32+1];

	uint8_t			unk[7];

	bool			vehDeathNotification;
	bool			vehOccupied;
	uint32_t		vehOccupiedTick;
	uint32_t		vehRespawnTick;

	CVehicle(uint32_t model, tVector *pos, float rot, uint32_t color1, uint32_t color2, uint32_t respawnTime);
	~CVehicle();

	uint32_t IsActive() { return vehActive; };
	uint32_t IsWasted() { return vehWasted; };

	void SetID(_VehicleID VehicleID) { vehID = VehicleID; };
	tVEHSPAWNS * GetSpawnInfo() { return &customSpawn; };

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

private:


};




#endif