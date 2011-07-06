#include "../main.h"



CPlayer::CPlayer( )
{
}

CPlayer::~CPlayer( )
{
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