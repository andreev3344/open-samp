#include "../main.h"



CPlayer::CPlayer( )
{
}

CPlayer::~CPlayer( )
{
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
			// this->sub_492400(  ); <----- StreamingProcess
		}
		else
		{
			//if( GetElaspedTime( ) - this->unknown1AE4 > *(uint32_t*)0x4E6408 )
			//{
			//	// this->sub_492400(  ); <----- StreamingProcess
			//	this->unknown1AE4 = GetElapsedTime( );
			//}
		}
	}

	/*
			Hé ouais, on peut retaper du code sans avoir le code source comme certains Trolls le pense ....
			C'est pas très clair mais ça le deviendra ...
	*/

	//if( GetElapsedTime( ) - this->unknown1A27 >= 5000 || this->GetDistanceFrom3DPoint( this->unknown1A2B ) <= *(float*)0x4E6404 )
	//{
	//	this->unknown1A23 = 0;
	//	// this->sub_492400( );
	//	if( this->bshowCheckpoint )
	//	{

	//		if( this->GetDistanceFrom3DPoint( checkpointPosition ) >= this->checkpointSize )
	//		{
	//			if( this->isInCheckpoint != 0 )
	//			{
	//				this->isInCheckpoint = 0;
	//				__NetGame->filterscriptsManager->OnPlayerLeaveCheckpoint( this->myPlayerID );
	//				if( __NetGame->gamemodeManager )
	//					__NetGame->gamemodeManager->OnPlayerLeaveCheckpoint( this->myPlayerID );

	//			}

	//		}
	//		else
	//		{
	//			if( this->isInCheckpoint == 0 )
	//			{
	//				this->isInCheckpoint = 1;
	//				__NetGame->filterscriptsManager->OnPlayerEnterCheckpoint( this->myPlayerID );
	//				if( __NetGame->gamemodeManager )
	//					__NetGame->gamemodeManager->OnPlayerEnterCheckpoint( this->myPlayerID );
	//			}

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


void CPlayer::ProcessOnFootSyncData( ON_FOOT_SYNC* syncData )
{
	this->currentVehicleID = 0;
	memcpy( (void*)&this->onFootSyncData, (void*)syncData, sizeof( ON_FOOT_SYNC ) );

	UpdatePosition( this->onFootSyncData.position.X, this->onFootSyncData.position.Y, this->onFootSyncData.position.Z, false );

	this->unknown0014 = this->onFootSyncData.zAngle;
	this->unknown0018 = *( uint32_t* ) &this->onFootSyncData.unknown0016[0];
	this->unknown001C = *( uint32_t* ) &this->onFootSyncData.unknown0016[4];
	this->unknown0020 = *( uint32_t* ) &this->onFootSyncData.unknown0016[8];

	this->SyncingDataType = 1;

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

		for( int i = 0, a = 0; i < recordname_len && a < 256; i++ )
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
			uint32_t dwReturn = ( uint32_t )__NetGame, CNetGame__GetElapsedTime = 0x498A90;
			_asm
			{
				pushad
				mov ecx, dwReturn
				call CNetGame__GetElapsedTime
				mov dwReturn, eax
				popad
			}

			lastNPCWritingInFile = dwReturn;

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
		this->Text3DLabelsNumber++;
	}

}

void CPlayer::destroyText3DLabel( uint16_t labelID )
{
	if( __NetGame->text3DLabelsPool > 0 )
	{
		__NetGame->text3DLabelsPool->hideForPlayer( labelID, this->myPlayerID );
		this->bisText3DLabelStreamedIn[ labelID ] = 0;
		this->Text3DLabelsNumber--;
	}
}

float CPlayer::GetDistanceFrom3DPoint( tVector point )
{
	return this->GetDistanceFrom3DPoint( point.X, point.Y, point.Z );
}

float CPlayer::GetDistanceFrom3DPoint( float x, float y, float z )
{

	return sqrt( (float) ( this->position.X - x ) * ( this->position.X - x ) +
		( this->position.Y - y ) * ( this->position.Y - y ) +
		( this->position.Z - z ) * ( this->position.Z - z ) );

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