#include "../../main.h"

#ifndef _STANDALONE
#include "../../../SDK/amx/amx.h"
#endif

#include "../func_amx.h"
#include "func_amx_players.h"


cell AMX_NATIVE_CALL funcUnbindKey ( AMX* a_AmxInterface, cell* a_Params )
{
	/* playerid, keyindex */
	if(bScriptDebug) logprintf ( "[Call]-> funcUnbindKey()" );
	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player )
		{
			if( player->GetKeyBinder()->IsSlotUsed( a_Params[ 2 ] ) )
			{
				player->GetKeyBinder()->UnBindKey( a_Params[ 2 ] );
				return 1;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL funcIsValidBindKey ( AMX* a_AmxInterface, cell* a_Params )
{
	/* playerid, keyindex */
	if(bScriptDebug) logprintf ( "[Call]-> funcIsValidBindKey()" );
	CHECK_PARAMS( 2 );
	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player )
		{
			return ( uint32_t )( player->GetKeyBinder()->IsSlotUsed( a_Params[ 2 ] ) );
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL funcBindKey ( AMX* a_AmxInterface, cell* a_Params )
{
	/* playerid, keycode, callOnDown, "function" */
	if(bScriptDebug) logprintf ( "[Call]-> funcBindKey()" );
	CHECK_PARAMS( 4 );
	
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];
	CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
	char* function_name = 0;
	bool founded = false;

	if( player )
	{
		amx_StrParam( a_AmxInterface, a_Params[ 4 ], function_name );
		uint32_t funcIdx = 0, scriptIdx = 0;

		if( __NetGame->gamemodeManager  && __NetGame->filterscriptsManager)
		{
			if( &__NetGame->gamemodeManager->gmAMX == a_AmxInterface )
			{
				scriptIdx = -1; // is from the gamemode
				founded = true;
			}
			else
			{
				for( uint32_t i = 0; i < MAX_FS; i++ )
				{
					if( __NetGame->filterscriptsManager->fsAMX[ i ] == a_AmxInterface )
					{
						scriptIdx = i;
						founded = true;
						break;
					}
				}
			}
		}

		if( founded == false ) return -1;
		if( amx_FindPublic( a_AmxInterface, function_name, (int*)&funcIdx ) ) return -1; 


		return player->GetKeyBinder()->BindKey( ( uint8_t )a_Params[ 2 ], ( bool )( a_Params[ 3 ] ? true : false ), funcIdx, scriptIdx );

	}
	return 1;
}

cell AMX_NATIVE_CALL funcIsAnOpenPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcIsAnOpenPlayer()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];
	CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
	if( player )
	{
		return (cell)( player->isAnOpenUser() ? 1 : 0 );
	}
	return 0;
}

cell AMX_NATIVE_CALL funcGetPlayerSkillLevel ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerSkillLevel()" );
	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];
	CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
	if( player )
	{
		return ( cell )player->getSkillLevel ( a_Params[ 2 ] );
	}
	return 0;
}

cell AMX_NATIVE_CALL funcSetPlayerGravity ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerGravity()" );
	CHECK_PARAMS( 2 );
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];
	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		player->setGravity( amx_ctof( a_Params[ 2 ] ) );
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL funcGetPlayerGravity ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerGravity()" );
	CHECK_PARAMS( 1 );
	float gravity = 0.0f;

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];
	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return amx_ftoc( gravity );
		gravity = player->getGravity( );
	}

	return amx_ftoc( gravity );
}

cell AMX_NATIVE_CALL funcSetPlayerName ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerName()" );
	CHECK_PARAMS( 2 );
	
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) ) 
	{

		char* new_nickname = 0, old_nickname[ MAX_PLAYER_NAME ] = "";
		amx_StrParam( a_AmxInterface, a_Params[ 2 ], new_nickname );
		if( new_nickname == 0 ) return 0;

		strncpy( old_nickname, __NetGame->playerPool->getPlayerNick( playerID ), MAX_PLAYER_NAME );
		bool success = true;

		if( __NetGame->playerPool->isNicknameUsed( new_nickname ) || strlen( new_nickname ) == 0 ) success = false;

		RakNet::BitStream bStream;
		bStream.Write( ( _PlayerID ) playerID );
		bStream.Write( ( uint8_t ) strlen( new_nickname ) );
		bStream.Write( ( char* ) new_nickname, strlen( new_nickname ) );
		bStream.Write( ( bool ) success );

		if( success )
		{
			
			__NetGame->playerPool->setPlayerNick( playerID, new_nickname );
			logprintf( "[nick] %s nick changed to %s", old_nickname, new_nickname );
			__NetGame->GlobalRPC( RPC_SetPlayerName, &bStream, -1, 2 );
			return 1;
		}
		return 0;

	}
	return -1;
}
cell AMX_NATIVE_CALL funcSetPlayerSkin ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerSkin()" );
	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		if( player->HasCustomSpawn( ) )
		{
			
			RakNet::BitStream bStream;
			bStream.Write( ( uint32_t ) playerID );
			bStream.Write( ( uint32_t ) a_Params[ 2 ] );
			__NetGame->AddedPlayersRPC( RPC_SetPlayerSkin, &bStream, playerID, 2 );
			__NetGame->PlayerRPC( RPC_SetPlayerSkin, &bStream, playerID, 2 );
		}
		player->getCustomSpawn( )->Skin = ( int )a_Params[ 2 ];
		return 1;
	}
	return 0;
}
cell AMX_NATIVE_CALL funcGetPlayerSkin ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerSkin()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];
	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player ) return player->getCustomSpawn( )->Skin;
	}
	return 0;
}
cell AMX_NATIVE_CALL funcGetPlayerPos ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerPos()" );
	CHECK_PARAMS( 4 );
	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		cell* ptr = 0;

		amx_GetAddr( a_AmxInterface, a_Params[ 2 ], &ptr );
		*ptr = amx_ftoc( player->getPosition( )->X );
		amx_GetAddr( a_AmxInterface, a_Params[ 3 ], &ptr );
		*ptr = amx_ftoc( player->getPosition( )->Y );
		amx_GetAddr( a_AmxInterface, a_Params[ 4 ], &ptr );
		*ptr = amx_ftoc( player->getPosition( )->Z );

		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL funcSetPlayerPos ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerPos()" );
	CHECK_PARAMS( 4 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		player->setPosition( amx_ctof( a_Params[ 2 ] ), amx_ctof( a_Params[ 3 ] ), amx_ctof( a_Params[ 4 ] ) );
		return 1;
	}
	return 0;
}
cell AMX_NATIVE_CALL funcSetPlayerPosFindZ ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerPosFindZ()" );
	CHECK_PARAMS( 4 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		player->setPositionFindZ( amx_ctof( a_Params[ 2 ] ), amx_ctof( a_Params[ 3 ] ), amx_ctof( a_Params[ 4 ] ) );
		return 1;
	}
	return 0;
}
cell AMX_NATIVE_CALL funcGetPlayerHealth ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerHealth()" );
	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		cell* ptr = 0;
		amx_GetAddr( a_AmxInterface, a_Params[ 2 ], &ptr );
		float health = player->getHealth( );
		*ptr = amx_ftoc( health );
		return 1;
	}
	return 0;
}
cell AMX_NATIVE_CALL funcSetPlayerHealth ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerHealth()" );
	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		player->setHealth( amx_ctof( a_Params[ 2 ] ) );
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL funcSetPlayerColor ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerColor()" );
	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		player->setColor( a_Params[ 2 ] );
		return 1;
	}
	return 0;
}
cell AMX_NATIVE_CALL funcGetPlayerColor ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerColor()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		return player->getColor( );
	}
	return 0;
}
cell AMX_NATIVE_CALL funcGetPlayerVehicleID ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerVehicleID()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		return ( cell )player->getCurrentVehicleID( );
	}
	return 0;
}
cell AMX_NATIVE_CALL funcGetPlayerVehicleSeat ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerVehicleSeat()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return -1;
		
		if( player->isDriving( ) || player->isPassenger( ) )
		{
			return (cell)player->getCurrentVehicleSeatID( );
		}
	}
	return -1;
}

cell AMX_NATIVE_CALL funcPutPlayerInVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcPutPlayerInVehicle()" );
	//return _funcPutPlayerInVehicle ( a_AmxInterface, a_Params );

	CHECK_PARAMS( 3 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];
	_VehicleID vehicleID = ( _VehicleID ) a_Params[ 2 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) && __NetGame->vehiclePool->GetSlotState( vehicleID ) )
	{
		RakNet::BitStream bStream;


		bStream.Write( ( _VehicleID ) vehicleID );
		bStream.Write( ( uint8_t ) a_Params[ 3 ] ); // seat

		CVehicle* vehicle = __NetGame->vehiclePool->GetVehicle( vehicleID );
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );

		if( vehicle && player )
		{
			player->streamInVehicle( vehicleID, false );
			if( a_Params[ 3 ] == 0 )
				vehicle->vehDriverID = playerID;

			player->setCurrentVehicleID( vehicleID );
			player->UpdatePosition( vehicle->vehPos.X, vehicle->vehPos.Y, vehicle->vehPos.Z, true );
			player->SetPlaceToBe( vehicle->vehPos.X, vehicle->vehPos.Y, vehicle->vehPos.Z );

			__NetGame->PlayerRPC( RPC_PutPlayerInVehicle, &bStream, playerID, 2 );
			return 1;
		}


	}
	return 0;
}
cell AMX_NATIVE_CALL funcRemovePlayerFromVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcRemovePlayerFromVehicle()" );
	CHECK_PARAMS( 1 );
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		RakNet::BitStream bStream;
		
		__NetGame->PlayerRPC( RPC_RemovePlayerFromVehicle, &bStream, playerID, 2 );
		return 1;
	}

	return 0;
}
cell AMX_NATIVE_CALL funcIsPlayerInVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcIsPlayerInVehicle()" );
	CHECK_PARAMS( 2 );
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];
	_VehicleID vehicleID = ( _VehicleID ) a_Params[ 2 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		if( player->getState( ) == PLAYER_STATE_DRIVER || player->getState( ) == PLAYER_STATE_PASSENGER )
		{
			if( player->getCurrentVehicleID( ) == vehicleID ) 
				return 1;
		}
	}

	return 0;
}
cell AMX_NATIVE_CALL funcIsPlayerInAnyVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcIsPlayerInAnyVehicle()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		if( player->getState( ) == PLAYER_STATE_DRIVER || player->getState( ) == PLAYER_STATE_PASSENGER )
		{
			return 1;
		}
	}

	return 0;

}
cell AMX_NATIVE_CALL funcGetPlayerName ( AMX* a_AmxInterface, cell* a_Params )
{
	/* playerid, array, size_of_array */
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerName()" );
	CHECK_PARAMS( 3 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		cell* dest = 0;
		amx_GetAddr( a_AmxInterface, a_Params[ 2 ], &dest );
		return amx_SetString( dest, __NetGame->playerPool->getPlayerNick( playerID ), 0, 0, a_Params[ 3 ] );
	}
	return 0;
}
cell AMX_NATIVE_CALL funcSetPlayerCheckpoint ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerCheckpoint()" );
/* playerID, posX, posY, posZ, size, color*/
	CHECK_PARAMS( 6 );

	_PlayerID playerID = (_PlayerID) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		tVector vecPos;
		vecPos.X = amx_ctof( a_Params[ 2 ] );
		vecPos.Y = amx_ctof( a_Params[ 3 ] );
		vecPos.Z = amx_ctof( a_Params[ 4 ] );
		player->setCheckpoint( vecPos, amx_ctof( a_Params[ 5 ] ), a_Params[ 6 ] );

		return 1;
	}
	return 0;
}
cell AMX_NATIVE_CALL funcDisablePlayerCheckpoint ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcDisablePlayerCheckpoint()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = (_PlayerID) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		player->showCheckpoint( false );

		return 1;
	}
	return 0;
}
cell AMX_NATIVE_CALL funcIsPlayerInCheckpoint ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcIsPlayerInCheckpoint()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = (_PlayerID) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		if( player->isInCheckpoint( ) ) return 1;
	}
	return 0;
}
cell AMX_NATIVE_CALL funcSetPlayerRaceCheckpoint ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerRaceCheckpoint()" );
	CHECK_PARAMS( 10 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];
	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		tVector vecPos, vecNext;
		vecPos.X = amx_ctof( a_Params[ 3 ] );
		vecPos.Y = amx_ctof( a_Params[ 4 ] );
		vecPos.Z = amx_ctof( a_Params[ 5 ] );

		vecNext.X = amx_ctof( a_Params[ 6 ] );
		vecNext.Y = amx_ctof( a_Params[ 7 ] );
		vecNext.Z = amx_ctof( a_Params[ 8 ] );

		player->setRaceCheckpoint( ( uint8_t ) a_Params[ 2 ], vecPos, vecNext, amx_ctof( a_Params[ 9 ] ), a_Params[ 10 ] );
		return 1;
	}

	return 0;
}
cell AMX_NATIVE_CALL funcDisablePlayerRaceCheckpoint ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcDisablePlayerRaceCheckpoint()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = (_PlayerID) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		player->showRaceCheckpoint( false );

		return 1;
	}
	return 0;
}
cell AMX_NATIVE_CALL funcIsPlayerInRaceCheckpoint ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcIsPlayerInRaceCheckpoint()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = (_PlayerID) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		if( player->isInRaceCheckpoint( ) ) return 1;
	}
	return 0;
}
cell AMX_NATIVE_CALL funcSetPlayerInterior ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerInterior()" );
	CHECK_PARAMS( 2 );
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) ) 
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		
		RakNet::BitStream bStream;
		bStream.Write( ( uint8_t ) a_Params[ 2 ] );
		__NetGame->PlayerRPC( RPC_SetPlayerInterior, &bStream, playerID, 2 );
		return 1;
	}

	return 0;
}
cell AMX_NATIVE_CALL funcGetPlayerInterior ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerInterior()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		return player->getInterior( );
	}
	return 0;
}
cell AMX_NATIVE_CALL funcSetPlayerAttachedObject ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerAttachedObject()" );

	CHECK_PARAMS( 13 );
	
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		tVector offset, rotation, scale;

		offset.X = amx_ctof( a_Params[5] );
		offset.Y = amx_ctof( a_Params[6] );
		offset.Z = amx_ctof( a_Params[7] );

		rotation.X = amx_ctof( a_Params[8] );
		rotation.Y = amx_ctof( a_Params[9] );
		rotation.Z = amx_ctof( a_Params[10] );

		scale.X = amx_ctof( a_Params[11] );
		scale.Y = amx_ctof( a_Params[12] );
		scale.Z = amx_ctof( a_Params[13] );

		player->setAttachedObject( ( uint32_t ) a_Params[2], ( uint32_t ) a_Params[3], ( uint32_t ) a_Params[4], offset, rotation, scale );		

	}
	return 0;
	//return _funcSetPlayerAttachedObject ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcRemovePlayerAttachedObject ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcRemovePlayerAttachedObject()" );

	CHECK_PARAMS( 2 );


	_PlayerID playerID = ( _PlayerID ) a_Params[1];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		player->removeAttachedObject( a_Params[ 2 ] );
	}
	return 0;
}

cell AMX_NATIVE_CALL funcIsPlayerAttachedObjectSlotUsed ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcIsPlayerAttachedObjectSlotUsed()" );

	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		if( player->IsAttachedObjectSlotUsed( a_Params[ 2 ] ) ) return 1;

	}
	return 0;
	//return _funcIsPlayerAttachedObjectSlotUsed ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerCameraLookAt ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerCameraLookAt()" );
	CHECK_PARAMS( 4 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		tVector lookAt;
		lookAt.X	= amx_ctof( a_Params[ 2 ] );
		lookAt.Y	= amx_ctof( a_Params[ 3 ] );
		lookAt.Z	= amx_ctof( a_Params[ 4 ] );

		RakNet::BitStream bStream;
#ifdef _BIG_ENDIAN_SYSTEM
		bStream.Write(lookAt.X);
		bStream.Write(lookAt.Y);
		bStream.Write(lookAt.Z);
#else
		bStream.Write( ( char* ) &lookAt, sizeof( tVector ) );
#endif
		__NetGame->PlayerRPC( RPC_SetPlayerCameralookAt, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcSetPlayerCameraLookAt ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerCameraPos ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerCameraPos()" );
	CHECK_PARAMS( 4 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		tVector cameraPos;
		cameraPos.X	= amx_ctof( a_Params[ 2 ] );
		cameraPos.Y	= amx_ctof( a_Params[ 3 ] );
		cameraPos.Z	= amx_ctof( a_Params[ 4 ] );

		RakNet::BitStream bStream;
#ifdef _BIG_ENDIAN_SYSTEM
		bStream.Write(cameraPos.X);
		bStream.Write(cameraPos.Y);
		bStream.Write(cameraPos.Z);
#else
		bStream.Write( ( char* ) &cameraPos, sizeof( tVector ) );
#endif
		__NetGame->PlayerRPC( RPC_SetPlayerCameraPos, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
//	return _funcSetPlayerCameraPos ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetCameraBehindPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetCameraBehindPlayer()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		
		RakNet::BitStream bStream;
		__NetGame->PlayerRPC( RPC_SetPlayerCameraBehindPlayer, &bStream, playerID, 2 );

		return 1;
	}
	return 0;
	//return _funcSetCameraBehindPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerCameraPos ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerCameraPos()" );

	CHECK_PARAMS( 4 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		tVector cam_pos = player->getAimSyncData( )->cameraPosition;

		cell* addr = 0;
		amx_GetAddr( a_AmxInterface, a_Params[ 2 ], &addr );
		*addr = amx_ftoc( cam_pos.X );
		amx_GetAddr( a_AmxInterface, a_Params[ 3 ], &addr );
		*addr = amx_ftoc( cam_pos.Y );
		amx_GetAddr( a_AmxInterface, a_Params[ 4 ], &addr );
		*addr = amx_ftoc( cam_pos.Z );

		return 1;
	}
	return 0;
//	return _funcGetPlayerCameraPos ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerCameraFrontVector ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerCameraFrontVector()" );
	CHECK_PARAMS( 4 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		tVector front_vector = player->getAimSyncData( )->cameraFrontVector;

		cell* addr = 0;
		amx_GetAddr( a_AmxInterface, a_Params[ 2 ], &addr );
		*addr = amx_ftoc( front_vector.X );
		amx_GetAddr( a_AmxInterface, a_Params[ 3 ], &addr );
		*addr = amx_ftoc( front_vector.Y );
		amx_GetAddr( a_AmxInterface, a_Params[ 4 ], &addr );
		*addr = amx_ftoc( front_vector.Z );

		return 1;
	}
	return 0;
	//return _funcGetPlayerCameraFrontVector ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcTogglePlayerControllable ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcTogglePlayerControllable()" );

	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		uint8_t toggle = ( uint8_t ) a_Params[ 2 ];

		RakNet::BitStream bStream;

		bStream.Write( ( uint8_t ) toggle );
		__NetGame->PlayerRPC( RPC_TogglePlayerControllable, &bStream, playerID, 2 );

		return 1;
	}
	return 0;
//	return _funcTogglePlayerControllable ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcPlayerPlaySound ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcPlayerPlaySound()" );

	CHECK_PARAMS( 5 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		tVector position;
		uint32_t soundid	= a_Params[ 2 ];
		position.X			= amx_ctof( a_Params[ 3 ] );
		position.Y			= amx_ctof( a_Params[ 4 ] );
		position.Z			= amx_ctof( a_Params[ 5 ] );

		RakNet::BitStream bStream;
		bStream.Write( ( uint32_t ) soundid );
#ifdef _BIG_ENDIAN_SYSTEM
		bStream.Write(position.X);
		bStream.Write(position.Y);
		bStream.Write(position.Z);
#else
		bStream.Write( ( char* )&position, sizeof( tVector ) );
#endif

		__NetGame->PlayerRPC( RPC_PlayerPlaySound, &bStream, playerID, 2 );

		return 1;
	}
	return 0;
	//return _funcPlayerPlaySound ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerScore ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerScore()" );
	CHECK_PARAMS( 2 );
	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		__NetGame->playerPool->setScore( playerID, a_Params[ 2 ] );
		return 1;
	}
	return 0;
	//return _funcSetPlayerScore ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerScore ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerScore()" );
	CHECK_PARAMS( 1 );
	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	return __NetGame->playerPool->getScore( playerID );
	//return _funcGetPlayerScore ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerFacingAngle ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerFacingAngle()" );

	CHECK_PARAMS( 2 );


	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		RakNet::BitStream bStream;
		
		bStream.Write( ( float )amx_ctof( a_Params[ 2 ] ) );
		__NetGame->PlayerRPC( RPC_SetPlayerFacingAngle, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcSetPlayerFacingAngle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerFacingAngle ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerFacingAngle()" );
	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		cell* ptr = 0;
		amx_GetAddr( a_AmxInterface, a_Params[ 2 ], &ptr );
		float angle = player->getFacingAngle( );
		*ptr = amx_ftoc( angle );
		return 1;
	}
	return 0;
	//return _funcGetPlayerFacingAngle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGivePlayerMoney ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGivePlayerMoney()" );

	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		__NetGame->playerPool->givePlayerMoney( playerID, a_Params[ 2 ] );
		return 1;
	}
	return 0;
	//return _funcGivePlayerMoney ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerMoney ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerMoney()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		return __NetGame->playerPool->getPlayerMoney( playerID );
	}
	return 0;
//	return _funcGetPlayerMoney ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcResetPlayerMoney ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcResetPlayerMoney()" );

	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		__NetGame->playerPool->resetPlayerMoney( playerID );
	}
	return 0;	
	//	return _funcResetPlayerMoney ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcGetPlayerState ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerState()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		return (cell)player->getState( );
	}
	return 0;
	//return _funcGetPlayerState ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcResetPlayerWeapons ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcResetPlayerWeapons()" );
	CHECK_PARAMS( 1 );


	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		
		RakNet::BitStream bStream;
		__NetGame->PlayerRPC( RPC_ResetPlayerWeapons, &bStream, playerID, 2 );

		return 1;
	}
	return 0;
	//return _funcResetPlayerWeapons ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGivePlayerWeapon ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGivePlayerWeapon()" );

	CHECK_PARAMS( 3 );

	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		
		RakNet::BitStream bStream;

		bStream.Write( ( uint32_t ) a_Params[2] );
		bStream.Write( ( uint32_t ) a_Params[3] );

		__NetGame->PlayerRPC( RPC_GivePlayerWeapon, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcGivePlayerWeapon ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerArmedWeapon ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerArmedWeapon()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		RakNet::BitStream bStream;
		bStream.Write( ( uint32_t ) a_Params[ 2 ] );

		__NetGame->PlayerRPC( RPC_SetPlayerArmedWeapon, &bStream, playerID, 2 );
		return 1;
	}

	return 0;
//	return _funcSetPlayerArmedWeapon ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerIp ( AMX* a_AmxInterface, cell* a_Params ) // Need rakserverinterface
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerIp()" );
	CHECK_PARAMS( 3 );
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		in_addr addr;
		addr.s_addr = __NetGame->rakServerInterface->GetPlayerIDFromIndex( playerID ).binaryAddress;
		cell* ptr = 0;
		amx_GetAddr( a_AmxInterface, a_Params[ 2 ], &ptr );
		amx_SetString( ptr, inet_ntoa( addr ), 0, 0, a_Params[ 3 ] );
		return 1;
	}
	return 0;
//	return _funcGetPlayerIp ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerPing ( AMX* a_AmxInterface, cell* a_Params ) // Need rakserverinterface
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerPing()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID )a_Params[1];

	if( __NetGame->playerPool->GetSlotState( playerID ) ) 
	{
		return ( cell )( __NetGame->getRakInterface()->GetLastPing( __NetGame->getRakInterface()->GetPlayerIDFromIndex( playerID ) ) );
	}
	return 0xFFFF;
//	return _funcGetPlayerPing ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerWeapon ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerWeapon()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];
	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		return (cell)player->getOnFootSyncData()->weapon;
	}
	return 0;
	//return _funcGetPlayerWeapon ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerArmour ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerArmour()" );
	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];


	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		float armour = amx_ctof( a_Params[ 2 ] );
		RakNet::BitStream bStream;

		bStream.Write( ( float )armour );
		__NetGame->PlayerRPC( RPC_SetPlayerArmour, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcSetPlayerArmour ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerArmour ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerArmour()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID ) a_Params[1];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		cell* ptr = 0;
		amx_GetAddr( a_AmxInterface, a_Params[ 2 ], &ptr );
		float armour = player->getArmour( );
		*ptr = amx_ftoc( armour );
	}
	return 0;
	//return _funcGetPlayerArmour ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerMapIcon ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerMapIcon()" );
	
	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: SetPlayerMapIcon(). Use RadarIcon Concept Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS( 8 );

	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];
	uint8_t iconID = ( uint8_t )a_Params[ 2 ];

	if( iconID >= MAX_MAP_ICON ) return 0;

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		RakNet::BitStream bStream;
		tVector position;

		bStream.Write( ( uint8_t ) iconID );		// iconid
		position.X	= amx_ctof( a_Params[ 3 ] );	// posX
		position.Y	= amx_ctof( a_Params[ 4 ] );	// posY
		position.Z	= amx_ctof( a_Params[ 5 ] );	// posZ
#ifdef _BIG_ENDIAN_SYSTEM
		bStream.Write(position.X);
		bStream.Write(position.Y);
		bStream.Write(position.Z);
#else
		bStream.Write( ( char* )&position, sizeof( tVector ) );
#endif
		bStream.Write( ( uint8_t ) a_Params[ 6 ] );		// markertype //
		bStream.Write( ( uint32_t ) a_Params[ 7 ] );	// color
		bStream.Write( ( uint8_t ) a_Params[ 8 ] );		// style // display

		__NetGame->PlayerRPC( RPC_SetPlayerMapIcon, &bStream, playerID, 2 );

		//logprintf ( "RadarIconCreate ( 0, %d, %d, 0x%X, %f, %f, %f, 0 );", a_Params[ 6 ], a_Params[ 8 ], a_Params[ 7 ], position.X, position.Y, position.Z );
		return 1;
	}
	return 0;
	//return _funcSetPlayerMapIcon ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcRemovePlayerMapIcon ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcRemovePlayerMapIcon()" );

	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: RemovePlayerMapIcon(). Use RadarIcon Concept Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];
	uint8_t iconID = ( uint8_t )a_Params[ 2 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) && iconID < MAX_MAP_ICON )
	{
		RakNet::BitStream bStream;
		bStream.Write( ( uint8_t ) iconID );
		__NetGame->PlayerRPC( RPC_RemovePlayerMapIcon, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcRemovePlayerMapIcon ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerKeys ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerKeys()" );
	CHECK_PARAMS( 4 );
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];


	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );

		uint32_t keys = 0, leftright = 0, updown = 0;

		switch( player->getState( ) )
		{
		case PLAYER_STATE_ONFOOT:
			{
				leftright	= player->getOnFootSyncData( )->leftRightKeysOnfoot;
				updown		= player->getOnFootSyncData( )->updownKeysOnfoot;
				keys		= player->getOnFootSyncData( )->keysOnfoot;
				break;
			}
		case PLAYER_STATE_DRIVER:
			{
				leftright	= player->getInVehicleSyncData( )->leftRightKeysOnVehicle;
				updown		= player->getInVehicleSyncData( )->updownKeysOnVehicle;
				keys		= player->getInVehicleSyncData( )->keysOnVehicle;
				break;
			}
		case PLAYER_STATE_PASSENGER:
			{
				leftright	= player->getPassengerSyncData( )->leftRightKeysPassenger;
				updown		= player->getPassengerSyncData( )->updownKeysPassenger;
				keys		= player->getPassengerSyncData( )->passengersKeys;
				break;
			}
		case PLAYER_STATE_SPECTATING:
			{
				leftright	= player->getSpectatingSyncData( )->leftRightKeysOnSpectating;
				updown		= player->getSpectatingSyncData( )->updownKeysOnSpectating;
				keys		= player->getSpectatingSyncData( )->keysOnSpectating;
				break;
			}
		default: 
			{
				return 0;
				break;
			}
		}

		cell* ptr = 0;

		amx_GetAddr( a_AmxInterface, a_Params[ 2 ], &ptr );
		*ptr = ( cell )keys;
		amx_GetAddr( a_AmxInterface, a_Params[ 3 ], &ptr );
		*ptr = ( cell )updown;
		amx_GetAddr( a_AmxInterface, a_Params[ 4 ], &ptr );
		*ptr = ( cell )leftright;
		return 1;
	}
	return 0;
//	return _funcGetPlayerKeys ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerMarkerForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerMarkerForPlayer()" );
	CHECK_PARAMS( 3 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		RakNet::BitStream bStream;

		bStream.Write( ( _PlayerID ) a_Params[ 2 ] );
		bStream.Write( ( uint32_t ) a_Params[ 3 ] );

		__NetGame->PlayerRPC( RPC_SetPlayerColor, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcSetPlayerMarkerForPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerAmmo ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerAmmo()" );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		int slot = player->GetWeaponSlot( player->GetCurrentWeapon( ) );
		if( slot != -1 )
		{
			return ( cell )player->GetAmmoInSlot( slot );
		}
		return 0;
	}
	return 0;
//	return _funcGetPlayerAmmo ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerAmmo ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerAmmo()" );
	CHECK_PARAMS( 3 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];


	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		RakNet::BitStream bStream;

		bStream.Write( ( uint8_t ) a_Params[ 2 ] );
		bStream.Write( ( uint16_t ) a_Params[ 3 ] );

		__NetGame->PlayerRPC( RPC_SetPlayerAmmo, &bStream, playerID, 0 );
		return 1;
	}
	return 0;
	//return _funcSetPlayerAmmo ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerWeaponData ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerWeaponData()" );
	CHECK_PARAMS( 4 );
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		uint32_t slot = ( uint32_t )a_Params[ 2 ];
		if( slot < 13 )
		{
			CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
			if( player == 0 ) return 0;

			cell* ptr = 0;
			amx_GetAddr( a_AmxInterface, a_Params[ 3 ], &ptr );
			*ptr = player->GetWeaponInSlot( slot );
			amx_GetAddr( a_AmxInterface, a_Params[ 4 ], &ptr );
			*ptr = player->GetAmmoInSlot( slot );
			return 1;
		}
	}
	return 0;
//	return _funcGetPlayerWeaponData ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerWeaponState ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerWeaponState()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		if( player->getState( ) == PLAYER_STATE_ONFOOT )
		{
			return ( cell )( player->getAimSyncData( )->weaponState >> 6 );
		}
	}
	return 0;
	//return _funcGetPlayerWeaponState ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcAllowPlayerTeleport ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcAllowPlayerTeleport()" );
	CHECK_PARAMS( 2 );

	logprintf( "AllowPlayerTeleport was disable since SA-MP 0.3d, use OnPlayerClickMap callback" );

	//_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	//if( __NetGame->playerPool->GetSlotState( playerID ) )
	//{
	//	CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
	//	if( player == 0 ) return 0;

	//	player->allowTeleport( a_Params[ 2 ] != 0 );
	//	return 1;
	//}
	return 0;
	//return _funcAllowPlayerTeleport ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcForceClassSelection ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcForceClassSelection()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		RakNet::BitStream bStream;
	
		__NetGame->PlayerRPC( RPC_ForceClassSelection, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
//	return _funcForceClassSelection ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerWantedLevel ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerWantedLevel()" );
	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		player->setWantedLevel( ( uint8_t )a_Params[ 2 ] );

		RakNet::BitStream bStream;
		bStream.Write( ( uint8_t )a_Params[ 2 ] );

		__NetGame->PlayerRPC( RPC_SetPlayerWantedLevel, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcSetPlayerWantedLevel ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerWantedLevel ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerWantedLevel()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		return ( cell )player->getWantedLevel( );
	}
	return 0;
	//	return _funcGetPlayerWantedLevel ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerFightingStyle ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerFightingStyle()" );
	CHECK_PARAMS( 1 );
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		return player->getFightingStyle( );

	}
	return 4;
	//return _funcGetPlayerFightingStyle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerFightingStyle ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerFightingStyle()" );
	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];
	uint8_t fightingStyle = ( uint8_t ) a_Params[ 2 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) &&  (fightingStyle == 4 || fightingStyle == 5 || fightingStyle == 6 || fightingStyle == 7 || fightingStyle == 15 || fightingStyle == 16 ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		player->setFightingStyle( fightingStyle );

		RakNet::BitStream bStream;
		bStream.Write( ( _PlayerID ) playerID );
		bStream.Write( ( uint8_t ) fightingStyle );
		__NetGame->AddedPlayersRPC( RPC_SetPlayerFightingStyle, &bStream, playerID, 2 );
		__NetGame->PlayerRPC( RPC_SetPlayerFightingStyle, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//	return _funcSetPlayerFightingStyle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerVelocity ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerVelocity()" );
	CHECK_PARAMS( 4 );
	
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) ) 
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		if( player->getState( ) == PLAYER_STATE_ONFOOT )
		{
			cell* ptr = 0;
			float tmp = 0.0f;
			tmp = player->getVelocity( )->X;
			amx_GetAddr( a_AmxInterface, a_Params[ 2 ], &ptr );
			*ptr = amx_ftoc( tmp );

			tmp = player->getVelocity( )->Y;
			amx_GetAddr( a_AmxInterface, a_Params[ 3 ], &ptr );
			*ptr = amx_ftoc( tmp );

			tmp = player->getVelocity( )->Z;
			amx_GetAddr( a_AmxInterface, a_Params[ 4 ], &ptr );
			*ptr = amx_ftoc( tmp );
			return 1;
		}
		else
		{
			cell* ptr = 0;
			amx_GetAddr( a_AmxInterface, a_Params[ 2 ], &ptr );
			*ptr = 0;
			amx_GetAddr( a_AmxInterface, a_Params[ 3 ], &ptr );
			*ptr = 0;
			amx_GetAddr( a_AmxInterface, a_Params[ 4 ], &ptr );
			*ptr = 0;
		}
	}
	return 0;
	//return _funcGetPlayerVelocity ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerVelocity ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerVelocity()" );
	CHECK_PARAMS( 4 );
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		
		RakNet::BitStream bStream;
		bStream.Write( ( float ) amx_ctof( a_Params[ 2 ] ) );
		bStream.Write( ( float ) amx_ctof( a_Params[ 3 ] ) );
		bStream.Write( ( float ) amx_ctof( a_Params[ 4 ] ) );
		__NetGame->PlayerRPC( RPC_SetPlayerVelocity, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcSetPlayerVelocity ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcIsPlayerInRangeOfPoint ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcIsPlayerInRangeOfPoint()" );
	CHECK_PARAMS( 5 );
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		if( player->getSquaredDistanceFrom3DPoint( amx_ctof( a_Params[ 3 ] ), amx_ctof( a_Params[ 4 ] ), amx_ctof( a_Params[ 5 ] ) ) <= amx_ctof( a_Params[ 2 ] ) * amx_ctof( a_Params[ 2 ] ) )
			return 1;
	}
	return 0;
	//return _funcIsPlayerInRangeOfPoint ( a_AmxInterface, a_Params );
}


cell AMX_NATIVE_CALL funcSetPlayerVirtualWorld ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerVirtualWorld()" );
	CHECK_PARAMS( 2 );
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		__NetGame->playerPool->setPlayerVirtualWorld( playerID, a_Params[ 2 ] );
		return 1;
	}
	return 0;
	//return _funcSetPlayerVirtualWorld ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerVirtualWorld ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerVirtualWorld()" );
	CHECK_PARAMS( 1 );
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		return __NetGame->playerPool->getPlayerVirtualWorld( playerID );
	}
	return 0;
	//return _funcGetPlayerVirtualWorld ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcShowPlayerNameTagForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcShowPlayerNameTagForPlayer()" );
	CHECK_PARAMS( 3 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		RakNet::BitStream bStream;

		bStream.Write( ( _PlayerID ) a_Params[ 2 ] );
		bStream.Write( ( uint8_t ) a_Params[ 3 ] );
		__NetGame->PlayerRPC( RPC_ShowPlayerNameTagForPlayer, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcShowPlayerNameTagForPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcEnableStuntBonusForAll ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcEnableStuntBonusForAll()" );
	CHECK_PARAMS( 1 );
	if( a_Params[ 1 ] != 1 ) a_Params[ 1 ] = 0;

	__NetGame->enableBonusStuntForAll = ( bool )( a_Params[ 1 ] == 0 ? false : true );

	
	RakNet::BitStream bStream;

	bStream.Write( ( bool )( a_Params[ 1 ] ? true : false ) );
	__NetGame->GlobalRPC( RPC_EnableStuntBonus, &bStream, -1, 2 );
	//if( a_Params[ 1 ] )
	//	bStream.Write( true );
	//else 
	//	bStream.Write( false );
	return 1;
	//return _funcEnableStuntBonusForAll ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcEnableStuntBonusForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcEnableStuntBonusForPlayer()" );
	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		if( a_Params[ 2 ] != 1 ) a_Params[ 2 ] = 0;

		RakNet::BitStream bStream;

		bStream.Write( ( bool )( a_Params[ 2 ] ? true : false ) );
		__NetGame->PlayerRPC( RPC_EnableStuntBonus, &bStream, playerID, 2 );
		return 1;
	}
	return 0;	
	//	return _funcEnableStuntBonusForPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcTogglePlayerSpectating ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcTogglePlayerSpectating()" );
	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		player->setSpectateID( -1 );
		player->setSpectatingType( SPECTATE_TYPE_NONE );

		RakNet::BitStream bStream;

		bStream.Write( ( uint32_t ) a_Params[ 2 ] );
		__NetGame->PlayerRPC( RPC_TogglePlayerSpectating, &bStream, playerID, 2 );

		return 1;
	}
	return 0;
	//return _funcTogglePlayerSpectating ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerDrunkLevel ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerDrunkLevel()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];
	return __NetGame->playerPool->getPlayerDrunkLevel( playerID );
	//return _funcGetPlayerDrunkLevel ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerDrunkLevel ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerDrunkLevel()" );
	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) ) 
	{
		RakNet::BitStream bStream;

		bStream.Write( ( uint32_t ) a_Params[ 2 ] );
		__NetGame->PlayerRPC( RPC_SetPlayerDrunkLevel, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcSetPlayerDrunkLevel ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcPlayerSpectateVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcPlayerSpectateVehicle()" );
	CHECK_PARAMS( 3 );
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];
	_VehicleID vehicleID = ( _VehicleID ) a_Params[ 2 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) && __NetGame->vehiclePool->GetSlotState( vehicleID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		CVehicle* vehicle = __NetGame->vehiclePool->GetVehicle( vehicleID );
		if( vehicle == 0 ) return 0;

		player->setSpectateID( vehicleID );
		player->setSpectatingType( SPECTATE_TYPE_VEHICLE );

		player->UpdatePosition( vehicle->vehPos.X, vehicle->vehPos.Y, vehicle->vehPos.Z, true );
		player->SetPlaceToBe( vehicle->vehPos.X, vehicle->vehPos.Y, vehicle->vehPos.Z );
		player->setState( PLAYER_STATE_SPECTATING );

		
		RakNet::BitStream bStream;

		bStream.Write( vehicleID );
		bStream.Write( ( uint8_t ) a_Params[ 3 ] );

		__NetGame->PlayerRPC( RPC_SetPlayerSpectatingVehicle, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
//	return _funcPlayerSpectateVehicle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcPlayerSpectatePlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcPlayerSpectatePlayer()" );
	CHECK_PARAMS( 3 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ], playerIDToSpectate = ( _PlayerID ) a_Params[ 2 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) && __NetGame->playerPool->GetSlotState( playerIDToSpectate ) )
	{
		CPlayer *player = __NetGame->playerPool->GetPlayer( playerID ), *playerToSpectate = __NetGame->playerPool->GetPlayer( playerIDToSpectate );
		
		if( player == 0 || playerToSpectate == 0 ) return 0;

		player->setSpectateID( playerIDToSpectate );
		player->setSpectatingType( SPECTATE_TYPE_PLAYER );

		player->UpdatePosition( playerToSpectate->getPosition( )->X, playerToSpectate->getPosition( )->Y, playerToSpectate->getPosition( )->Z, true );
		player->SetPlaceToBe( playerToSpectate->getPosition( )->X, playerToSpectate->getPosition( )->Y, playerToSpectate->getPosition( )->Z );
		player->setState( PLAYER_STATE_SPECTATING );

		
		RakNet::BitStream bStream;

		bStream.Write( playerIDToSpectate );
		bStream.Write( ( uint8_t ) a_Params[ 3 ] );
		__NetGame->PlayerRPC( RPC_SetPlayerSpectatingPlayer, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcPlayerSpectatePlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcApplyAnimation ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcApplyAnimation()" );
	CHECK_PARAMS( 10 );
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		char *animlib = 0, *animname = 0;
		amx_StrParam( a_AmxInterface, a_Params[ 2 ], animlib );
		amx_StrParam( a_AmxInterface, a_Params[ 3 ], animname );

		RakNet::BitStream bStream;
		

		bStream.Write( playerID );
		bStream.Write( ( uint8_t ) strlen( animlib ) );
		bStream.Write( ( char* ) animlib, strlen( animlib ) );
		bStream.Write( ( uint8_t ) strlen( animname ) );
		bStream.Write( ( char* ) animname, strlen( animname ) );

		bStream.Write( ( float ) amx_ctof( a_Params[ 4 ] ) );
		bStream.Write( ( bool )( a_Params[ 5 ] != 0 ? true : false ) );
		bStream.Write( ( bool )( a_Params[ 6 ] != 0 ? true : false ) );
		bStream.Write( ( bool )( a_Params[ 7 ] != 0 ? true : false ) );
		bStream.Write( ( bool )( a_Params[ 8 ] != 0 ? true : false ) );
		bStream.Write( ( bool )( a_Params[ 9 ] != 0 ? true : false ) );

		if( a_Params[ 10 ] /*|| *(uint32*)( player + 0x5014 )*/ )
		{
			__NetGame->PlayerRPC( RPC_ApplyAnimation, &bStream, playerID, 2 );
		}
		__NetGame->AddedPlayersRPC( RPC_ApplyAnimation, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcApplyAnimation ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcClearAnimations ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcClearAnimations()" );
	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		RakNet::BitStream bStream;
		
		bStream.Write( playerID );

		if( a_Params[ 2 ] /*|| *(uint32*)( player + 0x5014 )*/ )
		{
			__NetGame->AddedPlayersRPC( RPC_ClearAnimation, &bStream, playerID, 2 );
		}
		__NetGame->PlayerRPC( RPC_ClearAnimation, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcClearAnimations ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerAnimationIndex ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerAnimationIndex()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];
	
	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		if( player->getState( ) == PLAYER_STATE_ONFOOT )
		{
			return player->getOnFootSyncData( )->animationIndex;
		}

	}

	return 0;
	//return _funcGetPlayerAnimationIndex ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetAnimationName ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetAnimationName()" );
	CHECK_PARAMS( 5 );

	char* animationName = GetAnimationNameByIndex( a_Params[ 1 ] );

	if( animationName )
	{
		char* delim = strchr( animationName, ':' );
		if( delim )
		{
			char *animlib = new char[ delim - animationName ], *animname = new char[ strlen( animationName ) - ( delim - animationName ) + 1 ];
			strncpy( animlib, animationName, delim - animationName );
			strncpy( animname, &animationName[ delim - animationName + 1 ], strlen( animationName ) - ( delim - animationName ) + 1 ); // GOD :o

			cell* dest = 0;
			amx_GetAddr( a_AmxInterface, a_Params[2], &dest );
			amx_SetString( dest, animlib, 0, 0, a_Params[ 3 ] );
			amx_GetAddr( a_AmxInterface, a_Params[4], &dest );
			amx_SetString( dest, animlib, 0, 0, a_Params[ 5 ] );
			return 1;
		}
	}
	return 0;
	//return _funcGetAnimationName ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerSpecialAction ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerSpecialAction()" );
	CHECK_PARAMS( 2 );
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		
		RakNet::BitStream bStream;
		bStream.Write( ( uint8_t )a_Params[ 2 ] );

		__NetGame->PlayerRPC( RPC_SetPlayerSpecialAction, &bStream, playerID, 2 );

		return 1;
	}
	return 0;
	//return _funcSetPlayerSpecialAction ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerSpecialAction ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerSpecialAction()" );
	CHECK_PARAMS( 1 );
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		if( player->getState( ) == PLAYER_STATE_ONFOOT )
		{
			return ( cell )player->getOnFootSyncData( )->specialAction;	
		}
	}
	return 0;
	//return _funcGetPlayerSpecialAction ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcStartRecordingPlayerData ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcStartRecordingPlayerData()" );
	CHECK_PARAMS( 3 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		char* recordname = 0;
		amx_StrParam( a_AmxInterface, a_Params[ 3 ], recordname );
		player->startNPCRecordingData( a_Params[ 2 ], recordname );
		return 1;
	}
	return 0;
	//return _funcStartRecordingPlayerData ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcStopRecordingPlayerData ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcStopRecordingPlayerData()" );
	CHECK_PARAMS(1 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		player->stopNPCRecordingData( );
		return 1;
	}
	return 0;
	//return _funcStopRecordingPlayerData ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcPlayCrimeReportForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcPlayCrimeReportForPlayer()" );
	CHECK_PARAMS( 3 );

	_PlayerID playerID = (_PlayerID) a_Params[ 1 ], suspectID = (_PlayerID) a_Params[ 2 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) && __NetGame->playerPool->GetSlotState( suspectID ) )
	{
		CPlayer* suspect = __NetGame->playerPool->GetPlayer( suspectID );
		if( suspect == 0 ) return 0;
		
		RakNet::BitStream bStream;

		if( suspect->getState( ) == PLAYER_STATE_DRIVER || suspect->getState( ) == PLAYER_STATE_PASSENGER )
		{
			
			if( __NetGame->vehiclePool->GetSlotState( suspect->getCurrentVehicleID( ) ) )
			{
				CVehicle* vehicle = __NetGame->vehiclePool->GetVehicle( suspect->getCurrentVehicleID( ) );
				if( vehicle == 0 ) return 0;

				uint32_t color = vehicle->vehModInfo.vehColor1;
				if( color == -1 )
					color = vehicle->GetSpawnInfo()->vehColor1;

				bStream.Write( suspectID );
				bStream.Write( (uint32_t)1 );
				bStream.Write( ( uint32_t ) vehicle->GetSpawnInfo()->vehType );
				bStream.Write( ( uint32_t ) color );
				bStream.Write( ( uint32_t ) a_Params[ 3 ] );
				bStream.Write( ( float ) vehicle->vehPos.X );
				bStream.Write( ( float ) vehicle->vehPos.Y );
				bStream.Write( ( float ) vehicle->vehPos.Z );

			}
			else
				return 0;
		}
		else if( suspect->getState( ) == PLAYER_STATE_ONFOOT )
		{
			bStream.Write( suspectID );
			bStream.Write( ( uint32_t ) 0 );
			bStream.Write( ( uint32_t ) 0 );
			bStream.Write( ( uint32_t ) 0 );
			bStream.Write( ( uint32_t ) a_Params[ 3 ] );
			bStream.Write( ( float ) suspect->getPosition( )->X );
			bStream.Write( ( float ) suspect->getPosition( )->Y );
			bStream.Write( ( float ) suspect->getPosition( )->Z );
		}

		__NetGame->PlayerRPC( RPC_PlayCrimeReportForPlayer, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcPlayCrimeReportForPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerShopName ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerShopName()" );
	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		char* str = 0;
		amx_StrParam( a_AmxInterface, a_Params[ 2 ], str );
		if( strlen( str ) <= 31 )
		{
			RakNet::BitStream bStream;
			bStream.Write( str, 32 );
			__NetGame->PlayerRPC( RPC_SetPlayerShopName, &bStream, playerID, 2 );
			return 1;
		}

	}
	return 0;
	//return _funcSetPlayerShopName ( a_AmxInterface, a_Params );
}


cell AMX_NATIVE_CALL funcSetPlayerSkillLevel ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerSkillLevel()" );

	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];
	uint32_t skillID = a_Params[ 2 ];
	uint16_t skillLevel = ( uint16_t )a_Params[ 3 ];
	CPlayer* player = 0;
	if( ( player = __NetGame->playerPool->GetPlayer( playerID ) ) > 0 )
	{
		player->setSkillLevel( skillID, skillLevel );
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL funcGetPlayerTeam ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerTeam()" );

	_PlayerID playerID = (_PlayerID)a_Params[1];

	if( __NetGame->playerPool->GetSlotState( playerID ) == false ) return 0xFF;

	return (cell)__NetGame->playerPool->GetPlayer( playerID )->getCustomSpawn( )->Team;
}

cell AMX_NATIVE_CALL funcGetPlayerSurfingVehicleID ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerSurfingVehicleID()" );

	_PlayerID playerID = (_PlayerID)a_Params[ 1 ];
	if( __NetGame->playerPool->GetSlotState( playerID ) == false ) return 0xFFFF;

	CPlayer* player = __NetGame->playerPool->GetPlayer( playerID ) ;
	if( player == 0 ) return 0xFFFF;


	if( player->isOnFoot( ) )
	{
		return player->getOnFootSyncData( )->surfingVehicleID;
	}


	return 0xFFFF;//_funcGetPlayerSurfingVehicleID ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcIsPlayerConnected ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 1 );
	//if(bScriptDebug) logprintf ( "[Call]-> funcIsPlayerConnected()" );

	_PlayerID playerID = (_PlayerID)a_Params[ 1 ];

	if( 0 > playerID || playerID >= MAX_PLAYERS ) return 0;

	return (cell)( __NetGame->playerPool->GetSlotState( playerID ) ? 1 : 0 );//_funcIsPlayerConnected ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcIsPlayerStreamedIn ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcIsPlayerStreamedIn()" );

	CHECK_PARAMS( 2 );

	_PlayerID playerID = (_PlayerID)a_Params[1], forplayerID = (_PlayerID)a_Params[2];
	if( 0 > playerID || 0 > forplayerID || playerID >= MAX_PLAYERS || forplayerID >= MAX_PLAYERS ) return 0;

	CPlayer* player = __NetGame->playerPool->GetPlayer( forplayerID );
	if( player == 0 ) return 0;

	return ( cell )( player->isPlayerStreamedIn( playerID ) ? 1 : 0 );
}

cell AMX_NATIVE_CALL funcIsVehicleStreamedIn ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcIsVehicleStreamedIn()" );

	uint16_t vehicleID = (uint16_t)a_Params[ 1 ];
	_PlayerID forplayerID = (_PlayerID)a_Params[ 2 ];

	if( 0 > vehicleID || vehicleID >= MAX_VEHICLES || __NetGame->playerPool->GetSlotState( forplayerID ) == false ) return 0;


	CPlayer* player = __NetGame->playerPool->GetPlayer( forplayerID );
	if( player == 0 ) return 0; // inutile mais je m'en fous
	


	return (cell)( player->isVehicleStreamedIn( vehicleID ) ? 1 : 0 );//_funcIsVehicleStreamedIn ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcGetPlayerNetworkStats ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerNetworkStats()" );
	CHECK_PARAMS( 3 );

	if(!__NetGame || !__NetGame->playerPool) return 0;

	_PlayerID playerId = (_PlayerID)a_Params[1];

	if(__NetGame->playerPool->GetSlotState(playerId))
	{
		char* szSvrDispBuf = new char[a_Params[ 3 ] + 1];
		RakNetStatisticsStruct* RakServerStats;

		RakServerStats = __NetGame->rakServerInterface->GetStatistics(__NetGame->rakServerInterface->GetPlayerIDFromIndex(playerId));

		StatisticsToString(RakServerStats, szSvrDispBuf, 1);

		cell* dest = 0;
		amx_GetAddr( a_AmxInterface, a_Params[2], &dest );
		amx_SetString( dest, szSvrDispBuf, 0, 0, a_Params[ 3 ] );

		delete [] szSvrDispBuf;
	}

	return 1;
}
