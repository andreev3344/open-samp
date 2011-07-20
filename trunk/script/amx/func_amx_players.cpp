#include "../../main.h"
#include "../../../SDK/amx/amx.h"

#include "../func_amx.h"
#include "func_amx_players.h"


//cell ( __cdecl* _funcIsPlayerConnected )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsPlayerConnected;
//cell ( __cdecl* _funcIsPlayerStreamedIn )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsPlayerStreamedIn;
//cell ( __cdecl* _funcIsVehicleStreamedIn )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsVehicleStreamedIn;
//cell ( __cdecl* _funcGetPlayerSurfingVehicleID )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerSurfingVehicleID;
//cell ( __cdecl* _funcGetPlayerTeam )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerTeam;
//cell ( __cdecl* _funcSetPlayerSkillLevel )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerSkillLevel;


cell AMX_NATIVE_CALL funcSetPlayerSkillLevel ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerSkillLevel()" );

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
	logprintf ( "[Call]-> funcGetPlayerTeam()" );

	_PlayerID playerID = (_PlayerID)a_Params[1];

	if( __NetGame->playerPool->GetSlotState( playerID ) == false ) return 0xFF;

	return (cell)__NetGame->playerPool->GetPlayer( playerID )->customSpawn.Team;
}

cell AMX_NATIVE_CALL funcGetPlayerSurfingVehicleID ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerSurfingVehicleID()" );

	_PlayerID playerID = (_PlayerID)a_Params[ 1 ];
	if( __NetGame->playerPool->GetSlotState( playerID ) == false ) return 0xFFFF;

	CPlayer* player = __NetGame->playerPool->GetPlayer( playerID ) ;
	if( player == 0 ) return 0xFFFF;


	if( player->isOnFoot( ) )
	{
		return player->onFootSyncData.surfingVehicleID;
	}


	return 0xFFFF;//_funcGetPlayerSurfingVehicleID ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcIsPlayerConnected ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 1 );
	//logprintf ( "[Call]-> funcIsPlayerConnected()" );

	_PlayerID playerID = (_PlayerID)a_Params[ 1 ];

	if( 0 > playerID || playerID >= MAX_PLAYERS ) return 0;

	return (cell)( __NetGame->playerPool->GetSlotState( playerID ) ? 1 : 0 );//_funcIsPlayerConnected ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcIsPlayerStreamedIn ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsPlayerStreamedIn()" );

	CHECK_PARAMS( 2 );

	_PlayerID playerID = (_PlayerID)a_Params[1], forplayerID = (_PlayerID)a_Params[2];
	if( 0 > playerID || 0 > forplayerID || playerID >= MAX_PLAYERS || forplayerID >= MAX_PLAYERS ) return 0;

	CPlayer* player = __NetGame->playerPool->GetPlayer( forplayerID );
	if( player == 0 ) return 0;

	return player->isPlayerStreamedIn( playerID );
}

cell AMX_NATIVE_CALL funcIsVehicleStreamedIn ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsVehicleStreamedIn()" );

	uint16_t vehicleID = (uint16_t)a_Params[ 1 ];
	_PlayerID forplayerID = (_PlayerID)a_Params[ 2 ];

	if( 0 > vehicleID || vehicleID >= MAX_VEHICLES || __NetGame->playerPool->GetSlotState( forplayerID ) == false ) return 0;


	CPlayer* player = __NetGame->playerPool->GetPlayer( forplayerID );
	if( player == 0 ) return 0; // inutile mais je m'en fous
	


	return (cell)( player->isVehicleStreamedIn( vehicleID ) ? 1 : 0 );//_funcIsVehicleStreamedIn ( a_AmxInterface, a_Params );
}