#include "../main.h" 



CPlayerPool::CPlayerPool( )
{
	for( uint16_t i = 0; i < MAX_PLAYERS; i++ ) // utilisait uint8_t ... fail
	{
		this->isCreated[ i ]	= FALSE;
		this->player[ i ]		= 0;
	}
	this->playersCount			= 0;
	this->updatePlayerGameTimers= 0;
	this->lastMarkerUpdate		= __NetGame->GetTime( );
}

CPlayerPool::~CPlayerPool( )
{
	for(_PlayerID i = 0; i < MAX_PLAYERS; i++)
		this->Delete(i, 0);
}

void CPlayerPool::setScore( _PlayerID playerID, uint32_t value )
{
	if( GetSlotState( playerID ) )
	{
		this->playersScore[ playerID ] = value;
	}
}

uint32_t CPlayerPool::getScore( _PlayerID playerID )
{
	if( GetSlotState( playerID ) )
	{
		return this->playersScore[ playerID ];
	}
	return 0;
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

		this->isPlayerAdmin[ playerID ]		= 0;

		
		RakNet::BitStream bStream;
		bStream.Write( ( _PlayerID ) playerID );
		bStream.Write( ( uint8_t ) reason );

		__NetGame->GlobalRPC( RPC_PlayerLeave, &bStream, playerID, 2 );

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
		this->isCreated[ playerID ]	= 0;  // fail 
	}

	this->playersCount--;

	// this->sub_47C800( );
	return 1;
}

int CPlayerPool::New( _PlayerID playerID, const char* nickname, char* serial, uint32_t isNPC, bool isAnOpenClient )
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
	player->getPlayerTextLabels()->setOwnerID( playerID );
	player->setOpenUser( isAnOpenClient );

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

	
	__NetGame->GlobalRPC( RPC_NewPlayer, &bStream, playerID, 2 );

	in_addr addr;
	addr.s_addr = __NetGame->rakServerInterface->GetPlayerIDFromIndex( playerID ).binaryAddress;
	if( this->bIsNPC[ playerID ] )
	{
		logprintf( "[npc:join] %s has joined the server (%u:%s)", nickname, playerID, inet_ntoa( addr ) );
	}
	else
	{
		logprintf( "[%sjoin] %s has joined the server (%u:%s)", (isAnOpenClient ? "Open " : "" ), nickname, playerID, inet_ntoa( addr ) );
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


uint32_t CPlayerPool::getPlayerMoney( _PlayerID playerID )
{
	if( GetSlotState( playerID ) )
	{
		return this->playersMoney[ playerID ];
	}
	return 0;
}

void CPlayerPool::setPlayerMoney( _PlayerID playerID, uint32_t amount )
{
	if( GetSlotState( playerID ) )
	{
		uint32_t old_value = this->playersMoney[ playerID ];
		this->playersMoney[ playerID ] = amount;

		if( old_value != this->playersMoney[ playerID ] )
		{
			if( __NetGame->filterscriptsManager )
				__NetGame->filterscriptsManager->OnPlayerMoneyChange( playerID, old_value, this->playersMoney[ playerID ] );
			if( __NetGame->gamemodeManager )
				__NetGame->gamemodeManager->OnPlayerMoneyChange( playerID, old_value, this->playersMoney[ playerID ] );
		}
	}
}

void CPlayerPool::givePlayerMoney( _PlayerID playerID, uint32_t amount )
{
	if( GetSlotState( playerID ) )
	{
		
		RakNet::BitStream bStream;
		bStream.Write( ( uint32_t ) amount );
		__NetGame->PlayerRPC( RPC_GivePlayerMoney, &bStream, playerID, 2 );
		uint32_t old_value = this->playersMoney[ playerID ];
		this->playersMoney[ playerID ] += amount;

		if( __NetGame->filterscriptsManager )
			__NetGame->filterscriptsManager->OnPlayerMoneyChange( playerID, old_value, this->playersMoney[ playerID ] );
		if( __NetGame->gamemodeManager )
			__NetGame->gamemodeManager->OnPlayerMoneyChange( playerID, old_value, this->playersMoney[ playerID ] );
	}
}

void CPlayerPool::resetPlayerMoney( _PlayerID playerID )
{
	if( GetSlotState( playerID ) )
	{
		
		RakNet::BitStream bStream;
		__NetGame->PlayerRPC( RPC_ResetPlayerMoney, &bStream, playerID, 2 );


		uint32_t old_value = this->playersMoney[ playerID ];
		this->playersMoney[ playerID ] = 0;
		if( __NetGame->filterscriptsManager )
			__NetGame->filterscriptsManager->OnPlayerMoneyChange( playerID, old_value, 0 );
		if( __NetGame->gamemodeManager )
			__NetGame->gamemodeManager->OnPlayerMoneyChange( playerID, old_value, 0 );
	}
}

void CPlayerPool::setPlayerNick( _PlayerID playerID, char* nickname )
{
	if( GetSlotState( playerID )) 
	{
		strcpy( this->nickNames[playerID], nickname);
	}

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
		RakNet::BitStream bStream;
		bStream.Write( ( uint16_t )playerID );
		__NetGame->PlayerRPC( RPC_HidePlayerForPlayer, &bStream, forPlayerID, 2 );

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

void CPlayerPool::setPlayerVirtualWorld( _PlayerID playerID, uint32_t virtualWorld )
{
	if( GetSlotState( playerID ) )
	{
		this->playersVirtualWorlds[ playerID ] = virtualWorld;
	}
}

uint32_t CPlayerPool::getPlayerVirtualWorld( _PlayerID playerID )
{
	if( GetSlotState( playerID ) )
	{
		return this->playersVirtualWorlds[ playerID ];
	}
	return 0;
}


uint32_t CPlayerPool::getPlayerDrunkLevel( _PlayerID playerID )
{
	if( GetSlotState( playerID ) )
	{
		return this->drunkLevel[ playerID ];
	}
	return 0;
}

void CPlayerPool::setPlayerDrunkLevel( _PlayerID playerID, uint32_t level )
{
	if( GetSlotState( playerID ) )
	{
		this->drunkLevel[ playerID ] = level;
	}
}

void CPlayerPool::streamOutVehicleForAll(_VehicleID vehicleID)
{
	for(_PlayerID i = 0; i < MAX_PLAYERS; i++)
	{
		if(this->GetSlotState(i) && this->GetPlayer(i)->isVehicleStreamedIn(vehicleID)) {
			this->GetPlayer(i)->streamOutVehicle(vehicleID);
		}
	}
}

void CPlayerPool::DeactivateAll()
{
	for(_PlayerID playerId = 0; playerId < MAX_PLAYERS; playerId++)
	{
		if(this->isCreated[playerId]) 
		{
			this->player[playerId]->Deactivate();
			__NetGame->gamemodeManager->OnPlayerDisconnect(playerId, 1);
			__NetGame->filterscriptsManager->OnPlayerDisconnect(playerId, 1);
		}
		this->playersVirtualWorlds[playerId] = 0;
	}
}

void CPlayerPool::UpdateGameTimers()
{
	for(_PlayerID i = 0; i < MAX_PLAYERS; i++)
	{
		if(this->GetSlotState(i))
			if(this->player[i]) this->player[i]->SendTime();
	}
}

bool CPlayerPool::Process(float time)
{

	for(int playerId = 0; playerId < MAX_PLAYERS; playerId++)
	{
		if(this->isCreated[playerId]) {
			this->player[playerId]->Process(time);
		}
	}


	this->updatePlayerGameTimers += time;
	if(this->updatePlayerGameTimers > 1.0f) // 10.0f 0.3a
	{
		this->UpdateGameTimers();
		this->updatePlayerGameTimers = 0.0f;
	}

	return true;
}

void CPlayerPool::InitPlayersForPlayer(_PlayerID playerID)
{
	uint32_t			playerColor;
	uint8_t				bIsNPC = 0;
	RakNet::BitStream	bStream;

	for(_PlayerID i = 0; i < MAX_PLAYERS; i++)
	{
		if((this->GetSlotState(i)) && (i != playerID)) 
		{
			bStream.Reset();

			if(this->isNPC(i)) bIsNPC = 1;
			else bIsNPC = 0;

			playerColor = this->GetPlayer(i)->getColor();
			uint8_t nickLen = strlen(this->getPlayerNick(i));
			bStream.Write(i);
			bStream.Write(playerColor);
			bStream.Write(bIsNPC);
			bStream.Write(nickLen);
			bStream.Write(this->getPlayerNick(i), nickLen);
			__NetGame->PlayerRPC(RPC_NewPlayer, &bStream, playerID);
		}
	}
}
