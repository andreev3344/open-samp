#include "../main.h"



CPlayer::CPlayer( )
{
	this->myPlayerID			= INVALID_PLAYER_ID;
	this->playerText3DLabels	= 0;
	this->playerVarsClass		= 0;
	this->bIsAnOpenUser			= false;
	Init( );

}

CPlayer::~CPlayer( )
{
	if(this->playerText3DLabels) delete this->playerText3DLabels;
	if(this->playerVarsClass) delete this->playerVarsClass;
}

void CPlayer::setOpenUser( bool openUser )
{
	this->bIsAnOpenUser = openUser;
}

bool CPlayer::isAnOpenUser( )
{
	return this->bIsAnOpenUser;
}

void CPlayer::SendSyncData( )
{
	if( this->hasAplaceToBe ) return;

	RakNet::BitStream bStream;

	if( getState( ) == PLAYER_STATE_ONFOOT && this->SyncingDataType == SYNCING_TYPE_ON_FOOT )
	{
		bStream.Write( ( uint8_t ) ID_PLAYER_SYNC );
		bStream.Write( ( _PlayerID ) this->myPlayerID );

		if( this->onFootSyncData.leftRightKeysOnfoot )
		{
			bStream.Write( true );
			bStream.Write( ( uint16_t ) this->onFootSyncData.leftRightKeysOnfoot );
		}
		else
			bStream.Write( false );

		if( this->onFootSyncData.updownKeysOnfoot )
		{
			bStream.Write( true );
			bStream.Write( ( uint16_t ) this->onFootSyncData.updownKeysOnfoot );
		}
		else
			bStream.Write( false );

		bStream.Write( ( uint16_t ) this->onFootSyncData.keysOnfoot );
#ifdef _BIG_ENDIAN_SYSTEM
		bStream.Write(this->onFootSyncData.position.X);
		bStream.Write(this->onFootSyncData.position.Y);
		bStream.Write(this->onFootSyncData.position.Z);
#else
		bStream.Write( ( char*)&this->onFootSyncData.position, sizeof( tVector ) );
#endif
		bStream.WriteNormQuat( this->onFootSyncData.quaterRotation.W, this->onFootSyncData.quaterRotation.X,
			this->onFootSyncData.quaterRotation.Y, this->onFootSyncData.quaterRotation.Z );

		uint8_t compressedHealthArmour = 0;
		if( this->onFootSyncData.health > 0 && this->onFootSyncData.health < 100 )
			compressedHealthArmour = ( this->onFootSyncData.health / 7 ) << 4;
		else if( this->onFootSyncData.health >= 100 )
			compressedHealthArmour = 0xF0;

		if( this->onFootSyncData.armour > 0 && this->onFootSyncData.armour < 100 )
			compressedHealthArmour |= ( this->onFootSyncData.armour / 7 );
		else if( this->onFootSyncData.armour >= 100 )
			compressedHealthArmour |= 0x0F;

		bStream.Write( ( uint8_t ) compressedHealthArmour );
		bStream.Write( ( uint8_t ) this->onFootSyncData.weapon );
		bStream.Write( ( uint8_t ) this->onFootSyncData.specialAction );

		bStream.WriteVector( this->onFootSyncData.velocity.X, this->onFootSyncData.velocity.Y, this->onFootSyncData.velocity.Z );

		if( this->onFootSyncData.surfingVehicleID )
		{
			bStream.Write( true );
			bStream.Write( this->onFootSyncData.surfingVehicleID );
#ifdef _BIG_ENDIAN_SYSTEM
			bStream.Write(this->onFootSyncData.surfingOffsets.X);
			bStream.Write(this->onFootSyncData.surfingOffsets.Y);
			bStream.Write(this->onFootSyncData.surfingOffsets.Z);
#else
			bStream.Write( (char*)&this->onFootSyncData.surfingOffsets, sizeof( tVector ) );
#endif
		}
		else
			bStream.Write( false );

		if( this->onFootSyncData.animationIndex )
		{
			bStream.Write( true );
			bStream.Write( ( uint32_t ) this->onFootSyncData.animationIndex );
		}
		else 
			bStream.Write( false );


		__NetGame->AddedPlayersPacket(&bStream, this->myPlayerID);

	}
	else if( getState( ) == PLAYER_STATE_DRIVER && this->SyncingDataType == SYNCING_TYPE_DRIVER	)
	{
		bStream.Write( ( uint8_t ) ID_VEHICLE_SYNC );
		bStream.Write( ( _PlayerID ) this->myPlayerID );
		bStream.Write( ( _VehicleID ) this->onVehicleSyncData.vehicleID );

		bStream.Write( ( uint16_t ) this->onVehicleSyncData.leftRightKeysOnVehicle );
		bStream.Write( ( uint16_t ) this->onVehicleSyncData.updownKeysOnVehicle );
		bStream.Write( ( uint16_t ) this->onVehicleSyncData.keysOnVehicle );
		
		bStream.WriteNormQuat( this->onVehicleSyncData.rotation.W, this->onVehicleSyncData.rotation.X, this->onVehicleSyncData.rotation.Y, this->onVehicleSyncData.rotation.Z );
#ifdef _BIG_ENDIAN_SYSTEM
		bStream.Write(this->onVehicleSyncData.position.X);
		bStream.Write(this->onVehicleSyncData.position.Y);
		bStream.Write(this->onVehicleSyncData.position.Z);
#else
		bStream.Write( (char*)&this->onVehicleSyncData.position, sizeof( tVector ) );
#endif
		bStream.WriteVector( this->onVehicleSyncData.velocity.X, this->onVehicleSyncData.velocity.Y, this->onVehicleSyncData.velocity.Z );
		bStream.Write( ( uint16_t ) this->onVehicleSyncData.health );

		uint16_t compressedHealthArmour = 0x00;

		if( this->onVehicleSyncData.playerHealth > 0 && this->onVehicleSyncData.playerHealth < 100 )
			compressedHealthArmour = ( this->onVehicleSyncData.playerHealth / 7 ) << 4;
		else if( this->onVehicleSyncData.playerHealth >= 100 )
			compressedHealthArmour = 0xF0;
		
		if( this->onVehicleSyncData.playerArmor > 0 && this->onVehicleSyncData.playerArmor < 100 )
			compressedHealthArmour |= ( this->onVehicleSyncData.playerArmor / 7 );
		else if( this->onVehicleSyncData.playerArmor >= 100 )
			compressedHealthArmour |= 0x0F;

		bStream.Write( ( uint8_t ) compressedHealthArmour );
		bStream.Write( ( uint8_t ) this->onVehicleSyncData.playerWeapon );

		if( this->onVehicleSyncData.sirenType )
		{
			bStream.Write( true );
		}
		else
			bStream.Write( false );


		if( this->onVehicleSyncData.gearState )
		{
			bStream.Write( true );
		}
		else
			bStream.Write( false );


		if( this->onVehicleSyncData.hydraReactorAngle )
		{
			bStream.Write( true );
			bStream.Write( ( float) this->onVehicleSyncData.trainSpeed );
		}
		else 
			bStream.Write( false );
		
		if( this->onVehicleSyncData.trailerID )
		{
			bStream.Write( true );
			bStream.Write( ( _VehicleID ) this->onVehicleSyncData.trailerID );
		}
		else 
			bStream.Write( false );

		__NetGame->AddedPlayersPacket(&bStream, this->myPlayerID);
	}
	else if( getState( ) == PLAYER_STATE_PASSENGER && this->SyncingDataType == SYNCING_TYPE_PASSENGER )
	{

		bStream.Write( ( uint8_t ) ID_PASSENGER_SYNC );
		bStream.Write( ( _PlayerID ) this->myPlayerID );

		uint16_t old_keys = this->passengerSyncData.passengersKeys;

		if( this->passengerSyncData.playerWeapon == 43 )
			this->passengerSyncData.passengersKeys &= 0xFB;
#ifdef _BIG_ENDIAN_SYSTEM
		bStream.Write(this->passengerSyncData.vehicleID);
		bStream.Write(this->passengerSyncData.seatID);
		bStream.Write(this->passengerSyncData.playerWeapon);
		bStream.Write(this->passengerSyncData.playerHealth);
		bStream.Write(this->passengerSyncData.playerArmour);
		bStream.Write(this->passengerSyncData.leftRightKeysPassenger);
		bStream.Write(this->passengerSyncData.updownKeysPassenger);
		bStream.Write(this->passengerSyncData.passengersKeys);
		bStream.Write(this->passengerSyncData.position.X), bStream.Write(this->passengerSyncData.position.Y), bStream.Write(this->passengerSyncData.position.Z);
#else
		bStream.Write( (char*)&this->passengerSyncData, sizeof( PASSENGER_SYNC ) );
#endif
		this->passengerSyncData.passengersKeys = old_keys;
		__NetGame->AddedPlayersPacket(&bStream, this->myPlayerID);
	}


	if( this->bIsAimUpdated == TRUE )
	{
		bStream.Reset( );
		bStream.Write( ( uint8_t ) ID_AIM_SYNC );
		bStream.Write( ( _PlayerID ) this->myPlayerID );
#ifdef _BIG_ENDIAN_SYSTEM
		bStream.Write(this->aimSyncData.cameraMode);
		bStream.Write(this->aimSyncData.cameraFrontVector.X), bStream.Write(this->aimSyncData.cameraFrontVector.Y), bStream.Write(this->aimSyncData.cameraFrontVector.Z);
		bStream.Write(this->aimSyncData.cameraPosition.X), bStream.Write(this->aimSyncData.cameraPosition.Y), bStream.Write(this->aimSyncData.cameraPosition.Z);
		bStream.Write(this->aimSyncData.aimZaxis);
		bStream.Write(this->aimSyncData.weaponState);
		bStream.Write(this->aimSyncData.unknown001E);
#else
		bStream.Write( (char*)&this->aimSyncData, sizeof( AIM_SYNC ) );
#endif
		__NetGame->AddedPlayersPacket(&bStream, this->myPlayerID);
		this->bIsAimUpdated = FALSE;
	}


	if( this->bIsTrailerUpdated == TRUE )
	{
		bStream.Reset( );
		bStream.Write( ( uint8_t ) ID_TRAILER_SYNC );
		bStream.Write( ( _PlayerID ) this->myPlayerID );
#ifdef _BIG_ENDIAN_SYSTEM
		bStream.Write(this->trailerSyncData.trailerID);
		bStream.Write(this->trailerSyncData.roll.X), bStream.Write(this->trailerSyncData.roll.Y), bStream.Write(this->trailerSyncData.roll.Z);
		bStream.Write(this->trailerSyncData.direction.X), bStream.Write(this->trailerSyncData.direction.Y), bStream.Write(this->trailerSyncData.direction.Z);
		bStream.Write(this->trailerSyncData.position.X), bStream.Write(this->trailerSyncData.position.Y), bStream.Write(this->trailerSyncData.position.Z);
		bStream.Write(this->trailerSyncData.velocity.X), bStream.Write(this->trailerSyncData.velocity.Y), bStream.Write(this->trailerSyncData.velocity.Z);
#else
		bStream.Write( ( char* )&this->trailerSyncData, sizeof( TRAILER_SYNC ) );
#endif
		__NetGame->AddedPlayersPacket(&bStream, this->myPlayerID);
		this->bIsTrailerUpdated = FALSE;
	}

	if( this->bIsUnoccupiedUpdated == TRUE ) 
	{
		bStream.Reset();
		bStream.Write( ( uint8_t ) ID_UNOCCUPIED_SYNC );
		bStream.Write( ( _PlayerID ) this->myPlayerID );
#ifdef _BIG_ENDIAN_SYSTEM
		bStream.Write(this->unoccupiedSyncData.vehicleID);
		bStream.Write(this->unoccupiedSyncData.passengerSlot);
		bStream.Write(this->unoccupiedSyncData.roll.X), bStream.Write(this->unoccupiedSyncData.roll.Y), bStream.Write(this->unoccupiedSyncData.roll.Z);
		bStream.Write(this->unoccupiedSyncData.direction.X), bStream.Write(this->unoccupiedSyncData.direction.Y), bStream.Write(this->unoccupiedSyncData.direction.Z);
		bStream.Write(this->unoccupiedSyncData.position.X), bStream.Write(this->unoccupiedSyncData.position.Y), bStream.Write(this->unoccupiedSyncData.position.Z);
		bStream.Write(this->unoccupiedSyncData.velocity.X), bStream.Write(this->unoccupiedSyncData.velocity.Y), bStream.Write(this->unoccupiedSyncData.velocity.Z);
		bStream.Write(this->unoccupiedSyncData.turnVelocity.X), bStream.Write(this->unoccupiedSyncData.turnVelocity.Y), bStream.Write(this->unoccupiedSyncData.turnVelocity.Z);
		bStream.Write(this->unoccupiedSyncData.health);
#else
		bStream.Write( ( char* )&this->unoccupiedSyncData, sizeof( UNOCCUPIED_SYNC ) );
#endif
		__NetGame->AddedVehiclePacket(&bStream, this->unoccupiedSyncData.vehicleID, this->myPlayerID);
		this->bIsUnoccupiedUpdated = FALSE;
	}	

}

void CPlayer::Init( )
{

	this->SyncingDataType		= SYNCING_TYPE_NONE;
	this->currentVehicleID		= -1;
	this->bIsAimUpdated			= FALSE;
	this->bIsTrailerUpdated		= FALSE;
	this->playerState			= PLAYER_STATE_NONE;
	this->nickNameColor			= 0;
	this->lastKeysState			= 0;
	
	this->position.X =
		this->position.Y =
		this->position.Z		= 0.0f;

	this->quaterRotation.W =
		this->quaterRotation.X =
		this->quaterRotation.Y = 
		this->quaterRotation.Z	= 0.0f;

	this->facingAngle			= 0.0f;
	this->health				= 0.0f;
	this->armour				= 0.0f;
	this->gameTime				= 0.0f;
	this->time					= 0;
	this->wantedLevel			= 0;
	this->allowedToTeleport		= FALSE;
	this->fightingStyle			= 4;
	this->bshowCheckpoint		= FALSE;
	this->bshowRaceCheckpoint	= FALSE;
	this->currentInterior		= 0;
	this->spectateType			= SPECTATE_TYPE_NONE;
	this->spectateID			= -1;

	this->hasAplaceToBe			= FALSE;
	this->timePlaceToBeHasSet	= 0;
	this->bIsInModShop			= 0;

	this->lastStreaming			= __NetGame->GetTime( );

	for( uint8_t i = 0; i < 13; i++ )
	{
		this->weaponInSlot[ i ] = 0;
		this->ammoInSlot[ i ]	= 0;
	}

	int slot = GetWeaponSlot( 0 );
	if ( slot == -1 )
	{
		this->onFootSyncData.weapon = 0;
	}
	else
	{
		this->weaponInSlot[ slot ]	= 0;
		this->currentWeapon			= 0;
	}

	for( uint8_t i = 0; i < 11; i++ ) this->skillsLevel[ i ] = 999;

	memset( ( void* )bisPlayerStreamedIn, 0x00, sizeof( bool ) * MAX_PLAYERS );
	memset( ( void* )bisVehicleStreamedIn, 0x00, sizeof( bool ) * MAX_VEHICLES );
	memset( ( void* )unknown0C7F, 0x00, sizeof( uint8_t ) * 400 );
	memset( ( void* )bisText3DLabelStreamedIn, 0x00, sizeof( bool ) * MAX_TEXT_LABELS );
	memset( ( void* )bisPickupStreamedIn, 0x00, sizeof( bool ) * LIMIT_MAX_PICKUPS );

	this->StreamedInPlayers			= 0;
	this->StreamedInVehicles		= 0;
	this->unknown1A17				= 0;
	this->StreamedInText3DLabelsNumber = 0;
	this->hasCustomSpawn			= FALSE;
	memset( &customSpawn, 0x00, sizeof( tSPAWNS ) );

	this->time						= 0;
	this->gameTime					= 720.0f;
	this->NPCRecordingType			= 0;
	this->ioFileNPC					= 0;
	this->lastMarkerUpdate			= __NetGame->GetTime( );

	if( this->playerText3DLabels )
	{
		delete this->playerText3DLabels;
		this->playerText3DLabels = 0;
	}

	this->playerText3DLabels = new CPlayerText3DLabels( );


	this->velocity.X =
		this->velocity.Y =
		this->velocity.Z			= 0.0f;


	for( uint8_t i = 0; i < MAX_ATTACHED_OBJECT; i++ )
	{
		this->attachedObjectSlot[ i ] = 0;
		memset( &this->attachedObject[ i ], 0x00, sizeof( tAttachedObject ) );
	}
	this->gravity = __NetGame->gravity;
}


float CPlayer::getGravity( )
{
	return gravity;
}

void CPlayer::setGravity( float value )
{
	this->gravity = value;

	RakNet::BitStream bStream;
	bStream.Write ( gravity );
	__NetGame->PlayerRPC( RPC_SetGravity, &bStream, this->myPlayerID ); 
}

void CPlayer::setSyncingType( uint32_t type )
{
	this->SyncingDataType = type;
}

void CPlayer::Say( char* text, uint8_t len )
{
	RakNet::BitStream bStream;
	bStream.Write( ( _PlayerID ) this->myPlayerID );
	bStream.Write( ( uint8_t ) len );
	bStream.Write( ( char*) text, len );


	if( __NetGame->blimitGlobalChatRadius )
	{
		for( _PlayerID playerID = 0; playerID < MAX_PLAYERS; playerID ++ )
		{
			if( this->myPlayerID == playerID ) continue;

			if( __NetGame->playerPool->GetSlotState( playerID ) )
			{
				float distance = __NetGame->playerPool->GetDistanceBetweenPlayers( this->myPlayerID, playerID );
				if( distance <= __NetGame->dlimitGlobalChatRadius )
				{
					__NetGame->PlayerRPC( RPC_AddPlayerMessage, &bStream, playerID, PACKET_STREAM_RPC_TEXT );
				}
			}
		}
		__NetGame->PlayerRPC( RPC_AddPlayerMessage, &bStream, this->myPlayerID, PACKET_STREAM_RPC_TEXT );
	}
	else
	{
		__NetGame->GlobalRPC( RPC_AddPlayerMessage, &bStream, INVALID_PLAYER_ID, PACKET_STREAM_RPC_TEXT );
	}


}

void CPlayer::ToggleClock( bool enable )
{
	this->time = ( uint8_t )( enable ? 1 : 0 );
	RakNet::BitStream bStream;
	bStream.Write( ( uint8_t )( enable ? 1 : 0 ) );
	__NetGame->PlayerRPC( RPC_TogglePlayerClock, &bStream, this->myPlayerID, 2 );
}

void CPlayer::SetTime( uint8_t hour, uint8_t minute )
{
	SendTime( );
	RakNet::BitStream bStream;
	bStream.Write( hour );
	bStream.Write( minute );
	
	__NetGame->PlayerRPC( RPC_SetPlayerTime, &bStream, this->myPlayerID );

	this->gameTime = ( float )hour + 60.0f * ( float )minute;

}

void CPlayer::SendTime( )
{
	
	RakNet::BitStream bStream;
	bStream.Write( ( uint32_t ) __NetGame->GetTime( ) );
	__NetGame->PlayerRPC( RPC_SendTime, &bStream, this->myPlayerID );
}

void CPlayer::ShowPlayerAttachedObjectToPlayer( _PlayerID toPlayerID, uint8_t objectID )
{
	if( 0 > objectID || objectID >= MAX_ATTACHED_OBJECT ) return;

	if( this->attachedObjectSlot[ objectID ] )
	{
		
		RakNet::BitStream bStream;
		bStream.Write( ( uint16_t ) this->myPlayerID );
		bStream.Write( ( uint32_t ) objectID );
		//bStream.sub_465330( );
#ifdef _BIG_ENDIAN_SYSTEM
		bStream.Write(attachedObject[objectID].modelID);
		bStream.Write(attachedObject[objectID].boneID);
		bStream.Write(attachedObject[objectID].offset.X), bStream.Write(attachedObject[objectID].offset.Y), bStream.Write(attachedObject[objectID].offset.Z);
		bStream.Write(attachedObject[objectID].rotation.X), bStream.Write(attachedObject[objectID].rotation.Y), bStream.Write(attachedObject[objectID].rotation.Z);
		bStream.Write(attachedObject[objectID].scale.X), bStream.Write(attachedObject[objectID].scale.Y), bStream.Write(attachedObject[objectID].scale.Z);
#else
		bStream.Write( ( char* ) &attachedObject[ objectID ], sizeof( tAttachedObject ) );
#endif

		__NetGame->PlayerRPC( RPC_AttachAttachedObject, &bStream, toPlayerID, 2 );
	}

}

int CPlayer::showForPlayer( _PlayerID playerID )
{
	RakNet::BitStream bStream;

	bStream.Write( ( uint16_t ) this->myPlayerID ); // <-- une erreur de ...
	bStream.Write( ( uint8_t ) this->customSpawn.Team );
	bStream.Write( this->customSpawn.Skin ); // <-- une erreur de ... (x2)
	bStream.Write( ( tVector ) this->position );
	bStream.Write( ( float ) this->facingAngle );
	bStream.Write( ( uint32_t ) this->nickNameColor );
	bStream.Write( ( uint8_t ) this->fightingStyle );
#ifdef _BIG_ENDIAN_SYSTEM
	for(uint8_t i = 0; i < 11; i++) bStream.Write(skillsLevel[i]);
#else
	bStream.Write( ( char* )skillsLevel, sizeof( uint16_t ) * 11 );
#endif

	__NetGame->PlayerRPC( RPC_spawnPlayerForPlayer, &bStream, playerID, 2 );

	for( uint32_t i = 0; i < MAX_ATTACHED_OBJECT; i++ )
	{
		if( this->attachedObjectSlot[ i ] )
		{
			ShowPlayerAttachedObjectToPlayer( playerID, ( uint8_t )i );
		}

	}

	return 1;
}

void CPlayer::streamInPlayer( _PlayerID playerID )	
{
	if( __NetGame->playerPool )
	{
		if( this->bisPlayerStreamedIn[ playerID ] == 0 )
		{
			__NetGame->playerPool->ShowPlayerForPlayer( playerID, this->myPlayerID );
			// playerPool->sub_47C510( playerID, this->myPlayerID );

			this->bisPlayerStreamedIn[ playerID ] ++;
			this->StreamedInPlayers++;

			if( __NetGame->filterscriptsManager )
				__NetGame->filterscriptsManager->OnPlayerStreamIn( playerID, this->myPlayerID );
			if( __NetGame->gamemodeManager )
				__NetGame->gamemodeManager->OnPlayerStreamIn( playerID, this->myPlayerID );
		}
	

	}

}


void CPlayer::setAttachedObject( uint32_t index, uint32_t model, uint32_t bone, tVector offset, tVector rotation, tVector scale )
{
	if( 0 > index || index >= MAX_ATTACHED_OBJECT ) return;

	attachedObject[ index ].modelID		= model;
	attachedObject[ index ].boneID		= bone;
	attachedObject[ index ].offset		= offset;
	attachedObject[ index ].rotation	= rotation;
	attachedObject[ index ].scale		= scale;

	this->attachedObjectSlot[ index ] = TRUE;

	RakNet::BitStream bStream;
	bStream.Write( ( _PlayerID ) this->myPlayerID );
	bStream.Write( ( uint32_t ) index );
	bStream.Write( ( bool ) true );
#ifdef _BIG_ENDIAN_SYSTEM
	bStream.Write(attachedObject[ index ].modelID);
	bStream.Write(attachedObject[ index ].boneID);
	bStream.Write(attachedObject[ index ].offset.X), bStream.Write(attachedObject[ index ].offset.Y), bStream.Write(attachedObject[ index ].offset.Z);
	bStream.Write(attachedObject[ index ].rotation.X), bStream.Write(attachedObject[ index ].rotation.Y), bStream.Write(attachedObject[ index ].rotation.Z);
	bStream.Write(attachedObject[ index ].scale.X), bStream.Write(attachedObject[ index ].scale.Y), bStream.Write(attachedObject[ index ].scale.Z);
#else
	bStream.Write( ( char* )&attachedObject[ index ], sizeof( tAttachedObject ) );
#endif
	__NetGame->AddedPlayersRPC( RPC_AttachAttachedObject, &bStream, this->myPlayerID, 2 );
	__NetGame->PlayerRPC( RPC_AttachAttachedObject, &bStream, this->myPlayerID, 2 );

}

void CPlayer::removeAttachedObject( uint32_t index )
{
	if( 0 > index || index >= MAX_ATTACHED_OBJECT ) return;

	memset( &this->attachedObject[ index ], 0x00, sizeof( tAttachedObject ) );

	this->attachedObjectSlot[ index ] = FALSE;

	RakNet::BitStream bStream;
	bStream.Write( ( _PlayerID ) this->myPlayerID );
	bStream.Write( ( uint32_t ) index );
	bStream.Write( ( bool ) false );

	__NetGame->AddedPlayersRPC( RPC_AttachAttachedObject, &bStream, this->myPlayerID, 2 );
	__NetGame->PlayerRPC( RPC_AttachAttachedObject, &bStream, this->myPlayerID, 2 );

}

bool CPlayer::IsAttachedObjectSlotUsed( uint32_t index )
{
	if( 0 > index || index >= MAX_ATTACHED_OBJECT ) return false;
	return ( bool )( this->attachedObjectSlot[ index ] != FALSE ? true : false );
}

void CPlayer::streamOutPlayer( _PlayerID playerID )
{
	if( __NetGame->playerPool )
	{

		if( this->bisPlayerStreamedIn[ playerID ] != 0 )
		{
			__NetGame->playerPool->HidePlayerForPlayer( playerID, this->myPlayerID );
			this->bisPlayerStreamedIn[ playerID ] = 0;
			this->StreamedInPlayers--;

			if( __NetGame->filterscriptsManager )
				__NetGame->filterscriptsManager->OnPlayerStreamOut( playerID, this->myPlayerID );
			if( __NetGame->gamemodeManager )
				__NetGame->gamemodeManager->OnPlayerStreamOut( playerID, this->myPlayerID );


		}

	}
}

void CPlayer::UpdatePlayerMarkers()
{
	CPlayer* playerMarker = NULL;
	
	if(__NetGame->showPlayerMarkers != PLAYER_MARKERS_MODE_GLOBAL || !__NetGame->playerPool) return;

	int localplayerVW = __NetGame->playerPool->getPlayerVirtualWorld(this->myPlayerID);
	int remoteplayerVW = 0;
	
	if( (__NetGame->GetTime() - this->lastMarkerUpdate) > MARKER_UPDATE_TICKS ) 
	{
		this->lastMarkerUpdate = __NetGame->GetTime();
		RakNet::BitStream bStream;
		uint32_t playerCount = __NetGame->playerPool->playersCount - 1;

		bStream.Write((uint8_t) ID_PLAYER_MARKERS);
		bStream.Write(playerCount);
        
		short posX, posY, posZ;

		float playerMarkerRadiusSquared = __NetGame->dlimitPlayerMarkerRadius * __NetGame->dlimitPlayerMarkerRadius;
        
		for(_PlayerID i = 0; i < MAX_PLAYERS; i++)
		{
			if((i != this->myPlayerID) && __NetGame->playerPool->GetSlotState(i) && !__NetGame->playerPool->isNPC(i)) 
			{
				playerMarker = __NetGame->playerPool->GetPlayer(i);
				bStream.Write(i);
				remoteplayerVW = __NetGame->playerPool->getPlayerVirtualWorld(i);

				bool isOutsideRadiusLimit = false;
				if( __NetGame->bLimitPlayerMarkerRadius && 
					playerMarker->getDistanceFrom2DPoint(this->position.X, this->position.Y) > playerMarkerRadiusSquared )
				{
					isOutsideRadiusLimit = true;
				}

				if(!playerMarker->isActive() || (localplayerVW != remoteplayerVW) || isOutsideRadiusLimit)
					bStream.Write(false);
	
				else 
				{
					bStream.Write(true);
                    posX = (short)playerMarker->position.X;
					posY = (short)playerMarker->position.Y;
					posZ = (short)playerMarker->position.Z;
					bStream.Write(posX);
					bStream.Write(posY);
					bStream.Write(posZ);
				}
			}
		}

		__NetGame->PlayerPacket(&bStream, this->myPlayerID);
	}
}

void CPlayer::ProcessStreaming( )
{
	CPlayerPool* playerPool = __NetGame->playerPool;
	CVehiclePool* vehiclePool = __NetGame->vehiclePool;
	CText3DLabels* text3dlabelsPool = __NetGame->text3DLabelsPool;
	CPickupPool* pickupsPool = __NetGame->pickupPool;

	uint32_t currentVirtualWorld = 0;

	if( this->myPlayerID < MAX_PLAYERS )
	{
		currentVirtualWorld = playerPool->playersVirtualWorlds[ this->myPlayerID ];
	}
	
	float streamDistance = __Console->GetFloatVar("stream_distance");
	streamDistance *= streamDistance;


	if( vehiclePool == 0 || playerPool == 0 || text3dlabelsPool == 0 || pickupsPool == 0 )
		return;

	this->UpdatePlayerMarkers();


	for( _VehicleID vehicleID = 0; vehicleID < MAX_VEHICLES; vehicleID ++ ) // <-- ici se passent les calculs concernant le streaming des véhicles au joueur
	{
		CVehicle* vehicle = vehiclePool->GetVehicle( vehicleID );
		if( vehicle == 0 ) continue;
		
		if( vehicle->IsActive() && vehicle->GetSpawnInfo( )->vehType != 0x239 && vehicle->GetSpawnInfo( )->vehType != 0x23A )
		{
			
			if( vehicle->GetSquaredDistance2D_FromPoint( position.X, position.Y ) <= streamDistance )
			{
				
				if( isVehicleStreamedIn( vehicleID ) == false )
				{
					streamInVehicle( vehicleID, false );
				}
			}
			else if( this->currentVehicleID == vehicleID ) continue;
			else if( isVehicleStreamedIn( vehicleID ) )
			{
				streamOutVehicle( vehicleID );
			}
		}
		else
		{
			if( isVehicleStreamedIn( vehicleID ) )
			{
				streamOutVehicle( vehicleID );
			}
		}
	}


	for( _PlayerID playerID = 0; playerID < MAX_PLAYERS; playerID ++ ) 
	{
		if( playerID == this->myPlayerID ) continue;
		CPlayer* player = playerPool->GetPlayer( playerID );

		if( player && player->isActive( ) && currentVirtualWorld == playerPool->playersVirtualWorlds[ playerID ] )
		{
			if( player->isPassenger( ) )
			{
				CVehicle* vehicle = 0;
				if( ( vehicle = vehiclePool->GetVehicle( player->currentVehicleID ) ) )
				{
					if( vehicle->GetSquaredDistance2D_FromPoint( player->position.X, player->position.Y ) <= streamDistance )
					{
						if( isPlayerStreamedIn( playerID ) == false ) streamInPlayer( playerID );
					}
					else
					{
						if( isPlayerStreamedIn( playerID ) == true ) streamOutPlayer( playerID );
					}
				}
			}
			else
			{
				if( getSquaredDistanceFrom2DPoint( player->position.X, player->position.Y ) <= streamDistance  )
				{
					if( isPlayerStreamedIn( playerID ) == false ) streamInPlayer( playerID );
				}
				else
				{
					if( isPlayerStreamedIn( playerID ) == true ) streamOutPlayer( playerID );
				}
			}
		}
		else
		{
			streamOutPlayer( playerID );
		}
	}

	for( _Text3DID labelID = 0; labelID < MAX_TEXT_LABELS; labelID++ )
	{
		if( text3dlabelsPool->GetSlotState( labelID ) )
		{

			float squarredDistance = this->getSquaredDistanceFrom3DPoint( text3dlabelsPool->TextLabels[ labelID ].posX, text3dlabelsPool->TextLabels[ labelID ].posY, text3dlabelsPool->TextLabels[ labelID ].posZ );
			if( text3dlabelsPool->TextLabels[ labelID ].attachedToPlayerID != 0xFFFF && this->isPlayerStreamedIn( text3dlabelsPool->TextLabels[ labelID ].attachedToPlayerID ) )
			{
				if( isText3DLabelStreamedIn( labelID ) == false )
					showText3DLabel( labelID );
			}
			else if( text3dlabelsPool->TextLabels[ labelID ].attachedToVehicleID != 0xFFFF && this->isVehicleStreamedIn( text3dlabelsPool->TextLabels[ labelID ].attachedToVehicleID ) )
			{
				if( isText3DLabelStreamedIn( labelID ) == false )
					showText3DLabel( labelID );
			}
			else if( squarredDistance <= text3dlabelsPool->TextLabels[ labelID ].drawDistance * text3dlabelsPool->TextLabels[ labelID ].drawDistance && currentVirtualWorld == text3dlabelsPool->TextLabels[ labelID ].virtualWorld )
			{
				if( this->isText3DLabelStreamedIn( labelID ) == false )
				{
					showText3DLabel( labelID );
				}
			}
			else
			{
				if( this->isText3DLabelStreamedIn( labelID )  )
					hideText3DLabel( labelID );
			}

		}
		else
		{
			if( this->isText3DLabelStreamedIn( labelID ) )
			{
				this->hideText3DLabel( labelID );
			}
		}

	}

	/*
	
	for( uint16_t text3dID = 0; text3dID < MAX_TEXT_LABELS; text3dID++ )
	{
		bool isStreamedIn = isText3DLabelStreamedIn( text3dID );
		if( text3dlabelsPool->isCreated[ text3dID ] == 0 )
		{
			if( isStreamedIn == true )
			{
				this->destroyText3DLabel( text3dID );
				continue;
			}
		}

		if( text3dlabelsPool->TextLabels[ text3dID ].attachedToPlayerID != 0xFFFF )
		{
			if( isPlayerStreamedIn( text3dlabelsPool->TextLabels[ text3dID ].attachedToPlayerID ) )
				this->createText3DLabel( text3dID );
			else
				this->destroyText3DLabel( text3dID );
		}

		if( text3dlabelsPool->TextLabels[ text3dID ].attachedToVehicleID != 0xFFFF )
		{
			if( isVehicleStreamedIn( text3dlabelsPool->TextLabels[ text3dID ].attachedToVehicleID ) )
				this->createText3DLabel( text3dID );
			else
				this->destroyText3DLabel( text3dID );
		}


		if( currentVirtualWorld == text3dlabelsPool->TextLabels[ text3dID ].virtualWorld && getSquaredDistanceFrom3DPoint( text3dlabelsPool->TextLabels[ text3dID ].posX, 
			text3dlabelsPool->TextLabels[ text3dID ].posX, text3dlabelsPool->TextLabels[ text3dID ].posZ ) <= ( text3dlabelsPool->TextLabels[ text3dID ].drawDistance * text3dlabelsPool->TextLabels[ text3dID ].drawDistance ) )
		{
			if( bisText3DLabelStreamedIn[ text3dID ] == 0 ) createText3DLabel( text3dID );
		}
		else
		{
			if( bisText3DLabelStreamedIn[ text3dID ] != 0 ) destroyText3DLabel( text3dID );
		}
	}
	*/



	if( pickupsPool->getPickupCount( ) > 0 )
	{

		for( uint16_t pickupID = 0; pickupID < LIMIT_MAX_PICKUPS; pickupID++ )
		{
			if(pickupsPool->GetSlotState( pickupID )  )
			{
				if( this->getSquaredDistanceFrom3DPoint( pickupsPool->GetPickup( pickupID )->position ) <= streamDistance && currentVirtualWorld == pickupsPool->getVirtualWorld( pickupID )) 
				{
					if( this->isPickupStreamedIn( pickupID ) == false )
						streamInPickup( pickupID );
				}
				else
				{
					if( this->isPickupStreamedIn( pickupID ) ) 
						streamOutPickup( pickupID );
				}
			}
			else
			{
				if( this->isPickupStreamedIn( pickupID ) ) 
					streamOutPickup( pickupID );
			}
		}

	}

}

void CPlayer::SetPlaceToBe( float x, float y, float z ) // ????????????
{
	this->hasAplaceToBe = TRUE;
	this->timePlaceToBeHasSet = __NetGame->GetTime( );

	placeToBe.X = x;
	placeToBe.Y = y;
	placeToBe.Z = z;
}

void CPlayer::UpdatePosition( float x, float y, float z, bool forceStreamingProcess )
{
	this->position.X = x;
	this->position.Y = y;
	this->position.Z = z;


	if( this->hasAplaceToBe == FALSE )
	{
		if( forceStreamingProcess )
		{
			ProcessStreaming( );
		}
		else
		{
			if( __NetGame->GetTime( ) - this->lastStreaming > __Console->GetIntVar("stream_rate") ) // 0x4E6408 = stream_rate
			{
				ProcessStreaming( );
				this->lastStreaming = __NetGame->GetTime( );
			}
		}
	}

	if( __NetGame->GetTime( ) - this->timePlaceToBeHasSet >= 5000 || this->GetDistanceFrom3DPoint( this->placeToBe ) <= __Console->GetFloatVar("stream_distance") ) // 0x4E6404 = stream_distance
	{
		this->hasAplaceToBe = FALSE;
		ProcessStreaming( );
	}

	if( this->bshowCheckpoint )
	{

		if( this->GetDistanceFrom3DPoint( checkpointPosition ) >= this->checkpointSize )
		{
			if( isInCheckpoint( ) )
			{
				this->bIsInCheckpoint = 0;
				__NetGame->filterscriptsManager->OnPlayerLeaveCheckpoint( this->myPlayerID );
				if( __NetGame->gamemodeManager )
					__NetGame->gamemodeManager->OnPlayerLeaveCheckpoint( this->myPlayerID );
			}
		}
		else
		{
			if( isInCheckpoint( ) == false )
			{
				this->bIsInCheckpoint = 1;
				__NetGame->filterscriptsManager->OnPlayerEnterCheckpoint( this->myPlayerID );
				if( __NetGame->gamemodeManager )
					__NetGame->gamemodeManager->OnPlayerEnterCheckpoint( this->myPlayerID );
			}
		}
	}
	if( this->bshowCheckpoint )
	{
		if( this->GetDistanceFrom3DPoint( this->raceCheckpointPos ) >= this->raceCheckpointSize )
		{
			if( this->isInRaceCheckpoint( ) ) 
			{
				this->bIsInRaceCheckpoint = 0;
				__NetGame->filterscriptsManager->OnPlayerLeaveRaceCheckpoint( this->myPlayerID );
				if( __NetGame->gamemodeManager )
					__NetGame->gamemodeManager->OnPlayerLeaveRaceCheckpoint( this->myPlayerID );
			}
		}
		else
		{
			if( this->isInRaceCheckpoint( ) == false )
			{
				this->bIsInRaceCheckpoint = 1;
				__NetGame->filterscriptsManager->OnPlayerEnterRaceCheckpoint( this->myPlayerID );
				if( __NetGame->gamemodeManager )
					__NetGame->gamemodeManager->OnPlayerEnterRaceCheckpoint( this->myPlayerID );
			}
		}
	}

}

void CPlayer::CheckKeysUpdate( uint16_t keys )
{
	if( this->lastKeysState != keys )
	{
		if( __NetGame->filterscriptsManager )
			__NetGame->filterscriptsManager->OnPlayerKeyStateChange( this->myPlayerID, keys, this->lastKeysState );
		if( __NetGame->gamemodeManager )
			__NetGame->gamemodeManager->OnPlayerKeyStateChange( this->myPlayerID, keys, this->lastKeysState );
		this->lastKeysState = keys;
	}


}

uint32_t CPlayer::getInterior( )
{
	return this->currentInterior;
}

int CPlayer::GetAmmoInSlot( int slot )
{
	return this->ammoInSlot[ slot ];
}

int CPlayer::GetWeaponInSlot( int slot )
{
	return this->weaponInSlot[ slot ];
}

int CPlayer::GetCurrentWeapon( )
{
	return this->currentWeapon;
}

int CPlayer::GetWeaponSlot( uint8_t weapon )
{
  int result;

  switch ( weapon )
  {
    case 0:
    case 1:
      result = 0;
      break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      result = 1;
      break;
    case 0x16:
    case 0x17:
    case 0x18:
      result = 2;
      break;
    case 0x19:
    case 0x1A:
    case 0x1B:
      result = 3;
      break;
    case 0x1C:
    case 0x1D:
    case 0x20:
      result = 4;
      break;
    case 0x1E:
    case 0x1F:
      result = 5;
      break;
    case 0x21:
    case 0x22:
      result = 6;
      break;
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
      result = 7;
      break;
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x27:
      result = 8;
      break;
    case 0x29:
    case 0x2A:
    case 0x2B:
      result = 9;
      break;
    case 0xA:
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
      result = 10;
      break;
    case 0x2C:
    case 0x2D:
    case 0x2E:
      result = 11;
      break;
    case 0x28:
      result = 12;
      break;
    default:
      result = -1;
      break;
  }
  return result;
}


void CPlayer::ProcessOnFootSyncData( ON_FOOT_SYNC* syncData )
{
	this->currentVehicleID = 0;
	memcpy( (void*)&this->onFootSyncData, (void*)syncData, sizeof( ON_FOOT_SYNC ) );

	UpdatePosition( this->onFootSyncData.position.X, this->onFootSyncData.position.Y, this->onFootSyncData.position.Z, false );

	this->quaterRotation = syncData->quaterRotation;

	this->SyncingDataType = SYNCING_TYPE_ON_FOOT;

	MATRIX4X4 matrixRotation;
	memset( &matrixRotation, 0x00, sizeof( MATRIX4X4 ) );
	QuaternionToMatrix( &this->quaterRotation, &matrixRotation );

	this->facingAngle = atan2( -matrixRotation.up.X, matrixRotation.up.Y ) * 180.0f/PI; // pas sûr de cette merde

	if( this->facingAngle >= 360.0f ) this->facingAngle -= 360.0f;
	else if( this->facingAngle < 0.0f ) this->facingAngle += 360.0f;



	this->health = ( float ) this->onFootSyncData.health;
	this->armour = ( float ) this->onFootSyncData.armour;

	int slot = GetWeaponSlot( this->onFootSyncData.weapon );
	if( slot == -1 )
	{
		this->onFootSyncData.weapon = 0;
	}
	else
	{
		this->weaponInSlot[ slot ] = this->onFootSyncData.weapon;
		this->currentWeapon = this->onFootSyncData.weapon;
	}
	this->velocity = this->onFootSyncData.velocity;

	this->setState( PLAYER_STATE_ONFOOT );

	CheckKeysUpdate( this->onFootSyncData.keysOnfoot );

	if( this->onFootSyncData.surfingVehicleID != 0 && this->onFootSyncData.surfingVehicleID != 0xFFFF &&
		this->onFootSyncData.surfingVehicleID >= MAX_VEHICLES && this->onFootSyncData.surfingVehicleID < MAX_VEHICLES + LIMIT_MAX_OBJECT )
	{
		if( __NetGame->objectPool )
		{

			if( __NetGame->objectPool->GetSlotState( this->onFootSyncData.surfingVehicleID - MAX_VEHICLES ) == 0 )
			{
				this->onFootSyncData.surfingVehicleID = 0xFFFF;
				this->onFootSyncData.surfingOffsets.X = 
					this->onFootSyncData.surfingOffsets.Y =
					this->onFootSyncData.surfingOffsets.Z = 0.0f;
			}
		}
	}

	if( this->NPCRecordingType == RECORD_TYPE_ONFOOT )
	{
		if( this->ioFileNPC )
		{
			uint32_t timeElapsed = __NetGame->GetTime( ) - this->FirstNPCWritingTime;
			fwrite( &timeElapsed, 4, 1, this->ioFileNPC );
			fwrite( syncData, sizeof( ON_FOOT_SYNC ), 1, this->ioFileNPC );
		}
	}


}



void CPlayer::ProcessOnVehicleSyncData( IN_VEHICLE_SYNC* syncData )
{
	if( __NetGame->vehiclePool )
	{
		if( syncData->vehicleID < MAX_VEHICLES && isVehicleStreamedIn( syncData->vehicleID ) )
		{
			setState( PLAYER_STATE_DRIVER );
			this->SyncingDataType		= SYNCING_TYPE_DRIVER;
			this->currentVehicleID		= syncData->vehicleID;
			this->currentSeatinVehicle	= 0;
			memcpy( &onVehicleSyncData, syncData, sizeof( IN_VEHICLE_SYNC ) );

			UpdatePosition( syncData->position.X, syncData->position.Y, syncData->position.Z, false );

			this->armour = ( float )syncData->playerArmor;
			this->health = ( float )syncData->playerHealth;


			int slot = GetWeaponSlot( syncData->playerWeapon );
			if( slot == -1 )
			{
				this->onFootSyncData.weapon = 0;
			}
			else
			{
				this->weaponInSlot[ slot ] = this->onFootSyncData.weapon;
				this->currentWeapon = this->onFootSyncData.weapon;
			}
		
			
			
			if( this->currentVehicleID < MAX_VEHICLES )
			{
				CVehicle* vehicle = __NetGame->vehiclePool->GetVehicle( this->currentVehicleID );
				MATRIX4X4 matrixRotation;
				memset( &matrixRotation, 0x00, sizeof( MATRIX4X4 ) );
				QuaternionToMatrix( &syncData->rotation, &matrixRotation );

				matrixRotation.pos.X = syncData->position.X;
				matrixRotation.pos.Y = syncData->position.Y;
				matrixRotation.pos.Z = syncData->position.Z;

				vehicle->Update( this->myPlayerID, &matrixRotation, syncData->health, syncData->trailerID, true );
				vehicle->vehMoveSpeed.X = syncData->velocity.X;
				vehicle->vehMoveSpeed.Y = syncData->velocity.Y;
				vehicle->vehMoveSpeed.Z = syncData->velocity.Z;


				if( vehicle->IsATrainLoco( ) )
				{
					for( _VehicleID locoID = 1; locoID < 4; locoID ++ )
					{
						_VehicleID id = locoID + this->currentVehicleID;
						CVehicle* loco = __NetGame->vehiclePool->GetVehicle( id );
						if( loco )
						{
							if( loco->IsATrainPart( ) )
							{
								loco->Update( 0xFFFF, &matrixRotation, syncData->health, syncData->trailerID, true );
							}
						}
					}

				}


			}

		}
		CheckKeysUpdate( this->onVehicleSyncData.keysOnVehicle );

		if( this->NPCRecordingType == RECORD_TYPE_INVEHICLE )
		{
			if( this->currentVehicleID )
			{
				uint32_t time = __NetGame->GetTime( ) - this->FirstNPCWritingTime;
				fwrite( &time, 4, 1, this->ioFileNPC );
				fwrite( syncData, sizeof( IN_VEHICLE_SYNC ), 1, this->ioFileNPC );
			}
		}
	}
	else
	{
		this->SyncingDataType = SYNCING_TYPE_NONE;
	}

}


void CPlayer::ProcessPassengerSyncData( PASSENGER_SYNC* syncData )
{
	CVehiclePool* vehiclePool = __NetGame->vehiclePool;

	this->currentVehicleID = syncData->vehicleID;

	if( vehiclePool )
	{
		if( syncData->vehicleID < MAX_VEHICLES )
		{
			if( vehiclePool->GetSlotState( syncData->vehicleID ) )
			{
				memcpy( &this->passengerSyncData, syncData, sizeof( PASSENGER_SYNC ) );

				CVehicle* vehicle = vehiclePool->GetVehicle( syncData->vehicleID );
				if( vehicle )
					UpdatePosition( vehicle->vehPos.X, vehicle->vehPos.Y, vehicle->vehPos.Z, false );

				this->health = ( float )syncData->playerHealth;
				this->armour = ( float )syncData->playerArmour;

				int slot = GetWeaponSlot( this->onVehicleSyncData.playerWeapon );
				if( slot == -1 )
				{
					this->onFootSyncData.weapon = 0;
				}
				else
				{
					this->weaponInSlot[ slot ] = this->onFootSyncData.weapon;
					this->currentWeapon = this->onFootSyncData.weapon;
				}

				this->SyncingDataType = SYNCING_TYPE_PASSENGER;
				this->currentSeatinVehicle = syncData->seatID & 0x7F;
				CheckKeysUpdate( syncData->passengersKeys );
				setState( PLAYER_STATE_PASSENGER );

			}
		}
	}
}

void CPlayer::ProcessAimingSyncData( AIM_SYNC* syncData )
{
	memcpy( &this->aimSyncData, syncData, sizeof( AIM_SYNC ) );
	bIsAimUpdated = TRUE;
}

void CPlayer::ProcessSpectatingSyncData( SPECTATING_SYNC* syncData )
{
	this->currentVehicleID = 0;
	memcpy( &this->spectatingSyncData, syncData, sizeof( SPECTATING_SYNC ) );

	UpdatePosition( syncData->position.X, syncData->position.Y, syncData->position.Z, false );
	CheckKeysUpdate( syncData->keysOnSpectating );
	setState( PLAYER_STATE_SPECTATING );
}

void CPlayer::ProcessTrailerSyncData( TRAILER_SYNC* syncData )
{
	if( __NetGame->vehiclePool )
	{
		memcpy( &this->trailerSyncData, syncData, sizeof( TRAILER_SYNC ) );
		if( syncData->trailerID < MAX_VEHICLES )
		{		
			CVehicle* trailer = __NetGame->vehiclePool->GetVehicle( syncData->trailerID );
			if( trailer )
			{
				MATRIX4X4 matrix;
				memset( &matrix, 0x00, sizeof( MATRIX4X4 ) );
				matrix.right = trailerSyncData.roll;
				matrix.up = trailerSyncData.direction;
				matrix.pos = trailerSyncData.position;

				trailer->Update( this->myPlayerID, &matrix, 1000.0f, 0xFFFF, true );
				trailer->vehMoveSpeed = trailerSyncData.velocity;

				this->bIsTrailerUpdated = TRUE;
			}
		}
	}
}

void CPlayer::ProcessUnoccupiedSyncData( UNOCCUPIED_SYNC* syncData )
{
	memcpy(&this->unoccupiedSyncData, syncData, sizeof(UNOCCUPIED_SYNC));

	if(!__NetGame->vehiclePool) return;

	if(!__NetGame->vehiclePool->GetSlotState(syncData->vehicleID)) return;
	CVehicle* vehicle = __NetGame->vehiclePool->GetVehicle(syncData->vehicleID);
	
	if(vehicle) 
	{
		MATRIX4X4 mat;
		mat.pos.X = syncData->position.X;
		mat.pos.Y = syncData->position.Y;
		mat.pos.Z = syncData->position.Z;
		memcpy(&mat.up, &syncData->direction, sizeof(tVector));
		memcpy(&mat.right, &syncData->roll, sizeof(tVector));

		if(!syncData->passengerSlot)
		{
			if(!vehicle->IsOccupied() && __NetGame->vehiclePool->FindNearestToVehicle(syncData->vehicleID) == this->myPlayerID)
			{
				vehicle->Update(this->myPlayerID, &mat, syncData->health, INVALID_VEHICLE_ID, false);
				this->bIsUnoccupiedUpdated = TRUE;     

				__NetGame->filterscriptsManager->OnUnoccupiedVehicleUpdate(vehicle->vehID, this->myPlayerID, 0);
				if(__NetGame->gamemodeManager)
					__NetGame->gamemodeManager->OnUnoccupiedVehicleUpdate(vehicle->vehID, this->myPlayerID, 0);
			} 
			else
				this->bIsUnoccupiedUpdated = FALSE;

		} 
		else 
		{
			vehicle->Update(this->myPlayerID, &mat, syncData->health, INVALID_VEHICLE_ID, true);

			__NetGame->filterscriptsManager->OnUnoccupiedVehicleUpdate(vehicle->vehID, this->myPlayerID, syncData->passengerSlot);
				if(__NetGame->gamemodeManager)
					__NetGame->gamemodeManager->OnUnoccupiedVehicleUpdate(vehicle->vehID, this->myPlayerID, syncData->passengerSlot);

			this->bIsUnoccupiedUpdated = TRUE;
		}
	}
}


uint16_t CPlayer::getSkillLevel( int skill )
{
	if( 0 > skill || skill >= 11 ) return 0;
	return this->skillsLevel[ skill ];
}

void CPlayer::setSkillLevel( int skill, uint16_t level )
{
	if( 0 > skill || skill >= 11 ) return;

	

	RakNet::BitStream bStream;

	bStream.Write( ( uint16_t )this->myPlayerID );
	bStream.Write( ( uint32_t )skill );
	bStream.Write( ( uint16_t )this->skillsLevel[ skill ] );

	__NetGame->PlayerRPC( RPC_SetSkillLevel, &bStream, this->myPlayerID, 2 );

	if( this->playerState && this->playerState != PLAYER_STATE_SPECTATING )
	{
		__NetGame->AddedPlayersRPC( RPC_SetSkillLevel, &bStream, this->myPlayerID, 2 );
	}



}

int CPlayer::stopNPCRecordingData( )
{

	if( this->ioFileNPC )
	{
		fclose( this->ioFileNPC );
		this->ioFileNPC = 0;
	}
	this->NPCRecordingType = 0;

	return 1;
}

int CPlayer::startNPCRecordingData( int recordType, char* recordname )
{
	if( this->ioFileNPC )
	{
		fclose( this->ioFileNPC );
	}

	if( recordname != 0 )
	{
		uint32_t recordname_len = strlen( recordname );
		char record[256] = "";
		for( uint32_t i = 0, a = 0; i < recordname_len && a < 256; i++ )
		{
			if( recordname[i] == 0xFF ) break;
			if( recordname[i] != '.' && recordname[i] != '/' && recordname[i] != '\\' )
			{
				record[a] = recordname[i];
				a++;
			}
		}
		char path[ 512 ] = "";
		sprintf( path, "scriptfiles/%s.rec", record );

		this->ioFileNPC = fopen( path, "wb" );
		if( this->ioFileNPC )
		{
			uint32_t version = 0x3E8;
			fwrite( &version, 1, 4, this->ioFileNPC );
			fwrite( &recordType, 1, 4, this->ioFileNPC );
			FirstNPCWritingTime = __NetGame->GetTime( );
		}
		return 1;
	}
	return 0;
}


void CPlayer::showText3DLabel( uint16_t labelID )
{

	if( __NetGame->text3DLabelsPool > 0 )
	{
		__NetGame->text3DLabelsPool->showForPlayer( labelID, this->myPlayerID );
		this->bisText3DLabelStreamedIn[ labelID ] = true;
		this->StreamedInText3DLabelsNumber++;
	}

}

void CPlayer::hideText3DLabel( uint16_t labelID )
{
	if( __NetGame->text3DLabelsPool > 0 )
	{
		__NetGame->text3DLabelsPool->hideForPlayer( labelID, this->myPlayerID );
		this->bisText3DLabelStreamedIn[ labelID ] = false;
		this->StreamedInText3DLabelsNumber--;
	}
}

float CPlayer::GetDistanceFrom3DPoint( tVector point )
{
	return sqrt( this->getSquaredDistanceFrom3DPoint( point.X, point.Y, point.Z ) );
}

float CPlayer::GetDistanceFrom3DPoint( float x, float y, float z )
{

	return sqrt( getSquaredDistanceFrom3DPoint( x, y, z )  );

}

float CPlayer::getSquaredDistanceFrom3DPoint( tVector position )
{
	return getSquaredDistanceFrom3DPoint( position.X, position.Y, position.Z );
}

float CPlayer::getSquaredDistanceFrom3DPoint( float x, float y, float z )
{
	return ( (float) ( this->position.X - x ) * ( this->position.X - x ) +
		( this->position.Y - y ) * ( this->position.Y - y ) +
		( this->position.Z - z ) * ( this->position.Z - z )
		);
}

float CPlayer::getDistanceFrom2DPoint( float x, float y )
{
	return sqrt( getSquaredDistanceFrom2DPoint( x, y ) );
}

float CPlayer::getSquaredDistanceFrom2DPoint( float x, float y )
{
	return ( this->position.X - x ) * ( this->position.X - x ) + ( this->position.Y - y ) * ( this->position.Y - y );
}

void CPlayer::streamInPickup( uint16_t pickupID )
{
	if( 0 > pickupID || pickupID >= LIMIT_MAX_PICKUPS ) return;

	if( __NetGame->pickupPool )
	{
		__NetGame->pickupPool->showForPlayer( pickupID, this->myPlayerID );
		this->bisPickupStreamedIn[ pickupID ] = true;
		StreamedInPickupNumber++;
	}

}

void CPlayer::streamOutPickup( uint16_t pickupID )
{
	if( 0 > pickupID || pickupID >= LIMIT_MAX_PICKUPS ) return;

	if( __NetGame->pickupPool )
	{
		__NetGame->pickupPool->hideForPlayer( pickupID, this->myPlayerID );
		this->bisPickupStreamedIn[ pickupID ] = false;
		StreamedInPickupNumber--;
	}
}

void CPlayer::streamInVehicle( _VehicleID vehicleID, bool check_position )
{
	if ( isVehicleStreamedIn( vehicleID ) == false )
	{
		if ( StreamedInVehicles <= MAX_CLIENT_VEHICLES )
		{
			if ( check_position == true )
			{
				if( __NetGame->vehiclePool->GetVehicle( vehicleID )->GetSquaredDistance2D_FromPoint( position.X, position.Y ) <= *(float*)0x4E6404 * *(float*)0x4E6404 )
				{
					__NetGame->vehiclePool->showVehicleForPlayer( vehicleID, this->myPlayerID );
					bisVehicleStreamedIn[ vehicleID ] = true;
					StreamedInVehicles++;
					if( __NetGame->filterscriptsManager )
						__NetGame->filterscriptsManager->OnVehicleStreamIn( vehicleID, this->myPlayerID );
					if( __NetGame->gamemodeManager )
						__NetGame->gamemodeManager->OnVehicleStreamIn( vehicleID, this->myPlayerID );
				}
			}
			else
			{
				// __NetGame->vehiclePool->sub_47DC30( this->myPlayerID );
				__NetGame->vehiclePool->showVehicleForPlayer( vehicleID, this->myPlayerID );
				bisVehicleStreamedIn[ vehicleID ] = true;
				StreamedInVehicles++;
				if( __NetGame->filterscriptsManager )
					__NetGame->filterscriptsManager->OnVehicleStreamIn( vehicleID, this->myPlayerID );
				if( __NetGame->gamemodeManager )
					__NetGame->gamemodeManager->OnVehicleStreamIn( vehicleID, this->myPlayerID );
			}
		}
	}

}

void CPlayer::streamOutVehicle( _VehicleID vehicleID )
{

	if ( isVehicleStreamedIn( vehicleID ) )
	{
		// __NetGame->vehiclePool->sub_47DF30(a2, this->myPlayerID );
		__NetGame->vehiclePool->hideVehicleForPlayer( vehicleID, this->myPlayerID );
		bisVehicleStreamedIn[ vehicleID ] = false;
		StreamedInVehicles--;
		if( __NetGame->filterscriptsManager )
			__NetGame->filterscriptsManager->OnVehicleStreamOut( vehicleID, this->myPlayerID );
		if( __NetGame->gamemodeManager )
			__NetGame->gamemodeManager->OnVehicleStreamOut( vehicleID, this->myPlayerID );
	}


}

bool CPlayer::isPlayerStreamedIn( _PlayerID playerID )
{

	if( 0 > playerID || playerID >= MAX_PLAYERS ) return false;
	return this->bisPlayerStreamedIn[ playerID ];
}

bool CPlayer::isVehicleStreamedIn( _VehicleID vehicleID )
{
	if( 0 > vehicleID || vehicleID >= MAX_VEHICLES ) return false;
	return this->bisVehicleStreamedIn[ vehicleID ];
}

bool CPlayer::isPickupStreamedIn( uint16_t pickupID )
{
	if( 0 > pickupID || pickupID >= LIMIT_MAX_PICKUPS ) return false;
	return this->bisPickupStreamedIn[ pickupID ];
}
bool CPlayer::isText3DLabelStreamedIn( _Text3DID text3dID )
{
	if( 0 > text3dID  || text3dID  >= MAX_TEXT_LABELS ) return false;
	return this->bisText3DLabelStreamedIn[ text3dID ];
}

bool CPlayer::isInRaceCheckpoint( )
{
	return ( this->bIsInRaceCheckpoint > 0 ? true : false );
}

void CPlayer::setRaceCheckpoint( uint8_t type, tVector position, tVector next_position, float size, uint32_t color )
{
	raceCheckpointPos = position;
	nextraceCheckpointPos = next_position;
	raceCheckpointType = type;
	raceCheckpointSize = size;
	raceCheckpointColor = color;

	showRaceCheckpoint( true );

}

void CPlayer::showRaceCheckpoint( bool show )
{
	bshowRaceCheckpoint = (BOOL)(show ? 1 : 0 );
	bIsInRaceCheckpoint = 0;

	char* RPC_ShowOrHideThatIsTheQuestion = 0x00;
	RakNet::BitStream bStream;

	if( show )
	{
		
		RPC_ShowOrHideThatIsTheQuestion = RPC_ShowRaceCheckpoint;
		bStream.Write( (uint8_t)this->raceCheckpointType );
		bStream.Write( (float)this->raceCheckpointPos.X );
		bStream.Write( (float)this->raceCheckpointPos.Y );
		bStream.Write( (float)this->raceCheckpointPos.Z );
		bStream.Write( (float)this->nextraceCheckpointPos.X );
		bStream.Write( (float)this->nextraceCheckpointPos.Y );
		bStream.Write( (float)this->nextraceCheckpointPos.Z );
		bStream.Write( (float)this->raceCheckpointSize );
		if( isAnOpenUser() )
			bStream.Write( raceCheckpointColor );
	}
	else
	{
		RPC_ShowOrHideThatIsTheQuestion = RPC_HideRaceCheckpoint;
	}
	__NetGame->PlayerRPC( RPC_ShowOrHideThatIsTheQuestion, &bStream, this->myPlayerID, 2 );
}

bool CPlayer::isInCheckpoint( )
{
	return ( this->bIsInCheckpoint > 0 ? true : false );
}

void CPlayer::setCheckpoint( tVector position, float size, uint32_t color )
{
	checkpointPosition = position;
	checkpointSize = size;
	checkpointColor = color;
	showCheckpoint( true );
}

void CPlayer::showCheckpoint( bool show )
{
	this->bshowCheckpoint = (BOOL)( show ? 1 : 0 );
	this->bIsInCheckpoint = 0;

	char* RPC_ShowOrHideThatIsTheQuestion = 0x00;
	RakNet::BitStream bStream;

	if( show )
	{
		bStream.Write( (float)checkpointPosition.X );
		bStream.Write( (float)checkpointPosition.Y );
		bStream.Write( (float)checkpointPosition.Z );
		bStream.Write( (float)checkpointSize );

		if( isAnOpenUser( ) )
			bStream.Write( checkpointColor );

		RPC_ShowOrHideThatIsTheQuestion = RPC_ShowCheckpoint;

	}
	else
	{
		RPC_ShowOrHideThatIsTheQuestion = RPC_HideCheckpoint;
	}

	__NetGame->PlayerRPC( RPC_ShowOrHideThatIsTheQuestion, &bStream, this->myPlayerID, 2 );

}
void CPlayer::setCurrentVehicleID( _VehicleID vehicleID )
{
	this->currentVehicleID = vehicleID;
}

void CPlayer::setCurrentSeatID( uint8_t seatID )
{
	this->currentSeatinVehicle = seatID;
}

uint16_t CPlayer::getCurrentVehicleID( )
{
	return this->currentVehicleID;
}

uint8_t CPlayer::getCurrentVehicleSeatID( )
{
	return this->currentSeatinVehicle;
}

ON_FOOT_SYNC* CPlayer::getOnFootSyncData( )
{
	return &this->onFootSyncData;
}

IN_VEHICLE_SYNC* CPlayer::getInVehicleSyncData( )
{
	return &this->onVehicleSyncData;
}

PASSENGER_SYNC* CPlayer::getPassengerSyncData( )
{
	return &this->passengerSyncData;
}

AIM_SYNC* CPlayer::getAimSyncData( )
{
	return &this->aimSyncData;
}

SPECTATING_SYNC* CPlayer::getSpectatingSyncData( )
{
	return &this->spectatingSyncData;
}

bool CPlayer::HasCustomSpawn( )
{
	return ( bool )( this->hasCustomSpawn ? true : false );
}

tSPAWNS* CPlayer::getCustomSpawn( )
{
	return &this->customSpawn;
}

void CPlayer::setColor( uint32_t color )
{
	this->nickNameColor = color;
	RakNet::BitStream bStream;
	bStream.Write( ( _PlayerID ) this->myPlayerID );
	bStream.Write( ( uint32_t ) color );

	__NetGame->GlobalRPC( RPC_SetPlayerColor, &bStream, this->myPlayerID, 2 );
}

uint32_t CPlayer::getColor( )
{
	return this->nickNameColor;
}

tVector* CPlayer::getCameraPosition( )
{
	return &this->aimSyncData.cameraPosition;
}

tVector* CPlayer::getCameraFrontVector( )
{
	return &this->aimSyncData.cameraFrontVector;
}

float CPlayer::getFacingAngle( )
{
	return this->facingAngle;
}

void CPlayer::setState( uint8_t state )
{
	if( state != this->playerState )
	{
		uint8_t lastState = this->playerState;
		this->playerState = state;

		if( __NetGame->filterscriptsManager )
			__NetGame->filterscriptsManager->OnPlayerStateChange( this->myPlayerID, state, lastState );
		if( __NetGame->gamemodeManager )
			__NetGame->gamemodeManager->OnPlayerStateChange( this->myPlayerID, state, lastState );
	}
	
}

void CPlayer::setMyID( _PlayerID playerID )
{
	this->myPlayerID = playerID;
	this->playerText3DLabels->setOwnerID( playerID );
	playerKeysBind = new CKeyBinder( playerID );
}

uint8_t CPlayer::getState( )
{
	return this->playerState;
}


bool CPlayer::isActive( )
{
	if( getState( ) != PLAYER_STATE_NONE && getState( ) != PLAYER_STATE_SPECTATING) return true;
	return false;
}


bool CPlayer::isDriving( )
{
	if( getState( ) == PLAYER_STATE_DRIVER ) return true;
	return false;
}

bool CPlayer::isSpectating( )
{
	if( getState( ) == PLAYER_STATE_SPECTATING ) return true;
	return false;
}

bool CPlayer::isOnFoot( )
{
	if( getState( ) == PLAYER_STATE_ONFOOT ) return true;
	return false;
}

bool CPlayer::isPassenger( )
{
	if( getState( ) == PLAYER_STATE_PASSENGER ) return true;
	return false;
}

bool CPlayer::isWasted( )
{
	if( getState( ) == PLAYER_STATE_WASTED ) return true;
	return false;
}

bool CPlayer::isSpawned( )
{
	if( getState( ) == PLAYER_STATE_SPAWNED ) return true;
	return false;
}

void CPlayer::setWantedLevel( uint8_t level )
{
	this->wantedLevel = level;
}

uint8_t CPlayer::getWantedLevel( )
{
	return this->wantedLevel;
}

void CPlayer::setFightingStyle( uint8_t style )
{
	this->fightingStyle = style;
}

uint8_t CPlayer::getFightingStyle( )
{
	return this->fightingStyle;
}

float CPlayer::getHealth( )
{
	return this->health;
}

void CPlayer::setHealth( float health )
{
	
	RakNet::BitStream bStream;
	bStream.Write( ( float ) health );
	__NetGame->PlayerRPC( RPC_SetPlayerHealth, &bStream, this->myPlayerID, 2 );
}

float CPlayer::getArmour( )
{
	return this->armour;
}

void CPlayer::allowTeleport( BOOL value )
{
	allowedToTeleport = value;
}

tVector* CPlayer::getPosition( )
{
	return &this->position;
}

tVector* CPlayer::getVelocity( )
{
	return &this->velocity;
}

void CPlayer::setPosition( tVector position )
{
	setPosition( position.X, position.Y, position.Z );
}

void CPlayer::setPosition( float x, float y, float z )
{
	RakNet::BitStream bStream;

	bStream.Write( ( float ) x );
	bStream.Write( ( float ) y );
	bStream.Write( ( float ) z );

	__NetGame->PlayerRPC( RPC_SetPlayerPosition, &bStream, this->myPlayerID, 2 );
}

void CPlayer::setPositionFindZ( float x, float y, float z )
{
	
	RakNet::BitStream bStream;

	bStream.Write( ( float ) x );
	bStream.Write( ( float ) y );
	bStream.Write( ( float ) z );

	__NetGame->PlayerRPC( RPC_SetPlayerPositionFindZ, &bStream, this->myPlayerID, 2 );
}

void CPlayer::setSpectateID( uint32_t ID )
{
	this->spectateID = ID;
}

void CPlayer::setSpectatingType( uint8_t type )
{
	this->spectateType = type;
}

void CPlayer::setCustomSpawn(tSPAWNS* playerSpawn)
{
	memcpy(this->getCustomSpawn(), playerSpawn, sizeof(tSPAWNS));
	this->hasCustomSpawn = 1;
}

void CPlayer::Spawn()
{   
	if(this->hasCustomSpawn) 
	{
		for(uint16_t i = 0; i < MAX_PLAYERS; i++)
		{
			if(i != this->myPlayerID && __NetGame->playerPool->GetSlotState(i)) 
			{
				if(__NetGame->playerPool->GetPlayer(i) && __NetGame->playerPool->GetPlayer(i)->isPlayerStreamedIn(this->myPlayerID)) 
				{
				    __NetGame->playerPool->GetPlayer(i)->streamOutPlayer(this->myPlayerID);
				}
		
			}
		}

		for(uint8_t i = 0; i < MAX_ATTACHED_OBJECT; i++)
		{
			if(this->IsAttachedObjectSlotUsed(i))
			{
				this->removeAttachedObject(i);
			}
		}
		
		this->getOnFootSyncData()->position.X = this->customSpawn.posX;
		this->getOnFootSyncData()->position.Y = this->customSpawn.posY;
		this->getOnFootSyncData()->position.Z = this->customSpawn.posZ;

		this->getPosition()->X = this->customSpawn.posX;
		this->getPosition()->Y = this->customSpawn.posY;
		this->getPosition()->Z = this->customSpawn.posZ;

		this->currentVehicleID = 0;

		uint8_t weaponSlot = this->GetWeaponSlot(0);
		if ( weaponSlot == -1 )
			this->getOnFootSyncData()->weapon = 0;
		else
		{
			this->SetWeaponInSlot(weaponSlot, 0);
			this->SetCurrentWeapon(0);
		}


		this->setState(PLAYER_STATE_SPAWNED);	
	}
}


void CPlayer::Process(float time)
{
	static float fLastSync = 0.0;
	this->gameTime += time;

	if(this->isActive()) 
	{

		if(this->SyncingDataType != UPDATE_TYPE_NONE)  
		{
			this->SendSyncData();
			this->SyncingDataType = UPDATE_TYPE_NONE;
		}
		
		if (this->time)
		{
			if (this->gameTime - fLastSync >= 300.0f)
			{
				if (this->gameTime >= 1440.0f) this->gameTime -= 1440.0f;
				fLastSync = this->gameTime;
				int iTime;
				iTime = (int)(this->gameTime);

				RakNet::BitStream bsPlayerTime;

				bsPlayerTime.Write((BYTE)(iTime / 60));
				bsPlayerTime.Write((BYTE)(iTime % 60));
				__NetGame->PlayerRPC( RPC_SetTimeEx, &bsPlayerTime, this->myPlayerID, 2 );
			}
		}
	}	
}

void CPlayer::HandleDeath(uint8_t deathReason, _PlayerID killerID )
{
	RakNet::BitStream bStream;
	this->setState(PLAYER_STATE_WASTED);
	
	__NetGame->filterscriptsManager->OnPlayerDeath((cell)this->myPlayerID, (cell)killerID, (cell)deathReason);
	if(__NetGame->gamemodeManager) __NetGame->gamemodeManager->OnPlayerDeath((cell)this->myPlayerID, (cell)killerID, (cell)deathReason);

	bStream.Write(this->myPlayerID);
	__NetGame->GlobalRPC(RPC_PlayerDeath, &bStream, this->myPlayerID);

	if ( killerID == INVALID_PLAYER_ID )
		logprintf("[death] %s died %d", __NetGame->playerPool->getPlayerNick(this->myPlayerID), deathReason);
	else
		logprintf("[kill] %s killed %s %s", __NetGame->playerPool->getPlayerNick(killerID), __NetGame->playerPool->getPlayerNick(this->myPlayerID), __NetGame->getWeaponName(deathReason));
	
}

void CPlayer::EnterVehicle(_VehicleID vehicleID, uint8_t isPassenger)
{
	RakNet::BitStream bStream;

	__NetGame->filterscriptsManager->OnPlayerEnterVehicle((cell)this->myPlayerID, (cell)vehicleID, (cell)isPassenger);
	if(__NetGame->gamemodeManager) __NetGame->gamemodeManager->OnPlayerEnterVehicle((cell)this->myPlayerID, (cell)vehicleID, (cell)isPassenger);

	bStream.Write(this->myPlayerID);
	bStream.Write(vehicleID);
	bStream.Write(isPassenger);

	__NetGame->AddedPlayersRPC(RPC_EnterVehicle, &bStream, this->myPlayerID);
}

void CPlayer::ExitVehicle(_VehicleID vehicleID)
{
	RakNet::BitStream bStream;

	__NetGame->filterscriptsManager->OnPlayerExitVehicle((cell)this->myPlayerID, (cell)vehicleID);
	if(__NetGame->gamemodeManager) __NetGame->gamemodeManager->OnPlayerExitVehicle((cell)this->myPlayerID, (cell)vehicleID);

	bStream.Write(this->myPlayerID);
	bStream.Write(vehicleID);

	__NetGame->AddedPlayersRPC(RPC_ExitVehicle, &bStream, this->myPlayerID);
}

#define EVENT_ENTEREXIT_MODSHOP			4

void CPlayer::EnterExitModShop(_VehicleID vehicleID, uint32_t enterExit, uint32_t interiorID)
{
	if(enterExit) this->bIsInModShop = TRUE;
	else this->bIsInModShop = FALSE;

	RakNet::BitStream bStream;
	uint32_t dwEvent = EVENT_ENTEREXIT_MODSHOP;
	uint32_t dwVehicleID = vehicleID;
	uint32_t dwParamEnterExit = enterExit;
	uint32_t dwInterior = interiorID;

	bStream.Write(this->myPlayerID);
    bStream.Write(dwEvent);
	bStream.Write(dwVehicleID);
	bStream.Write(dwParamEnterExit);
	bStream.Write(dwInterior);

	if(__NetGame->filterscriptsManager && __NetGame->gamemodeManager) {
		__NetGame->filterscriptsManager->OnEnterExitModShop((cell)this->myPlayerID, enterExit, interiorID);
		__NetGame->gamemodeManager->OnEnterExitModShop((cell)this->myPlayerID, enterExit,interiorID);
	}

	__NetGame->AddedPlayersRPC(RPC_ScmEvent, &bStream, this->myPlayerID); 
}

	
_PlayerID CPlayer::GetTargettedPlayerID( )
{
	return this->targettedPlayerID;
}
void CPlayer::SetTargettedPlayerID( _PlayerID targetID )
{
	if( targettedPlayerID == targetID ) return;
	targettedPlayerID = targetID;

	if( __NetGame->filterscriptsManager )
		__NetGame->filterscriptsManager->OnPlayerTargetPlayer( this->myPlayerID, targetID );
	if( __NetGame->gamemodeManager )
		__NetGame->gamemodeManager->OnPlayerTargetPlayer( this->myPlayerID, targetID );
	
}

CKeyBinder* CPlayer::GetKeyBinder( )
{
	return this->playerKeysBind;
}