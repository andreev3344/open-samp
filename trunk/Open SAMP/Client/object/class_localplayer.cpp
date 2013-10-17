#include "../main.h"


void CLocalPlayer::RequestClass( uint32_t classid )
{
	RakNet::BitStream bStream;
	bStream.Write( classid );
	__NetGame->getRakClientInterface()->RPC( RPC_RequestClass, &bStream, HIGH_PRIORITY, RELIABLE, 0, false );

}

void CLocalPlayer::RequestSpawn()
{
	RakNet::BitStream bStream;
	__NetGame->getRakClientInterface()->RPC( RPC_RequestSpawn, &bStream, HIGH_PRIORITY, RELIABLE, 0, false );
}


void CLocalPlayer::SetSpawnInfo( tSPAWNS* spawnInfo )
{
	//__asm pushad
	//__asm mov eax, 0x38F0
	//__asm add eax, sampBaseAddr
	//__asm push spawnInfo
	//__asm mov ecx, this
	//__asm call eax
	//__asm popad

	memcpy( &customSpawnInfo, spawnInfo, sizeof( tSPAWNS ) );
	hasCustomSpawn = TRUE;
}

void CLocalPlayer::Spawn( )
{
	uint32_t CLocalPlayer__Spawn = sampBaseAddr + FUNC_CLOCALPLAYER_SPAWN;
	uint32_t dwThis = ( uint32_t )this;

	__asm
	{
		pushad
		mov ecx, dwThis
		call CLocalPlayer__Spawn
		popad
	}
}

void CLocalPlayer::Say( const char* message )
{
	RakNet::BitStream bStream;
	bStream.Write( ( uint8_t )strlen( message ) );
	bStream.Write( message, ( uint8_t)strlen( message ) );

	__NetGame->getRakClientInterface()->RPC( RPC_AddPlayerMessage, &bStream, HIGH_PRIORITY, RELIABLE, 0, false );

}

void CLocalPlayer::ToggleSpectating( BOOL toggle ) // Ref: sampBaseAddr + 0x3E10
{
	uint32_t CLocalPlayer__TogglePlayerSpectating = sampBaseAddr + FUNC_CLOCALPLAYER_TOGGLESPECTATING;
	uint32_t dwThis = ( uint32_t )this;
	
	__asm
	{
		pushad
		push toggle
		mov ecx, dwThis
		call CLocalPlayer__TogglePlayerSpectating
		popad
	}
}

BOOL CLocalPlayer::isSpectating( )
{
	return this->bIsSpectating;
}


void CLocalPlayer::spectateVehicleID( _VehicleID vehicleID )
{
	_asm
	{
		pushad

		mov ecx, this
		mov ebx, FUNC_CLOCALPLAYER_SPECTATEVEHICLEID
		add ebx, sampBaseAddr
		push vehicleID
		call ebx

		popad
	}
}

void CLocalPlayer::spectatePlayerID( _PlayerID playerID )
{
	_asm
	{
		pushad

		mov ecx, this
		mov ebx, FUNC_CLOCALPLAYER_SPECTATEPLAYERID
		add ebx, sampBaseAddr
		push playerID
		call ebx

		popad
	}


}

uint32_t CLocalPlayer::getSpectatingID( )
{
	return this->spectatingID;
}

uint32_t CLocalPlayer::getColorAsARGB()
{
	return __NetGame->getPlayerPool()->getPlayerColor( __NetGame->getPlayerPool()->getLocalPlayerID() );
}

uint32_t CLocalPlayer::getColorAsRGBA()
{
	return ( __NetGame->getPlayerPool()->getPlayerColor( __NetGame->getPlayerPool()->getLocalPlayerID() ) >> 8 ) | 0xFF000000;
}

void CLocalPlayer::setColor( uint32_t color )
{
	_asm
	{
		pushad

		mov ecx, this
		mov ebx, FUNC_CLOCALPLAYER_SETCOLOR
		add ebx, sampBaseAddr
		push color
		call ebx

		popad
	}
}