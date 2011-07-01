#include "main.h"


CNetGame::CNetGame ( )
{

}

CNetGame::~CNetGame( )
{

}



uint32_t CNetGame::addSpawn( tSPAWNS spawn )
{
	if( this->spawnsNumber >= MAX_SPAWNS ) return MAX_SPAWNS; // Pourquoi ? demandez à Kye :p
	
	memcpy( &this->spawns[ this->spawnsNumber ], &spawn, sizeof( tSPAWNS ) );

	return this->spawnsNumber++;
}

void CNetGame::limitGlobalChatRadius( float distance )
{
	this->blimitGlobalChatRadius = true;
	this->dlimitGlobalChatRadius = distance;
}
void CNetGame::limitPlayerMarkerRadius( float distance )
{
	this->bLimitPlayerMarkerRadius = true;
	this->dlimitPlayerMarkerRadius = distance;
}

void CNetGame::setWeather( uint8_t weather )
{
	RakNet::BitStream* bStream = new RakNet::BitStream( );

	bStream->Write( (uint8_t)weather );
	this->weather = weather;

	if( this->playerPool > 0 )
	{
		uint32_t RPC_ChangeWeather = 0x78;

		

	}

	/*
			char str[ 128 ] = "";
			sprintf( str, "%d", weather );
			CConsole::SetStringVariable( "weather", str );
	*/
}