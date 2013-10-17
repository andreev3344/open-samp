#include "../main.h"



CVehiclePool::CVehiclePool( )
{
}
CVehiclePool::~CVehiclePool( )
{
}

bool CVehiclePool::GetSlotState( _VehicleID vehicleID )
{
	if( 0 > vehicleID || vehicleID >= MAX_VEHICLES ) return false;

	if( isCreated[ vehicleID ] )
		return true;
	return false;

}
CVehicle* CVehiclePool::GetVehicle( _VehicleID vehicleID ) // sampBaseAddr + 0x1120
{
	if( 0 > vehicleID || vehicleID >= MAX_VEHICLES ) return false;
	return this->vehicles[ vehicleID ];
}