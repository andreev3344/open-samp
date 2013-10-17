#include "../main.h"


CPlayerPool::CPlayerPool( )
{

}

CPlayerPool::~CPlayerPool( )
{

}

CLocalPlayer* CPlayerPool::GetLocalPlayer( )
{
	return localPlayer;
}


CPlayer* CPlayerPool::GetPlayer( _PlayerID playerID )
{
	if( GetSlotState( playerID ) )
	{
		return players[ playerID ];
	}
	return 0;
}

bool CPlayerPool::New( _PlayerID playerID, char* nickName, BOOL isNPC ) // ref: sampBase + 0xDBC0
{

	this->players[ playerID ] = new CPlayer( nickName, isNPC );


	if( GetSlotState( playerID ) )
	{
		this->players[ playerID ]->getRemoteData()->playerID = playerID;

		if( isNPC == TRUE )
		{
			this->players[ playerID ]->getRemoteData()->isNPC = TRUE;
		}
		this->isCreated[ playerID ] = TRUE;
		return true;
	}

	return false;
}

bool CPlayerPool::Delete( _PlayerID playerID, uint32_t reason ) // ref: sampBase + 0xDA30
{
	if( GetSlotState( playerID ) )
	{
		if( GetLocalPlayer( ) )
		{
			if( GetLocalPlayer( )->isSpectating( ) && GetLocalPlayer( )->getSpectatingID( ) == playerID )
			{
				GetLocalPlayer( )->ToggleSpectating( FALSE );
			}
		}

		this->isCreated[ playerID ] = FALSE;
		if( GetPlayer( playerID ) )
		{
			delete players[ playerID ];
		}
		players[ playerID ] = NULL;
		return true;
	}
	return false;
}

bool CPlayerPool::GetSlotState( _PlayerID playerID )
{
	if( 0 > playerID || playerID >= MAX_PLAYERS ) return false;

	return ( bool )( players[ playerID ] != 0 && isCreated[ playerID ] != 0 );
}

char* CPlayerPool::GetLocalPlayerName()
{
	return (char*)this->localPlayerNickName;
}


void CPlayerPool::SetLocalPlayerID( _PlayerID id )
{
	this->localPlayerID = id;
}

_PlayerID CPlayerPool::getLocalPlayerID()
{
	return this->localPlayerID;
}

uint32_t CPlayerPool::getPlayerColor( _PlayerID playerID )
{
	uint32_t retour = 0;
	__asm
	{
		pushad

		mov edx, this
		mov ebx, FUNC_CPLAYERPOOL_GETPLAYERCOLOR
		add ebx, sampBaseAddr
		push playerID
		call ebx
		mov retour, eax

		popad
	}

	return retour;
}