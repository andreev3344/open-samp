#include "../main.h"



CPlayer::CPlayer( )
{
}

CPlayer::~CPlayer( )
{
}
void CPlayer::ShowPlayerAttachedObjectToPlayer( _PlayerID toPlayerID, uint8_t objectID )
{
	if( 0 > objectID || objectID >= MAX_ATTACHED_OBJECT ) return;

	if( this->attachedObjectSlot[ objectID ] )
	{
		uint32_t RPC_ShowAttachedObject = 0x5B;
		RakNet::BitStream bStream;
		bStream.Write( ( uint16_t ) this->unknown001E );
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



	bStream.Write( ( uint16_t ) this->unknown001E );
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

			//if( __NetGame->filterscriptsManager )
			//	__NetGame->filterscriptsManager->OnPlayerStreamedIn( playerID, this->myPlayerID );
			//if( __NetGame->gamemodeManager )
			//	__NetGame->gamemodeManager->OnPlayerStreamedIn( playerID, this->myPlayerID );
		}
	

	}

}

void CPlayer::streamOutPlayer( _PlayerID playerID )
{
	if( __NetGame->playerPool )
	{

		if( this->bisPlayerStreamedIn[ playerID ] != 0 )
		{
			// le call ici
			this->bisPlayerStreamedIn[ playerID ] = 0;
			this->StreamedInPlayers--;

			//if( __NetGame->filterscriptsManager )
			//	__NetGame->filterscriptsManager->OnPlayerStreamOut( playerID, this->myPlayerID );
			//if( __NetGame->gamemodeManager )
			//	__NetGame->gamemodeManager->OnPlayerStreamOut( playerID, this->myPlayerID );


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

		if( player && player->getState( ) != 0 && currentVirtualWorld == playerPool->playersVirtualWorlds[ playerID ] )
		{
			if( player->getState( ) == PLAYER_STATE_PASSENGER )
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
		bool isStreamedIn = ( this->bisText3DLabelStreamedIn[ text3dID ] ? true : false );
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

void CPlayer::UpdatePosition( float x, float y, float z, bool forceStreamingProcess )
{
	this->position.X = x;
	this->position.Y = y;
	this->position.Z = z;


	if( this->unknown1A23 == 0 )
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

	if( __NetGame->GetTime( ) - this->unknown1A27 >= 5000 || this->GetDistanceFrom3DPoint( this->unknown1A2B ) <= *(float*)0x4E6404 ) // 0x4E6404 = stream_distance
	{
		this->unknown1A23 = 0;
		// this->sub_492400( );
	}

	//if( this->bshowCheckpoint )
	//{

	//	if( this->GetDistanceFrom3DPoint( checkpointPosition ) >= this->checkpointSize )
	//	{
	//		if( this->isInCheckpoint != 0 )
	//		{
	//			this->isInCheckpoint = 0;
	//			__NetGame->filterscriptsManager->OnPlayerLeaveCheckpoint( this->myPlayerID );
	//			if( __NetGame->gamemodeManager )
	//				__NetGame->gamemodeManager->OnPlayerLeaveCheckpoint( this->myPlayerID );
	//		}
	//	}
	//	else
	//	{
	//		if( this->isInCheckpoint == 0 )
	//		{
	//			this->isInCheckpoint = 1;
	//			__NetGame->filterscriptsManager->OnPlayerEnterCheckpoint( this->myPlayerID );
	//			if( __NetGame->gamemodeManager )
	//				__NetGame->gamemodeManager->OnPlayerEnterCheckpoint( this->myPlayerID );
	//		}
	//	}
	//}
	//if( this->bshowCheckpoint )
	//{
	//	if( this->GetDistanceFrom3DPoint( this->raceCheckpointPos ) >= this->raceCheckpointSize )
	//	{
	//		if( this->isInRaceCheckpoint != 0 ) 
	//		{
	//			this->isInRaceCheckpoint = 0;
	//			__NetGame->filterscriptsManager->OnPlayerLeaveRaceCheckpoint( this->myPlayerID );
	//			if( __NetGame->gamemodeManager )
	//				__NetGame->gamemodeManager->OnPlayerLeaveRaceCheckpoint( this->myPlayerID );
	//		}
	//	}
	//	else
	//	{
	//		if( this->isInRaceCheckpoint == 0 )
	//		{
	//			this->isInRaceCheckpoint = 1;
	//			__NetGame->filterscriptsManager->OnPlayerEnterRaceCheckpoint( this->myPlayerID );
	//			if( __NetGame->gamemodeManager )
	//				__NetGame->gamemodeManager->OnPlayerEnterRaceCheckpoint( this->myPlayerID );
	//		}
	//	}
	//}

}

void CPlayer::CheckKeysUpdate( uint16_t keys )
{
	if( this->lastKeysState != keys )
	{
		
		if( __NetGame->gamemodeManager )
//			__NetGame->gamemodeManager->OnPlayerKeyStateChange( this->myPlayerID, keys, this->lastKeysState );
		if( __NetGame->filterscriptsManager )
//			__NetGame->filterscriptsManager->OnPlayerKeyStateChange( this->myPlayerID, keys, this->lastKeysState );

		this->lastKeysState = keys;
	}


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

	this->unknown0014 = this->onFootSyncData.zAngle;
	this->unknown0018 = *( uint32_t* ) &this->onFootSyncData.unknown0016[0]; // <-- What is that ?
	this->unknown001C = *( uint32_t* ) &this->onFootSyncData.unknown0016[4]; // and that ?
	this->unknown0020 = *( uint32_t* ) &this->onFootSyncData.unknown0016[8]; // that too ?

	this->SyncingDataType = 1;

	// sub_495630( this->unknown0014, &bufOut ); // la flème de m'y pencher :D
	
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
			uint32_t timeElapsed = __NetGame->GetTime( ) - this->lastNPCWritingInFile;
			fwrite( &timeElapsed, 4, 1, this->ioFileNPC );
			fwrite( syncData, sizeof( ON_FOOT_SYNC ), 1, this->ioFileNPC );
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

	uint32_t RPC_SetSkillLevel = 0x8F;

	RakNet::BitStream bStream;

	bStream.Write( ( uint16_t )this->myPlayerID );
	bStream.Write( ( uint32_t )skill );
	bStream.Write( ( uint16_t )this->skillsLevel[ skill ] );

	CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_SetSkillLevel, &bStream, this->myPlayerID, 2 );

	if( this->playerState && this->playerState != PLAYER_STATE_SPECTACTING )
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

			lastNPCWritingInFile = __NetGame->GetTime( );

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

bool CPlayer::isVehicleStreamedIn( uint16_t vehicleID )
{
	if( 0 > vehicleID || vehicleID >= MAX_VEHICLES ) return false;
	return this->bisVehicleStreamedIn[ vehicleID ];
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
	isInRaceCheckpoint = 0;

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

void CPlayer::setCheckpoint( tVector position, float size )
{
	checkpointPosition = position;
	checkpointSize = size;
	showCheckpoint( true );
}

void CPlayer::showCheckpoint( bool show )
{
	this->bshowCheckpoint = (BOOL)( show ? 1 : 0 );
	this->isInCheckpoint = 0;

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

uint16_t CPlayer::getCurrentVehicleID( )
{
	return this->currentVehicleID;
}

tVector* CPlayer::getCameraPosition( )
{
	return &this->cameraPosition;
}

tVector* CPlayer::getCameraFrontVector( )
{
	return &this->cameraFrontVector;
}

float CPlayer::getFacingAngle( )
{
	return this->facingAngle;
}

void CPlayer::setState( uint8_t state )
{
}

uint8_t CPlayer::getState( )
{
	return this->playerState;
}

float CPlayer::getHealth( )
{
	return this->health;
}

tVector* CPlayer::getPosition( )
{
	return &this->position;
}