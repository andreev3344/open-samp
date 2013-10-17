#ifndef __CLASS_VEHICLE_H__
#define __CLASS_VEHICLE_H__




class CVehicle
{
#pragma pack( 1 )
public:
	CVehicle( );
	~CVehicle( );


	void ToggleCollision( bool toggle );
	uint32_t GetGTAVehicleID( ) { return this->gtaVehicleID; }
	void* GetGtaVehiclePtr() { return this->gtaVehiclePtr; }
	BOOL isVehicleVulnerable( ) { return this->isInvunerable; }

private:

	uint32_t		unknown[ 2 ];		// + 0x0000
	uint32_t		gtaVehicleID;		// + 0x0008 <-- GTA Vehicle ID, not SAMP ID !!

	uint32_t		unknown000C;		// + 0x000C

	void*			gtaVehiclePtr;		// + 0x0010 // à vérifier ici sampBaseAddr + 0x9B380, j'ai reconnu ça grace au **(_DWORD **)(v3 + 0x10) != 0x863C40 et 0x863C40 c'est la vtable sur CPlaceable
	BOOL			isInvunerable;		// + 0x0014

};





#endif