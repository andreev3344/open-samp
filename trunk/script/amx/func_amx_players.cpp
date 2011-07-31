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
//cell ( __cdecl* _funcSetPlayerName )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerName;
cell ( __cdecl* _funcSetPlayerSkin )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerSkin;
cell ( __cdecl* _funcGetPlayerSkin )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerSkin;
cell ( __cdecl* _funcGetPlayerPos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerPos;
cell ( __cdecl* _funcSetPlayerPos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerPos;
cell ( __cdecl* _funcSetPlayerPosFindZ )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerPosFindZ;
cell ( __cdecl* _funcGetPlayerHealth )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerHealth;
cell ( __cdecl* _funcSetPlayerHealth )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerHealth;
cell ( __cdecl* _funcSetPlayerColor )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerColor;
cell ( __cdecl* _funcGetPlayerColor )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerColor;
cell ( __cdecl* _funcGetPlayerVehicleID )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerVehicleID;
cell ( __cdecl* _funcGetPlayerVehicleSeat )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerVehicleSeat;

cell ( __cdecl* _funcPutPlayerInVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_PutPlayerInVehicle;
cell ( __cdecl* _funcRemovePlayerFromVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_RemovePlayerFromVehicle;
cell ( __cdecl* _funcIsPlayerInVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsPlayerInVehicle;
cell ( __cdecl* _funcIsPlayerInAnyVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsPlayerInAnyVehicle;
cell ( __cdecl* _funcGetPlayerName )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerName;
cell ( __cdecl* _funcSetPlayerCheckpoint )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerCheckpoint;
cell ( __cdecl* _funcDisablePlayerCheckpoint )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DisablePlayerCheckpoint;
cell ( __cdecl* _funcIsPlayerInCheckpoint )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsPlayerInCheckpoint;
cell ( __cdecl* _funcSetPlayerRaceCheckpoint )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerRaceCheckpoint;
cell ( __cdecl* _funcDisablePlayerRaceCheckpoint )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DisablePlayerRaceCheckpoint;
cell ( __cdecl* _funcIsPlayerInRaceCheckpoint )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsPlayerInRaceCheckpoint;
cell ( __cdecl* _funcSetPlayerInterior )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerInterior;
cell ( __cdecl* _funcGetPlayerInterior )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerInterior;
cell ( __cdecl* _funcSetPlayerAttachedObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerAttachedObject;
cell ( __cdecl* _funcRemovePlayerAttachedObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_RemovePlayerAttachedObject;
cell ( __cdecl* _funcIsPlayerAttachedObjectSlotUsed )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsPlayerAttachedObjectSlotUsed;
cell ( __cdecl* _funcSetPlayerCameraLookAt )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerCameraLookAt;
cell ( __cdecl* _funcSetPlayerCameraPos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerCameraPos;
cell ( __cdecl* _funcSetCameraBehindPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetCameraBehindPlayer;
cell ( __cdecl* _funcGetPlayerCameraPos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerCameraPos;
cell ( __cdecl* _funcGetPlayerCameraFrontVector )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerCameraFrontVector;
cell ( __cdecl* _funcTogglePlayerControllable )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_TogglePlayerControllable;
cell ( __cdecl* _funcPlayerPlaySound )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_PlayerPlaySound;
cell ( __cdecl* _funcSetPlayerScore )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerScore;
cell ( __cdecl* _funcGetPlayerScore )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerScore;
cell ( __cdecl* _funcSetPlayerFacingAngle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerFacingAngle;
cell ( __cdecl* _funcGetPlayerFacingAngle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerFacingAngle;
cell ( __cdecl* _funcGivePlayerMoney )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GivePlayerMoney;
cell ( __cdecl* _funcGetPlayerMoney )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerMoney;
cell ( __cdecl* _funcResetPlayerMoney )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ResetPlayerMoney;

cell ( __cdecl* _funcGetPlayerState )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerState;
cell ( __cdecl* _funcResetPlayerWeapons )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ResetPlayerWeapons;
cell ( __cdecl* _funcGivePlayerWeapon )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GivePlayerWeapon;
cell ( __cdecl* _funcSetPlayerArmedWeapon )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerArmedWeapon;
cell ( __cdecl* _funcGetPlayerIp )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerIp;
cell ( __cdecl* _funcGetPlayerPing )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerPing;
cell ( __cdecl* _funcGetPlayerWeapon )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerWeapon;
cell ( __cdecl* _funcSetPlayerArmour )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerArmour;
cell ( __cdecl* _funcGetPlayerArmour )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerArmour;
cell ( __cdecl* _funcSetPlayerMapIcon )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerMapIcon;
cell ( __cdecl* _funcRemovePlayerMapIcon )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_RemovePlayerMapIcon;
cell ( __cdecl* _funcGetPlayerKeys )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerKeys;
cell ( __cdecl* _funcSetPlayerMarkerForPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerMarkerForPlayer;
cell ( __cdecl* _funcGetPlayerAmmo )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerAmmo;
cell ( __cdecl* _funcSetPlayerAmmo )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerAmmo;
cell ( __cdecl* _funcGetPlayerWeaponData )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerWeaponData;
cell ( __cdecl* _funcGetPlayerWeaponState )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerWeaponState;
cell ( __cdecl* _funcAllowPlayerTeleport )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AllowPlayerTeleport;
cell ( __cdecl* _funcForceClassSelection )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ForceClassSelection;
cell ( __cdecl* _funcSetPlayerWantedLevel )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerWantedLevel;
cell ( __cdecl* _funcGetPlayerWantedLevel )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerWantedLevel;
cell ( __cdecl* _funcGetPlayerFightingStyle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerFightingStyle;
cell ( __cdecl* _funcSetPlayerFightingStyle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerFightingStyle;
cell ( __cdecl* _funcGetPlayerVelocity )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerVelocity;
cell ( __cdecl* _funcSetPlayerVelocity )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerVelocity;
cell ( __cdecl* _funcIsPlayerInRangeOfPoint )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsPlayerInRangeOfPoint;


cell ( __cdecl* _funcSetPlayerVirtualWorld )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerVirtualWorld;
cell ( __cdecl* _funcGetPlayerVirtualWorld )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerVirtualWorld;
cell ( __cdecl* _funcShowPlayerNameTagForPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ShowPlayerNameTagForPlayer;
cell ( __cdecl* _funcEnableStuntBonusForAll )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_EnableStuntBonusForAll;
cell ( __cdecl* _funcEnableStuntBonusForPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_EnableStuntBonusForPlayer;
cell ( __cdecl* _funcTogglePlayerSpectating )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_TogglePlayerSpectating;
cell ( __cdecl* _funcGetPlayerDrunkLevel )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerDrunkLevel;
cell ( __cdecl* _funcSetPlayerDrunkLevel )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerDrunkLevel;
cell ( __cdecl* _funcPlayerSpectateVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_PlayerSpectateVehicle;
cell ( __cdecl* _funcPlayerSpectatePlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_PlayerSpectatePlayer;
cell ( __cdecl* _funcApplyAnimation )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ApplyAnimation;
cell ( __cdecl* _funcClearAnimations )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ClearAnimations;
cell ( __cdecl* _funcGetPlayerAnimationIndex )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerAnimationIndex;
cell ( __cdecl* _funcGetAnimationName )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetAnimationName;
cell ( __cdecl* _funcSetPlayerSpecialAction )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerSpecialAction;
cell ( __cdecl* _funcGetPlayerSpecialAction )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerSpecialAction;
cell ( __cdecl* _funcStartRecordingPlayerData )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_StartRecordingPlayerData;
cell ( __cdecl* _funcStopRecordingPlayerData )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_StopRecordingPlayerData;
cell ( __cdecl* _funcPlayCrimeReportForPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_PlayCrimeReportForPlayer;
cell ( __cdecl* _funcSetPlayerShopName )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerShopName;


cell AMX_NATIVE_CALL funcSetPlayerName ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerName()" );
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
			uint32_t RPC_ChangeName = 0x0E;
			__NetGame->playerPool->setPlayerNick( playerID, new_nickname );
			logprintf( "[nick] %s nick changed to %s", old_nickname, new_nickname );
			CNetGame__RPC_SendToEveryPlayer( ( uint32_t ) __NetGame, &RPC_ChangeName, &bStream, -1, 2 );
			return 1;
		}
		return 0;

	}
	return -1;
}
cell AMX_NATIVE_CALL funcSetPlayerSkin ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerSkin()" );
	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		if( player->HasCustomSpawn( ) )
		{
			uint32_t RPC_SetPlayerSkin = 0x0D;
			RakNet::BitStream bStream;
			bStream.Write( ( uint32_t ) playerID );
			bStream.Write( ( uint32_t ) a_Params[ 2 ] );
			CNetGame__RPC_SendToUnknown( ( uint32_t )__NetGame, &RPC_SetPlayerSkin, &bStream, playerID, 2 );
			CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_SetPlayerSkin, &bStream, playerID, 2 );
		}
		player->getCustomSpawn( )->Skin = ( int )a_Params[ 2 ];
		return 1;
	}
	return 0;
}
cell AMX_NATIVE_CALL funcGetPlayerSkin ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerSkin()" );
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
	logprintf ( "[Call]-> funcGetPlayerPos()" );
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
	logprintf ( "[Call]-> funcSetPlayerPos()" );
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
	logprintf ( "[Call]-> funcSetPlayerPosFindZ()" );
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
	logprintf ( "[Call]-> funcGetPlayerHealth()" );
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
	logprintf ( "[Call]-> funcSetPlayerHealth()" );
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
	logprintf ( "[Call]-> funcSetPlayerColor()" );
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
	logprintf ( "[Call]-> funcGetPlayerColor()" );
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
	logprintf ( "[Call]-> funcGetPlayerVehicleID()" );
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
	logprintf ( "[Call]-> funcGetPlayerVehicleSeat()" );
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
	logprintf ( "[Call]-> funcPutPlayerInVehicle()" );
	return _funcPutPlayerInVehicle ( a_AmxInterface, a_Params );

	CHECK_PARAMS( 3 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];
	_VehicleID vehicleID = ( _VehicleID ) a_Params[ 2 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) && __NetGame->vehiclePool->GetSlotState( vehicleID ) )
	{
		RakNet::BitStream bStream;


		bStream.Write( ( _VehicleID ) vehicleID );
		bStream.Write( ( uint8_t ) a_Params[ 3 ] ); // seat

		void* vehicle = __NetGame->vehiclePool->GetVehicle( vehicleID );
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );

		if( vehicle && player )
		{
			// player->sub_491340( vehicle, 0.0f );
//			if( a_Params[ 3 ] == 0 )
//				vehicle->setDriver( playerID );
			player->setCurrentVehicleID( vehicleID );
			//player->UpdatePosition( vehicle->getPosition().X, vehicle->getPosition().Y, vehicle->getPosition().Z, true );
			//player->SetPlaceToBe( vehicle->getPosition().X, vehicle->getPosition().Y, vehicle->getPosition().Z );

			uint32_t RPC_SetPlayerInVehicle = 0x12;

			CNetGame__RPC_SendToPlayer( ( uint32_t ) __NetGame, &RPC_SetPlayerInVehicle, &bStream, playerID, 2 );
			return 1;
		}


	}
	return 0;
}
cell AMX_NATIVE_CALL funcRemovePlayerFromVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcRemovePlayerFromVehicle()" );
	CHECK_PARAMS( 1 );
	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		RakNet::BitStream bStream;
		uint32_t RPC_RemovePlayerFromPlayer = 0x13;
		CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_RemovePlayerFromPlayer, &bStream, playerID, 2 );
		return 1;
	}

	return 0;
}
cell AMX_NATIVE_CALL funcIsPlayerInVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsPlayerInVehicle()" );
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
	logprintf ( "[Call]-> funcIsPlayerInAnyVehicle()" );
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
	logprintf ( "[Call]-> funcGetPlayerName()" );
	CHECK_PARAMS( 3 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		return amx_SetString( &a_Params[ 2 ], __NetGame->playerPool->getPlayerNick( playerID ), 0, 1, a_Params[ 3 ] );
	}
	return 0;
}
cell AMX_NATIVE_CALL funcSetPlayerCheckpoint ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerCheckpoint()" );
/* playerID, posX, posY, posZ, size*/
	CHECK_PARAMS( 5 );

	_PlayerID playerID = (_PlayerID) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		tVector vecPos;
		vecPos.X = amx_ctof( a_Params[ 2 ] );
		vecPos.Y = amx_ctof( a_Params[ 3 ] );
		vecPos.Z = amx_ctof( a_Params[ 4 ] );
		player->setCheckpoint( vecPos, amx_ctof( a_Params[ 5 ] ) );

		return 1;
	}
	return 0;
}
cell AMX_NATIVE_CALL funcDisablePlayerCheckpoint ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDisablePlayerCheckpoint()" );
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
	logprintf ( "[Call]-> funcIsPlayerInCheckpoint()" );
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
	logprintf ( "[Call]-> funcSetPlayerRaceCheckpoint()" );
	CHECK_PARAMS( 9 );

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

		player->setRaceCheckpoint( ( uint8_t ) a_Params[ 2 ], vecPos, vecNext, amx_ctof( a_Params[ 9 ] ) );
		return 1;
	}

	return 0;
}
cell AMX_NATIVE_CALL funcDisablePlayerRaceCheckpoint ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDisablePlayerRaceCheckpoint()" );
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
	logprintf ( "[Call]-> funcIsPlayerInRaceCheckpoint()" );
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
	logprintf ( "[Call]-> funcSetPlayerInterior()" );

	_PlayerID playerID = ( _PlayerID ) a_Params[0];

	if( __NetGame->playerPool->GetSlotState( playerID ) ) 
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		uint32_t RPC_SetPlayerInterior = 0x16;
		RakNet::BitStream bStream;
		bStream.Write( ( uint8_t ) a_Params[ 2 ] );
		CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_SetPlayerInterior, &bStream, playerID, 2 );
		return 1;
	}

	return 0;
}
cell AMX_NATIVE_CALL funcGetPlayerInterior ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerInterior()" );
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
	logprintf ( "[Call]-> funcSetPlayerAttachedObject()" );

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
	logprintf ( "[Call]-> funcRemovePlayerAttachedObject()" );

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
	logprintf ( "[Call]-> funcIsPlayerAttachedObjectSlotUsed()" );

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
	logprintf ( "[Call]-> funcSetPlayerCameraLookAt()" );
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

		uint32_t RPC_SetPlayerCameralookAt = 0x18;

		RakNet::BitStream bStream;
		bStream.Write( ( char* ) &lookAt, sizeof( tVector ) );
		CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_SetPlayerCameralookAt, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcSetPlayerCameraLookAt ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerCameraPos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerCameraPos()" );
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

		uint32_t RPC_SetPlayerCameraPos = 0x17;

		RakNet::BitStream bStream;
		bStream.Write( ( char* ) &cameraPos, sizeof( tVector ) );
		CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_SetPlayerCameraPos, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
//	return _funcSetPlayerCameraPos ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetCameraBehindPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetCameraBehindPlayer()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;

		uint32_t RPC_SetPlayerCameraBehindPlayer = 0x1C;
		RakNet::BitStream bStream;
		CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_SetPlayerCameraBehindPlayer, &bStream, playerID, 2 );

		return 1;
	}
	return 0;
	//return _funcSetCameraBehindPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerCameraPos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerCameraPos()" );

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
	logprintf ( "[Call]-> funcGetPlayerCameraFrontVector()" );
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
	logprintf ( "[Call]-> funcTogglePlayerControllable()" );

	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		uint8_t toggle = ( uint8_t ) a_Params[ 2 ];

		uint32_t RPC_TogglePlayerControllable = 0x1D;

		RakNet::BitStream bStream;

		bStream.Write( ( uint8_t ) toggle );
		CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_TogglePlayerControllable, &bStream, playerID, 2 );

		return 1;
	}
	return 0;
//	return _funcTogglePlayerControllable ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcPlayerPlaySound ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcPlayerPlaySound()" );

	CHECK_PARAMS( 5 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		tVector position;
		uint32_t soundid	= a_Params[ 2 ];
		position.X			= amx_ctof( a_Params[ 3 ] );
		position.Y			= amx_ctof( a_Params[ 4 ] );
		position.Z			= amx_ctof( a_Params[ 5 ] );

		uint32_t RPC_PlayerPlaySound = 0x1E;

		RakNet::BitStream bStream;
		bStream.Write( ( uint32_t ) soundid );
		bStream.Write( ( char* )&position, sizeof( tVector ) );

		CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_PlayerPlaySound, &bStream, playerID, 2 );

		return 1;
	}
	return 0;
	//return _funcPlayerPlaySound ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerScore ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerScore()" );
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
	logprintf ( "[Call]-> funcGetPlayerScore()" );
	CHECK_PARAMS( 1 );
	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	return __NetGame->playerPool->getScore( playerID );
	//return _funcGetPlayerScore ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerFacingAngle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerFacingAngle()" );

	CHECK_PARAMS( 2 );


	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		RakNet::BitStream bStream;
		uint32_t RPC_SetPlayerFacingAngle = 0x21;
		bStream.Write( ( float )amx_ctof( a_Params[ 2 ] ) );
		CNetGame__RPC_SendToPlayer( ( uint32_t ) __NetGame, &RPC_SetPlayerFacingAngle, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcSetPlayerFacingAngle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerFacingAngle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerFacingAngle()" );
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
	logprintf ( "[Call]-> funcGivePlayerMoney()" );

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
	logprintf ( "[Call]-> funcGetPlayerMoney()" );
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
	logprintf ( "[Call]-> funcResetPlayerMoney()" );

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
	logprintf ( "[Call]-> funcGetPlayerState()" );
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
	logprintf ( "[Call]-> funcResetPlayerWeapons()" );
	CHECK_PARAMS( 1 );


	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		uint32_t RPC_ResetPlayerWeapons = 0x23;
		RakNet::BitStream bStream;
		CNetGame__RPC_SendToPlayer( ( uint32_t ) __NetGame, &RPC_ResetPlayerWeapons, &bStream, playerID, 2 );

		return 1;
	}
	return 0;
	//return _funcResetPlayerWeapons ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGivePlayerWeapon ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGivePlayerWeapon()" );

	CHECK_PARAMS( 3 );

	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		uint32_t RPC_GivePlayerWeapon = 0x24;
		RakNet::BitStream bStream;

		bStream.Write( ( uint32_t ) a_Params[2] );
		bStream.Write( ( uint32_t ) a_Params[3] );

		CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_GivePlayerWeapon, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcGivePlayerWeapon ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerArmedWeapon ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerArmedWeapon()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		uint32_t RPC_SetPlayerArmedWeapon = 0x0A;
		RakNet::BitStream bStream;
		bStream.Write( ( uint32_t ) a_Params[ 2 ] );

		CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_SetPlayerArmedWeapon, &bStream, playerID, 2 );
		return 1;
	}

	return 0;
//	return _funcSetPlayerArmedWeapon ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerIp ( AMX* a_AmxInterface, cell* a_Params ) // Need rakserverinterface
{
	logprintf ( "[Call]-> funcGetPlayerIp()" );
	return _funcGetPlayerIp ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerPing ( AMX* a_AmxInterface, cell* a_Params ) // Need rakserverinterface
{
	logprintf ( "[Call]-> funcGetPlayerPing()" );
	return _funcGetPlayerPing ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerWeapon ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerWeapon()" );
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
	logprintf ( "[Call]-> funcSetPlayerArmour()" );
	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];


	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		float armour = amx_ctof( a_Params[ 2 ] );
		uint32_t RPC_SetPlayerArmour = 0x27;
		RakNet::BitStream bStream;

		bStream.Write( ( float )armour );
		CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_SetPlayerArmour, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcSetPlayerArmour ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerArmour ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerArmour()" );
	CHECK_PARAMS( 1 );

	_PlayerID playerID = ( _PlayerID ) a_Params[1];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
		if( player == 0 ) return 0;
		cell* ptr = 0;
		amx_GetAddr( a_AmxInterface, a_Params[ 2 ], &ptr );
		*ptr = player->getArmour( );
	}
	return 0;
	//return _funcGetPlayerArmour ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerMapIcon ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerMapIcon()" );

	CHECK_PARAMS( 8 );

	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];
	uint8_t iconID = ( uint8_t )a_Params[ 2 ];

	if( iconID >= MAX_MAP_ICON ) return 0;

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		uint32_t RPC_SetPlayerMapIcon = 0x29;
		RakNet::BitStream bStream;
		tVector position;

		bStream.Write( ( uint8_t ) iconID );		// iconid
		position.X	= amx_ctof( a_Params[ 3 ] );	// posX
		position.Y	= amx_ctof( a_Params[ 4 ] );	// posY
		position.Z	= amx_ctof( a_Params[ 5 ] );	// posZ
		bStream.Write( ( char* )&position, sizeof( tVector ) );
		bStream.Write( ( uint8_t ) a_Params[ 6 ] );		// markertype
		bStream.Write( ( uint32_t ) a_Params[ 7 ] );	// color
		bStream.Write( ( uint8_t ) a_Params[ 8 ] );		// style

		CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_SetPlayerMapIcon, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcSetPlayerMapIcon ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcRemovePlayerMapIcon ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcRemovePlayerMapIcon()" );
	CHECK_PARAMS( 2 );

	_PlayerID playerID = ( _PlayerID )a_Params[ 1 ];
	uint8_t iconID = ( uint8_t )a_Params[ 2 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) && iconID < MAX_MAP_ICON )
	{
		uint32_t RPC_RemovePlayerMapIcon = 0x2A;
		RakNet::BitStream bStream;

		bStream.Write( ( uint8_t ) iconID );

		CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_RemovePlayerMapIcon, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcRemovePlayerMapIcon ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerKeys ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerKeys()" );
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
	logprintf ( "[Call]-> funcSetPlayerMarkerForPlayer()" );
	CHECK_PARAMS( 3 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];

	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		uint32_t RPC_SetPlayerColor = 0x14;
		RakNet::BitStream bStream;

		bStream.Write( ( _PlayerID ) a_Params[ 2 ] );
		bStream.Write( ( uint32_t ) a_Params[ 3 ] );

		CNetGame__RPC_SendToPlayer( ( uint32_t ) __NetGame, &RPC_SetPlayerColor, &bStream, playerID, 2 );
		return 1;
	}
	return 0;
	//return _funcSetPlayerMarkerForPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerAmmo ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerAmmo()" );

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
	logprintf ( "[Call]-> funcSetPlayerAmmo()" );
	CHECK_PARAMS( 3 );

	_PlayerID playerID = ( _PlayerID ) a_Params[ 1 ];


	if( __NetGame->playerPool->GetSlotState( playerID ) )
	{
		uint32_t RPC_SetPlayerAmmo = 0x2B;
		RakNet::BitStream bStream;

		bStream.Write( ( uint8_t ) a_Params[ 2 ] );
		bStream.Write( ( uint16_t ) a_Params[ 3 ] );

		CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_SetPlayerAmmo, &bStream, playerID, 0 );
		return 1;
	}
	return 0;
	//return _funcSetPlayerAmmo ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerWeaponData ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerWeaponData()" );
	return _funcGetPlayerWeaponData ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerWeaponState ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerWeaponState()" );
	return _funcGetPlayerWeaponState ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcAllowPlayerTeleport ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAllowPlayerTeleport()" );
	return _funcAllowPlayerTeleport ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcForceClassSelection ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcForceClassSelection()" );
	return _funcForceClassSelection ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerWantedLevel ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerWantedLevel()" );
	return _funcSetPlayerWantedLevel ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerWantedLevel ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerWantedLevel()" );
	return _funcGetPlayerWantedLevel ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerFightingStyle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerFightingStyle()" );
	return _funcGetPlayerFightingStyle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerFightingStyle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerFightingStyle()" );
	return _funcSetPlayerFightingStyle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerVelocity ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerVelocity()" );
	return _funcGetPlayerVelocity ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerVelocity ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerVelocity()" );
	return _funcSetPlayerVelocity ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcIsPlayerInRangeOfPoint ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsPlayerInRangeOfPoint()" );
	return _funcIsPlayerInRangeOfPoint ( a_AmxInterface, a_Params );
}


cell AMX_NATIVE_CALL funcSetPlayerVirtualWorld ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerVirtualWorld()" );
	return _funcSetPlayerVirtualWorld ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerVirtualWorld ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerVirtualWorld()" );
	return _funcGetPlayerVirtualWorld ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcShowPlayerNameTagForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcShowPlayerNameTagForPlayer()" );
	return _funcShowPlayerNameTagForPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcEnableStuntBonusForAll ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcEnableStuntBonusForAll()" );
	return _funcEnableStuntBonusForAll ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcEnableStuntBonusForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcEnableStuntBonusForPlayer()" );
	return _funcEnableStuntBonusForPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcTogglePlayerSpectating ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcTogglePlayerSpectating()" );
	return _funcTogglePlayerSpectating ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerDrunkLevel ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerDrunkLevel()" );
	return _funcGetPlayerDrunkLevel ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerDrunkLevel ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerDrunkLevel()" );
	return _funcSetPlayerDrunkLevel ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcPlayerSpectateVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcPlayerSpectateVehicle()" );
	return _funcPlayerSpectateVehicle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcPlayerSpectatePlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcPlayerSpectatePlayer()" );
	return _funcPlayerSpectatePlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcApplyAnimation ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcApplyAnimation()" );
	return _funcApplyAnimation ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcClearAnimations ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcClearAnimations()" );
	return _funcClearAnimations ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerAnimationIndex ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerAnimationIndex()" );
	return _funcGetPlayerAnimationIndex ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetAnimationName ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetAnimationName()" );
	return _funcGetAnimationName ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerSpecialAction ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerSpecialAction()" );
	return _funcSetPlayerSpecialAction ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerSpecialAction ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerSpecialAction()" );
	return _funcGetPlayerSpecialAction ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcStartRecordingPlayerData ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcStartRecordingPlayerData()" );
	return _funcStartRecordingPlayerData ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcStopRecordingPlayerData ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcStopRecordingPlayerData()" );
	return _funcStopRecordingPlayerData ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcPlayCrimeReportForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcPlayCrimeReportForPlayer()" );
	return _funcPlayCrimeReportForPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerShopName ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerShopName()" );
	return _funcSetPlayerShopName ( a_AmxInterface, a_Params );
}


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

	return (cell)__NetGame->playerPool->GetPlayer( playerID )->getCustomSpawn( )->Team;
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
		return player->getOnFootSyncData( )->surfingVehicleID;
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

	return ( cell )( player->isPlayerStreamedIn( playerID ) ? 1 : 0 );
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