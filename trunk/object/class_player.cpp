#include "../main.h"



CPlayer::CPlayer( )
{
}

CPlayer::~CPlayer( )
{
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