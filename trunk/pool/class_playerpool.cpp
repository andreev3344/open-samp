#include "../main.h" 



CPlayerPool::CPlayerPool( )
{
}

CPlayerPool::~CPlayerPool( )
{
}
int CPlayerPool::New( _PlayerID playerID, const char* nickname, char* unknown, uint32_t isNPC )
{
	if( playerID >= MAX_PLAYERS ) return 0;
	if( strlen( nickname ) > MAX_PLAYER_NAME ) return 0; // au pire je peux aussi couper le pseudo au 0x18ème caractère.
	


	this->player[ playerID ] = new CPlayer(  );
	strcpy( this->nickNames[ playerID ], nickname );
	memset( ( void* )&this->unknown6F60[ playerID ], 0x00, 0x64 );

	if( unknown != 0 )
	{
		if( strlen( unknown )  >= 0x64 ) return 0; // ?!
		strcpy( this->unknown6F60[ playerID ], unknown ); // ?!
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

	this->isNPC[ playerID ] = ( BOOL )( isNPC == 0 ? 0 : 1 );

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
	if( this->isNPC[ playerID ] )
	{
		logprintf( "[npc:join] %s has joined the server (%u:%s)", nickname, playerID, "There is no ip address here !"/*inet_ntoa( addr )*/ );
	}
	else
	{
		logprintf( "[join] %s has joined the server (%u:%s)", nickname, playerID, "There is no ip address here !"/*inet_ntoa( addr )*/ );
	}

	player->SendTime( );

	//if( __NetGame->filterscriptsManager )
	//	__NetGame->filterscriptsManager->OnPlayerConnect( PlayerID );
	//if( __NetGame->gamemodeManager )
	//	__NetGame->gamemodeManager->OnPlayerConnect( PlayerID );

	this->playersCount++;

	//this->sub_47C800( );
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