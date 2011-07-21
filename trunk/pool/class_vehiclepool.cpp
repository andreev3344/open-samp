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

	return (bool)( this->isCreated[ vehicleID ] ? true : false );
}

/*CVehicle**/void* CVehiclePool::GetVehicle( _VehicleID vehicleID )
{
	if( GetSlotState( vehicleID ) == false ) return (/*CVehicle**/void*)0;


	return this->vehicles[ vehicleID ];
}