#include "../main.h"



CPlayer::CPlayer( )
{
	setMyID( -1 );
	this->playerText3DLabels	= 0;
	this->playerVarsClass		= 0;

	Init( );

}

CPlayer::~CPlayer( )
{
}

void CPlayer::Init( )
{

	this->SyncingDataType		= SYNCING_TYPE_NONE;
	this->currentVehicleID		= -1;
	this->unknown0275			= 0;
	this->unknown0279			= 0;
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
	this->unknown02B7			= 0;

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
	this->unknown1A13				= 0;
	this->unknown1A17				= 0;
	this->StreamedInText3DLabelsNumber = 0;
	this->hasCustomSpawn			= FALSE;
	memset( &customSpawn, 0x00, sizeof( tSPAWNS ) );

	this->time						= 0;
	this->gameTime					= 720.0f;
	this->NPCRecordingType			= 0;
	this->ioFileNPC					= 0;
	this->unknown1A4D				= __NetGame->GetTime( );

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

}

void CPlayer::Say( char* text, uint8_t len )
{
	RakNet::BitStream bStream;
	bStream.Write( ( _PlayerID ) this->myPlayerID );
	bStream.Write( ( uint8_t ) len );
	bStream.Write( ( char*) text, len );

	uint32_t RPC_AddPlayerMessage = 0x7D;

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
					CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_AddPlayerMessage, &bStream, playerID, 3 );
				}
			}
		}
		CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_AddPlayerMessage, &bStream, this->myPlayerID, 3 );
	
	}
	else
	{
		CNetGame__RPC_SendToEveryPlayer( ( uint32_t )__NetGame, &RPC_AddPlayerMessage, &bStream, -1, 3 );
	}


}

void CPlayer::SendTime( )
{
	uint32_t RPC_SendTime = 0x94;
	RakNet::BitStream bStream;
	bStream.Write( ( uint32_t ) __NetGame->GetTime( ) );
	CNetGame__RPC_SendToPlayer( ( uint32_t ) __NetGame, &RPC_SendTime, &bStream, this->myPlayerID, 2 );
}

void CPlayer::ShowPlayerAttachedObjectToPlayer( _PlayerID toPlayerID, uint8_t objectID )
{
	if( 0 > objectID || objectID >= MAX_ATTACHED_OBJECT ) return;

	if( this->attachedObjectSlot[ objectID ] )
	{
		uint32_t RPC_ShowAttachedObject = 0x5B;
		RakNet::BitStream bStream;
		bStream.Write( ( uint16_t ) this->myPlayerID );
		bStream.Write( ( uint32_t ) objectID );
		//bStream.sub_465330( );
		bStream.Write( ( char* ) &attachedObject[ objectID ], sizeof( tAttachedObject ) );

		CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_ShowAttachedObject, &bStream, toPlayerID, 2 );
	}

}

int CPlayer::showForPlayer( _PlayerID playerID )
{
	uint32_t RPC_ShowPlayer = 0x65;	// je pense plutot à renommer en spawnForPlayer mais bon

	RakNet::BitStream bStream;



	bStream.Write( ( uint16_t ) this->myPlayerID ); // <-- une erreur de ...
	bStream.Write( ( uint8_t ) this->customSpawn.Team );
	bStream.Write( ( uint8_t ) this->customSpawn.Skin );
	bStream.Write( ( tVector ) this->position );
	bStream.Write( ( float ) this->facingAngle );
	bStream.Write( ( uint32_t ) this->nickNameColor );
	bStream.Write( ( uint8_t ) this->fightingStyle );

	bStream.Write( ( char* )skillsLevel, sizeof( uint16_t ) * 11 );

	CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_ShowPlayer, &bStream, playerID, 2 );

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
	uint32_t RPC_AttachObject = 0x5B;
	bStream.Write( ( _PlayerID ) this->myPlayerID );
	bStream.Write( ( uint32_t ) index );
	bStream.Write( ( bool ) true );
	bStream.Write( ( char* )&attachedObject[ index ], sizeof( tAttachedObject ) );

	CNetGame__RPC_SendToUnknown( ( uint32_t )__NetGame, &RPC_AttachObject, &bStream, this->myPlayerID, 2 );
	CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_AttachObject, &bStream, this->myPlayerID, 2 );

}

void CPlayer::removeAttachedObject( uint32_t index )
{
	if( 0 > index || index >= MAX_ATTACHED_OBJECT ) return;

	memset( &this->attachedObject[ index ], 0x00, sizeof( tAttachedObject ) );

	this->attachedObjectSlot[ index ] = FALSE;

	RakNet::BitStream bStream;
	uint32_t RPC_AttachObject = 0x5B;
	bStream.Write( ( _PlayerID ) this->myPlayerID );
	bStream.Write( ( uint32_t ) index );
	bStream.Write( ( bool ) false );

	CNetGame__RPC_SendToUnknown( ( uint32_t )__NetGame, &RPC_AttachObject, &bStream, this->myPlayerID, 2 );
	CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_AttachObject, &bStream, this->myPlayerID, 2 );

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

void CPlayer::ProcessStreaming( )
{
	CPlayerPool* playerPool = __NetGame->playerPool;
//	CVehiclePool* vehiclePool = __NetGame->vehiclePool;
	CText3DLabels* text3dlabelsPool = __NetGame->text3DLabelsPool;
	CPickupPool* pickupsPool = __NetGame->pickupPool;

	uint32_t currentVirtualWorld = 0;

	if( this->myPlayerID < MAX_PLAYERS )
	{
		currentVirtualWorld = playerPool->playersVirtualWorlds[ this->myPlayerID ];
	}

	float streamDistance = *(float*)0x4E6404 * *(float*)0x4E6404; // 0x4E6404 correspond à la variable contenant la distance de stream

	if( /*vehiclePool == 0* ||*/ playerPool == 0 || text3dlabelsPool == 0 || pickupsPool == 0 )
		return;

	// this->sub_491EB0( );


	//for( uint32_t vehicleID = 0; vehicleID < MAX_VEHICLES; vehicleID ++ ) // <-- ici se passent les calculs concernant le streaming des véhicles au joueur
	//{
	//	CVehicle* vehicle = vehiclePool->GetVehicle( vehicleID );
	//	if( vehicle == 0 ) continue;
	//}


	for( _PlayerID playerID = 0; playerID < MAX_PLAYERS; playerID ++ ) 
	{
		if( playerID == this->myPlayerID ) continue;
		CPlayer* player = playerPool->GetPlayer( playerID );

		if( player && player->isActive( ) && currentVirtualWorld == playerPool->playersVirtualWorlds[ playerID ] )
		{
			if( player->isPassenger( ) )
			{
				//CVehicle* vehicle = 0;
				//if( ( vehicle = vehiclePool->GetVehicle( player->currentVehicleID ) ) )
				//{
				//	if( vehicle->getSquaredDistanceFrom2DPoint( player->position.X, player->position.Y ) <= streamDistance )
				//	{
				//		if( isPlayerStreamedIn( playerID ) == false ) streamInPlayer( playerID );
				//	}
				//	else
				//	{
				//		if( isPlayerStreamedIn( playerID ) == true ) streamOutPlayer( playerID );
				//	}
				//}
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


	for( uint16_t pickupID = 0; pickupID < LIMIT_MAX_PICKUPS; pickupID++ )
	{
		

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
			if( __NetGame->GetTime( ) - this->lastStreaming > *(uint32_t*)0x4E6408 ) // 0x4E6408 = stream_rate
			{
				ProcessStreaming( );
				this->lastStreaming = __NetGame->GetTime( );
			}
		}
	}

	/*
			Hé ouais, on peut retaper du code sans avoir le code source comme certains Trolls le pense ....
			C'est pas très clair mais ça le deviendra ...
	*/
	// this->unknown1A2B // Place to be ?
	if( __NetGame->GetTime( ) - this->timePlaceToBeHasSet >= 5000 || this->GetDistanceFrom3DPoint( this->placeToBe ) <= *(float*)0x4E6404 ) // 0x4E6404 = stream_distance
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
	// sub_495630( &this->quaterRotation, &bufOut ); // la flème de m'y pencher :D
	QuaternionToMatrix( &this->quaterRotation, &matrixRotation );

	this->facingAngle = atan2( matrixRotation.at.X, -matrixRotation.at.Y ) * 57.2957763671875f; // pas sûr de cette merde

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
			this->currentVehicleID		= syncData->vehicleID;
			this->currentSeatinVehicle	= 0;
			memcpy( &onVehicleSyncData, syncData, 0x3C );


			// this->unknown00C2 = syncData->hydraReactorAngle[0];
			// this->unknown00C4 = syncData->hydraReactorAngle[1];


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
		
			this->SyncingDataType = SYNCING_TYPE_DRIVER;
			
			if( this->currentVehicleID < MAX_VEHICLES )
			{
				/*CVehicle**/void* vehicle = __NetGame->vehiclePool->GetVehicle( this->currentVehicleID );
				MATRIX4X4 matrixRotation;
				memset( &matrixRotation, 0x00, sizeof( MATRIX4X4 ) );
				QuaternionToMatrix( &syncData->rotation, &matrixRotation );

				// vehicle->Update( this->myPlayerID, &matrixRotation, syncData->health, syncData->trailerID, true );
				// vehicle->SetVelocity( syncData->velocity );


				//if( vehicle->IsATrainLoco( ) )
				//{
				//	for( _VehicleID locoID = 1; locoID < 4; locoID ++ )
				//	{
				//		_VehicleID id = locoID + this->currentVehicleID;
				//		CVehicle* loco = __NetGame->vehiclePool->GetVehicle( id );
				//		if( loco )
				//		{
				//			if( loco->IsATrainPart( ) )
				//			{
				//				loco->Update( 0xFFFF, &matrixRotation, syncData->health, syncData->trailerID, true );
				//			}
				//		}
				//	}

				//}


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

				//CVehicle* vehicle = vehiclePool->GetVehicle( syncData->vehicleID );
				//if( vehicle )
				//	UpdatePosition( vehicle->GetPosition().X, vehicle->GetPosition().Y, vehicle->GetPosition().Z, false );

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

void CPlayer::ProcessSpectatingSyncData( SPECTATING_SYNC* syncData )
{
	this->currentVehicleID = 0;
	memcpy( &this->spectatingSyncData, syncData, sizeof( SPECTATING_SYNC ) );

	UpdatePosition( syncData->position.X, syncData->position.Y, syncData->position.Z, false );
	CheckKeysUpdate( syncData->keysOnSpectating );
	setState( PLAYER_STATE_SPECTATING );
}



uint16_t CPlayer::getSkillLevel( int skill )
{
	if( 0 > skill || skill >= 11 ) return 0;
	return this->skillsLevel[ skill ];
}

void CPlayer::setSkillLevel( int skill, uint16_t level )
{
	if( 0 > skill || skill >= 11 ) return;

	uint32_t RPC_SetSkillLevel = 0x8F;

	RakNet::BitStream bStream;

	bStream.Write( ( uint16_t )this->myPlayerID );
	bStream.Write( ( uint32_t )skill );
	bStream.Write( ( uint16_t )this->skillsLevel[ skill ] );

	CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_SetSkillLevel, &bStream, this->myPlayerID, 2 );

	if( this->playerState && this->playerState != PLAYER_STATE_SPECTATING )
	{
		CNetGame__RPC_SendToUnknown( ( uint32_t )__NetGame, &RPC_SetSkillLevel, &bStream, this->myPlayerID, 2 );
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


void CPlayer::createText3DLabel( uint16_t labelID )
{

	if( __NetGame->text3DLabelsPool > 0 )
	{
		__NetGame->text3DLabelsPool->showForPlayer( labelID, this->myPlayerID );
		this->bisText3DLabelStreamedIn[ labelID ]++;
		this->StreamedInText3DLabelsNumber++;
	}

}

void CPlayer::destroyText3DLabel( uint16_t labelID )
{
	if( __NetGame->text3DLabelsPool > 0 )
	{
		__NetGame->text3DLabelsPool->hideForPlayer( labelID, this->myPlayerID );
		this->bisText3DLabelStreamedIn[ labelID ] = 0;
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

void CPlayer::setRaceCheckpoint( uint8_t type, tVector position, tVector next_position, float size )
{
	raceCheckpointPos = position;
	nextraceCheckpointPos = next_position;
	raceCheckpointType = type;
	raceCheckpointSize = size;

	showRaceCheckpoint( true );

}

void CPlayer::showRaceCheckpoint( bool show )
{
	bshowRaceCheckpoint = (BOOL)(show ? 1 : 0 );
	bIsInRaceCheckpoint = 0;

	uint32_t RPC_ShowOrHideThatIsTheQuestion = 0x00;
	RakNet::BitStream bStream;

	if( show )
	{
		RPC_ShowOrHideThatIsTheQuestion = 0x6F;
		bStream.Write( (uint8_t)this->raceCheckpointType );
		bStream.Write( (float)this->raceCheckpointPos.X );
		bStream.Write( (float)this->raceCheckpointPos.Y );
		bStream.Write( (float)this->raceCheckpointPos.Z );
		bStream.Write( (float)this->nextraceCheckpointPos.X );
		bStream.Write( (float)this->nextraceCheckpointPos.Y );
		bStream.Write( (float)this->nextraceCheckpointPos.Z );
		bStream.Write( (float)this->raceCheckpointSize );
	}
	else
	{
		RPC_ShowOrHideThatIsTheQuestion = 0x70;
	}
	CNetGame__RPC_SendToPlayer( (uint32_t)__NetGame, &RPC_ShowOrHideThatIsTheQuestion, &bStream, this->myPlayerID, 2 );
}

bool CPlayer::isInCheckpoint( )
{
	return ( this->bIsInCheckpoint > 0 ? true : false );
}

void CPlayer::setCheckpoint( tVector position, float size )
{
	checkpointPosition = position;
	checkpointSize = size;
	showCheckpoint( true );
}

void CPlayer::showCheckpoint( bool show )
{
	this->bshowCheckpoint = (BOOL)( show ? 1 : 0 );
	this->bIsInCheckpoint = 0;

	uint32_t RPC_ShowOrHideThatIsTheQuestion = 0x00;
	RakNet::BitStream bStream;
	if( show )
	{
		bStream.Write( (float)checkpointPosition.X );
		bStream.Write( (float)checkpointPosition.Y );
		bStream.Write( (float)checkpointPosition.Z );
		bStream.Write( (float)checkpointSize );
		RPC_ShowOrHideThatIsTheQuestion = 0x6D; // le RPC pour montrer le Checkpoint

	}
	else
	{
		RPC_ShowOrHideThatIsTheQuestion = 0x6E; // le RPC pour cacher le Checkpoint
	}

	CNetGame__RPC_SendToPlayer( (uint32_t)__NetGame, &RPC_ShowOrHideThatIsTheQuestion, &bStream, this->myPlayerID, 2 );

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
	uint32_t RPC_SetPlayerColor = 0x14;
	RakNet::BitStream bStream;
	bStream.Write( ( _PlayerID ) this->myPlayerID );
	bStream.Write( ( uint32_t ) color );

	CNetGame__RPC_SendToEveryPlayer( ( uint32_t ) __NetGame, &RPC_SetPlayerColor, &bStream, this->myPlayerID, 2 );
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
	this->myPlayerID;
	this->playerText3DLabels->setOwnerID( playerID );
}

uint8_t CPlayer::getState( )
{
	return this->playerState;
}


bool CPlayer::isActive( )
{
	if( getState( ) != PLAYER_STATE_NONE ) return true;
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


float CPlayer::getHealth( )
{
	return this->health;
}

void CPlayer::setHealth( float health )
{
	uint32_t RPC_SetPlayerHealth = 0x11;
	RakNet::BitStream bStream;
	bStream.Write( ( float ) health );
	CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_SetPlayerHealth, &bStream, this->myPlayerID, 2 );
}

float CPlayer::getArmour( )
{
	return this->armour;
}

tVector* CPlayer::getPosition( )
{
	return &this->position;
}

void CPlayer::setPosition( tVector position )
{
	setPosition( position.X, position.Y, position.Z );
}

void CPlayer::setPosition( float x, float y, float z )
{
	uint32_t RPC_SetPlayerPosition = 0x0F;
	RakNet::BitStream bStream;

	bStream.Write( ( float ) x );
	bStream.Write( ( float ) y );
	bStream.Write( ( float ) z );

	CNetGame__RPC_SendToPlayer( ( uint32_t ) __NetGame, &RPC_SetPlayerPosition, &bStream, this->myPlayerID, 2 );
}

void CPlayer::setPositionFindZ( float x, float y, float z )
{
	uint32_t RPC_SetPlayerPositionFindZ = 0x10;
	RakNet::BitStream bStream;

	bStream.Write( ( float ) x );
	bStream.Write( ( float ) y );
	bStream.Write( ( float ) z );

	CNetGame__RPC_SendToPlayer( ( uint32_t ) __NetGame, &RPC_SetPlayerPositionFindZ, &bStream, this->myPlayerID, 2 );
}