#ifndef __CVEHICLE_POOL_H__
#define __CVEHICLE_POOL_H__

#define NUM_VEHICLE_MODELS				212

#define TRAIN_PASSENGER_LOCO			538
#define TRAIN_FREIGHT_LOCO				537
#define TRAIN_PASSENGER					570
#define TRAIN_FREIGHT					569
#define TRAIN_TRAM						449

class CVehiclePool
{
#pragma pack( 1 )
public:

	BOOL		isCreated[MAX_VEHICLES];
	CVehicle*	vehicles[MAX_VEHICLES];
	uint32_t	vehiclesVirtualWorlds[MAX_VEHICLES];
	uint8_t		modelsUsed[212];

	_VehicleID	New(int vehModel, tVector* vecPos, float vehRot, int vehColor1, int vehColor2, int vehRespawnTime);
	BOOL		Delete(_VehicleID vehID);

	void		Process(float timeElapsed);

	bool		GetSlotState( _VehicleID playerID );
	CVehicle*	GetVehicle( _VehicleID playerID );

	int			GetUsedModelsCount();
	_PlayerID	FindNearestToVehicle(_VehicleID vehicleID);

	void showVehicleForPlayer( _VehicleID vehicleid, _PlayerID playerid );
	void hideVehicleForPlayer( _VehicleID vehicleid, _PlayerID playerid );

	CVehiclePool( );
	~CVehiclePool( );

private:

};

#endif