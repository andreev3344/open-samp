#include "../main.h" 



CPlayerPool::CPlayerPool( )
{
	for( uint8_t i = 0; i < MAX_PLAYERS; i++ )
	{
		this->isCreated[ i ]	= FALSE;
		this->player[ i ]		= 0;
	}
	this->playersCount			= 0;
	this->unknown57E8			= 0;
	this->unkonwn57EC			= 0;
	this->unknown57E8			= __NetGame->GetTime( );
}

CPlayerPool::~CPlayerPool( )
{
}

float CPlayerPool::GetDistanceBetweenPlayers( _PlayerID player_one, _PlayerID player_two )
{
	if( GetSlotState( player_one ) == false || GetSlotState( player_two ) ) return 0.0f;
	return GetPlayer( player_one )->GetDistanceFrom3DPoint( *GetPlayer( player_two )->getPosition( ) );
}

int CPlayerPool::Delete( _PlayerID playerID, uint8_t reason )
{
	if( GetSlotState( playerID ) )
	{
		if( __NetGame->filterscriptsManager ) 
			__NetGame->filterscriptsManager->OnPlayerDisconnect( playerID, reason );
		if( __NetGame->gamemodeManager ) 
			__NetGame->gamemodeManager->OnPlayerDisconnect( playerID, reason );

		if( GetPlayer( playerID ) )
		{
			delete this->player[ playerID ];
			this->player[ playerID ] = 0;
		}

		this->isCreated[ playerID ]			= 0;
		this->isPlayerAdmin[ playerID ]		= 0;

		uint32_t RPC_PlayerLeave = 0x63;
		RakNet::BitStream bStream;
		bStream.Write( ( _PlayerID ) playerID );
		bStream.Write( ( uint8_t ) reason );

		CNetGame__RPC_SendToEveryPlayer( ( uint32_t )__NetGame, &RPC_PlayerLeave, &bStream, playerID, 2 );

		if( __NetGame->objectPool )
		{
			for( uint16_t objectID = 0; objectID < LIMIT_MAX_OBJECT; objectID ++ )
			{
				__NetGame->objectPool->Delete( playerID, objectID ); // Remove Player Objects
			}
		}

		if( isNPC( playerID ) )
		{
			logprintf( "[npc:part] %s has left the server (%u:%u)", getPlayerNick( playerID ), playerID, reason );
		}
		else
		{
			logprintf( "[part] %s has left the server (%u:%u)", getPlayerNick( playerID ), playerID, reason );
		}
		this->bIsNPC[ playerID ] = 0;
	}

	this->playersCount--;

	// this->sub_47C800( );
	return 1;
}

int CPlayerPool::New( _PlayerID playerID, const char* nickname, char* serial, uint32_t isNPC )
{
	if( playerID >= MAX_PLAYERS ) return 0;
	if( strlen( nickname ) > MAX_PLAYER_NAME ) return 0; // au pire je peux aussi couper le pseudo au 0x18ème caractère.
	


	this->player[ playerID ] = new CPlayer(  );
	strcpy( this->nickNames[ playerID ], nickname );
	memset( ( void* )&this->playersSerial[ playerID ], 0x00, 0x64 );

	if( serial != 0 )
	{
		if( strlen( serial )  >= 0x64 ) return 0; // ?!
		strcpy( this->playersSerial[ playerID ], serial ); // ?!
	}
	CPlayer* player = this->player[ playerID ];
	
	player->setMyID( playerID );
	//player->playerText3DLabels->setPlayerID( playerID );

	this->isCreated[ playerID ]				= 1;
	this->playersScore[ playerID ]			= 0;
	this->playersMoney[ playerID ]			= 0;
	this->isPlayerAdmin[ playerID ]			= 0;
	this->playersVirtualWorlds[ playerID ]	= 0;
	this->drunkLevel[ playerID ]			= 0;

	this->bIsNPC[ playerID ] = ( BOOL )( isNPC == 0 ? 0 : 1 );

	RakNet::BitStream bStream;
	bStream.Write( ( uint16_t )playerID );
	bStream.Write( ( uint32_t ) 0 );
	bStream.Write( ( uint8_t )isNPC );
	bStream.Write( ( uint8_t ) strlen( nickname ) );
	bStream.Write( nickname, strlen( nickname ) );

	uint32_t RPC_NewPlayer = 0x62;
	CNetGame__RPC_SendToEveryPlayer( ( uint32_t )__NetGame, &RPC_NewPlayer, &bStream, playerID, 2 );

	//in_addr addr;
	//addr.S_un.S_addr = __NetGame->rakServerInterface->GetPlayerIDFromIndex( playerID ).binaryAddress;
	if( this->bIsNPC[ playerID ] )
	{
		logprintf( "[npc:join] %s has joined the server (%u:%s)", nickname, playerID, "There is no ip address here !"/*inet_ntoa( addr )*/ );
	}
	else
	{
		logprintf( "[join] %s has joined the server (%u:%s)", nickname, playerID, "There is no ip address here !"/*inet_ntoa( addr )*/ );
	}

	player->SendTime( );

	if( __NetGame->filterscriptsManager )
		__NetGame->filterscriptsManager->OnPlayerConnect( playerID );
	if( __NetGame->gamemodeManager )
		__NetGame->gamemodeManager->OnPlayerConnect( playerID );

	this->playersCount++;

	//this->sub_47C800( );
	return 1;
}

bool CPlayerPool::isNPC( _PlayerID playerID )
{
	if( GetSlotState( playerID ) )
	{
		return ( bool )( this->bIsNPC[ playerID ] != 0 ? true : false );
	}
	return false;
}

char* CPlayerPool::getPlayerNick( _PlayerID playerID )
{
	if( GetSlotState( playerID ) )
	{
		return ( char* )this->nickNames[ playerID ];
	}
	return 0;
}

bool CPlayerPool::isNicknameUsed( char* nick )
{
	for( _PlayerID playerID = 0; playerID < MAX_PLAYERS; playerID ++ )
	{
		if( GetSlotState( playerID ) )
		{
			if( stricmp( nick, this->nickNames[ playerID ] ) == 0 )
				return true;
		}
	}

	return false;
}

int CPlayerPool::HidePlayerForPlayer( _PlayerID playerID, _PlayerID forPlayerID )
{
	if( 0 > forPlayerID || forPlayerID >= MAX_PLAYERS ) return 0;
	if( 0 > playerID || playerID >= MAX_PLAYERS ) return 0;

	if( this->player[ playerID ] )
	{
		uint32_t RPC_HidePlayerForPlayer = 0x66;
		RakNet::BitStream bStream;
		bStream.Write( ( uint16_t )playerID );
		CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_HidePlayerForPlayer, &bStream, forPlayerID, 2 );

	}

	return 1;
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