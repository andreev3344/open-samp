#include "../main.h" 



CPlayerPool::CPlayerPool( )
{
}

CPlayerPool::~CPlayerPool( )
{
}

int	CPlayerPool::ShowPlayerForPlayer( _PlayerID forPlayerID, _PlayerID playerID  )
{
	if( 0 > forPlayerID || forPlayerID >= MAX_PLAYERS ) return 0;
	if( 0 > playerID || playerID >= MAX_PLAYERS ) return 0;


	return this->player[ forPlayerID ]->showForPlayer( playerID );
}

bool CPlayerPool::GetSlotState( _PlayerID playerID )
{
	if( 0 > playerID || playerID >= MAX_PLAYERS ) return false;

	return (bool)( this->isCreated[ playerID ] ? true : false );
}

CPlayer* CPlayerPool::GetPlayer( _PlayerID playerID )
{
	if( GetSlotState( playerID ) == false ) return (CPlayer*)0;


	return this->player[ playerID ];
}