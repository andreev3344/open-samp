#ifndef __CVEHICLE_POOL_H__
#define __CVEHICLE_POOL_H__

class CVehiclePool
{
#pragma pack( 1 )
public:

	BOOL		isCreated[MAX_VEHICLES];
	//CVehicle*	vehicles[MAX_VEHICLES];
	void*		vehicles[MAX_VEHICLES];
	uint32_t	vehiclesVirtualWorlds[MAX_VEHICLES];
	uint8_t		modelsUsed[212];

	bool GetSlotState( _VehicleID playerID );
	/*CVehicle**/void* GetVehicle( _VehicleID playerID );

	CVehiclePool( );
	~CVehiclePool( );
private:

};

#endif