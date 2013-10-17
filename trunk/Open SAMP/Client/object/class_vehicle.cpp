#include "../main.h"


void CVehicle::ToggleCollision( bool toggle )
{
	if( toggle )
	{
		*( uint32_t* )( (uint32_t)gtaVehiclePtr + 0x1C ) |= 1; // enable collision
		*( uint32_t* )( (uint32_t)gtaVehiclePtr + 0x40 ) |= 2;
	}
	else
	{
		*( uint32_t* )( (uint32_t)gtaVehiclePtr + 0x1C ) &= 0xFFFFFFFE; // disable collision
		*( uint32_t* )( (uint32_t)gtaVehiclePtr + 0x40 ) &= 0xFFFFFFFD;
	}
}