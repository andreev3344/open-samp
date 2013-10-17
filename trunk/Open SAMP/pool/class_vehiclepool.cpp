#include "../main.h"


CVehiclePool::CVehiclePool( )
{
	for(_VehicleID vehID = 0; vehID != MAX_VEHICLES; vehID++) {
		this->isCreated[vehID] = FALSE;
		this->vehicles[vehID] = NULL;
		this->vehiclesVirtualWorlds[vehID] = 0;
	}
	memset(&this->modelsUsed[0], 0, NUM_VEHICLE_MODELS);
}

CVehiclePool::~CVehiclePool( )
{
	for(_VehicleID vehID = 0; vehID != MAX_VEHICLES; vehID++)
		this->Delete(vehID);
}

_VehicleID CVehiclePool::New(int vehModel, tVector* vecPos, float vehRot, int vehColor1, int vehColor2, int vehRespawnTime)
{
	_VehicleID vehID;

	if(vehModel < 400 || vehModel > 611) return INVALID_VEHICLE_ID;

	for(vehID = 1; vehID != MAX_VEHICLES; vehID++)
		if(this->isCreated[vehID] == FALSE) break;

	if(vehID == MAX_VEHICLES) return INVALID_VEHICLE_ID;

	// Open SA:MP
	if(this->vehicles[vehID] != NULL) return INVALID_VEHICLE_ID;
	//

	this->vehicles[vehID] = new CVehicle(vehModel, vecPos, vehRot, vehColor1, vehColor2, vehRespawnTime);

	if(this->vehicles[vehID])
	{
		BYTE byteModelIndexArr = (BYTE)(vehModel - 400);
		this->modelsUsed[byteModelIndexArr]++;
		this->vehicles[vehID]->SetID(vehID);
		this->isCreated[vehID] = TRUE;
		this->vehiclesVirtualWorlds[vehID] = 0;

		return vehID;
	}
	else
	{
		return INVALID_VEHICLE_ID;
	}
}

BOOL CVehiclePool::Delete(_VehicleID vehID)
{

	if(!this->GetSlotState(vehID) || !this->GetVehicle(vehID))
		return FALSE;

	int vehModel = this->GetVehicle(vehID)->customSpawn.vehType;
	BYTE byteModelIndexArr = (BYTE)(vehModel - 400);
	this->modelsUsed[byteModelIndexArr]--;

	this->isCreated[vehID] = FALSE;
	delete this->vehicles[vehID];
	this->vehicles[vehID] = NULL;

	return TRUE;
}

void CVehiclePool::Process(float timeElapsed)
{
	for (_VehicleID i=0; i < MAX_VEHICLES; i++) 
	{
		if (this->GetSlotState(i))
			this->GetVehicle(i)->Process(timeElapsed);
	}
}

bool CVehiclePool::GetSlotState( _VehicleID vehicleID )
{
	if( 0 > vehicleID || vehicleID >= MAX_VEHICLES ) return false;

	return (bool)( this->isCreated[ vehicleID ] ? true : false );
}

CVehicle* CVehiclePool::GetVehicle( _VehicleID vehicleID )
{
	if( GetSlotState( vehicleID ) == false ) return (CVehicle*)0;
	return this->vehicles[ vehicleID ];
}

int	CVehiclePool::GetUsedModelsCount()
{
	int iTotalUsedModels = 0;
	int iLoopNumUsed = 0;

	for(int iLoopNumUsed = 0; iLoopNumUsed < NUM_VEHICLE_MODELS; iLoopNumUsed++)
	{
		if(this->modelsUsed[iLoopNumUsed] > 0) iTotalUsedModels++;
	}

	return iTotalUsedModels;
}

_PlayerID CVehiclePool::FindNearestToVehicle(_VehicleID vehicleID)
{
    _PlayerID NearPlayer = INVALID_PLAYER_ID;
	CPlayer *pPlayer = NULL;

	if(!this->GetSlotState(vehicleID)) return INVALID_PLAYER_ID;
	if(!__NetGame->playerPool) return INVALID_PLAYER_ID;

	float fNearestDistance = 100000.0f;
	float fThisDistance = 0.0f;

	for(_PlayerID i = 0; i < MAX_PLAYERS; i++)
	{
		if(__NetGame->playerPool->GetSlotState(i) && !__NetGame->playerPool->isNPC(i)) 
		{
			pPlayer = __NetGame->playerPool->GetPlayer(i);
			if(pPlayer->isActive() && pPlayer->isVehicleStreamedIn(vehicleID))
			{
				fThisDistance = pPlayer->GetDistanceFrom3DPoint(
					this->vehicles[vehicleID]->vehPos.X,
					this->vehicles[vehicleID]->vehPos.Y,
					this->vehicles[vehicleID]->vehPos.Z);

				if(fThisDistance < fNearestDistance) 
				{
					fNearestDistance = fThisDistance;
					NearPlayer = i;
				}
			}
		}
	}

	return NearPlayer;
}

void CVehiclePool::showVehicleForPlayer( _VehicleID vehicleid, _PlayerID playerid )
{
	RakNet::BitStream bStream;
	CVehicle* vehicle = GetVehicle( vehicleid );
	if( vehicle == 0 ) return;

	float angle = 0.0f;
	if( vehicle->vehMatrix.up.X == 0.0f && vehicle->vehMatrix.up.Y == 0.0f || vehicle->GetSpawnInfo()->vehType == 0x219 || vehicle->GetSpawnInfo()->vehType == 0x21A )
	{
		angle = vehicle->GetSpawnInfo()->vehRot;
	}
	else
	{
		angle = atan2( -vehicle->vehMatrix.up.X, vehicle->vehMatrix.up.Y ) * 57.2957763671875f;
		if( angle >= 360.0 ) angle -= 360.0f;
		else if( angle < 0.0f ) angle += 360.0f;
	}

	bStream.Write( ( _VehicleID ) vehicleid );
	bStream.Write( ( uint32_t ) vehicle->GetSpawnInfo( )->vehType );
#ifdef _BIG_ENDIAN_SYSTEM
	bStream.Write(vehicle->vehMatrix.pos.X);
	bStream.Write(vehicle->vehMatrix.pos.Y);
	bStream.Write(vehicle->vehMatrix.pos.Z);
#else
	bStream.Write( (char*)&vehicle->vehMatrix.pos, sizeof( tVector ) );
#endif
	bStream.Write( ( float ) angle );
	bStream.Write( ( uint8_t )vehicle->GetSpawnInfo()->vehColor1 );
	bStream.Write( ( uint8_t )vehicle->GetSpawnInfo()->vehColor2 );
	bStream.Write( ( float ) vehicle->vehHealth );
	bStream.Write( ( uint8_t ) vehicle->GetSpawnInfo()->vehInterior );
	bStream.Write( ( uint32_t ) vehicle->vehDoorStatus );
	bStream.Write( ( uint32_t ) vehicle->vehPanelStatus );
	bStream.Write( ( uint8_t ) vehicle->vehLightStatus );
	bStream.Write( ( uint8_t ) vehicle->vehTireStatus );
#ifdef _BIG_ENDIAN_SYSTEM
	bStream.Write( (char*)&vehicle->vehModInfo.vehModSlots, sizeof(vehicle->vehModInfo.vehModSlots));
	bStream.Write(vehicle->vehModInfo.vehPaintJob);
	bStream.Write(vehicle->vehModInfo.vehColor1);
	bStream.Write(vehicle->vehModInfo.vehColor2);
#else
	bStream.Write( (char*)&vehicle->vehModInfo, sizeof( VEHMOD_INFO ) );
#endif
	__NetGame->PlayerRPC( RPC_ShowVehicleToPlayer, &bStream, playerid, 2 );

	if( strlen( vehicle->vehNumberPlate ) > 0 )
	{
		bStream.Reset( );
		bStream.Write( ( _VehicleID ) vehicleid );
		bStream.Write( ( uint8_t )strlen( vehicle->vehNumberPlate ) );
		bStream.Write( (char*)vehicle->vehNumberPlate, strlen( vehicle->vehNumberPlate ) );
		char* RPC_SetVehicleNumberPlate = 0;
		__NetGame->PlayerRPC( RPC_SetVehicleNumberPlate, &bStream, playerid, 2);
	}

	if ( vehicle->hasParamExModified() )
	{
		bStream.Reset( );
		VEHPARAM_EX* params = vehicle->GetParamsEx();
		bStream.Write( vehicleid );
		bStream.Write( (char*)params, sizeof( VEHPARAM_EX ) );
		__NetGame->PlayerRPC( RPC_SetVehicleParamsEx, &bStream, playerid, 2 );
	}

	uint8_t paramsFlags = vehicle->GetParamsForPlayer( playerid );
	vehicle->SetParamsForPlayer( playerid, paramsFlags & 1, ( paramsFlags & 2 ) ? 1 : 0 ); // Prevent lock/unlocking bug

	vehicle->UpdateVehicleColorForPlayer( playerid ); // prevent unsynced color


}

void CVehiclePool::hideVehicleForPlayer( _VehicleID vehicleid, _PlayerID playerid )
{
	RakNet::BitStream bStream;
	bStream.Write( vehicleid );
	__NetGame->PlayerRPC( RPC_HideVehicleToPlayer, &bStream, playerid, 2);
}


