#ifndef __CLASS_VEHICLEPOOL_H__
#define __CLASS_VEHICLEPOOL_H__



class CVehiclePool
{
#pragma pack( 1 )
public:

	CVehiclePool( );
	~CVehiclePool( );

	bool GetSlotState( _VehicleID vehicleID );
	CVehicle* GetVehicle( _VehicleID vehicleID ); // sampBaseAddr + 0x1120


private:
	uint8_t		unknown0000[ 0x9D6C ];			// + 0x0000

	CVehicle*	vehicles[ MAX_VEHICLES ];		// + 0x9D6C
	BOOL		isCreated[ MAX_VEHICLES ];		// + 0xBCAC


};



#endif